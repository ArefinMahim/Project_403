#pragma once
#include "guest.hpp"
//#include "admin.hpp"
#include "hotel.hpp"
#include "rooms.hpp"
#include "days.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class FileManager
{
    private:

    static vector<string> split(const string& s, char delim) //taking a whole string as input and parsing it properly to load
    {
        vector<string> tokens;
        string token;
        istringstream ss(s);
        while (getline(ss, token, delim))
            tokens.push_back(token);
        return tokens;
    }


    public:

    //save functions

    //save for guests

    static void saveGuests(const vector<Guest>& guests) 
    {
        ofstream f("guests.txt");
        if (!f) { cerr << "[FileManager] Cannot write guests.txt\n"; return; }
        f << "# Project_403 Guest Accounts\n";  //#will indicate skipping of line as input when loading
        for (auto& g : guests) 
        {
            f << "GUEST|" << g.getId()          << "|"
                          << g.getFirstName()   << "|"
                          << g.getLastName()    << "|"
                          << g.getPhone()       << "|"
                          << g.getEmail()       << "|"
                          << g.getAddress()     << "|"
                          << g.getNid()         << "|"
                          << g.getUsername()    << "|"
                          << g.getPasswordHash()<< "|"
                          << g.getProfileCreated() << "|"
                          << static_cast<int>(g.getTier()) << "\n";
            for (auto& b : g.getBookingHistory()) 
            {
                f << "BOOKING|" << b.hotelName << "|"
                                << b.roomID    << "|"
                                << b.roomType  << "|"
                                << b.checkIn   << "|"
                                << b.checkOut  << "|"
                                << b.totalCost << "|"
                                << (b.active ? 1 : 0) << "\n";
            }
            f << "END_GUEST\n";
        }


    }

    //for hotels

    static void saveHotels(const vector<Hotel>& hotels) 
    {
        ofstream f("hotels.txt");
        if (!f) { cerr << "[FileManager] Cannot write hotels.txt\n"; return; }
        f << "# Project_403 Hotels\n";
            for (const auto& h : hotels)
            {
                f << "HOTEL|" << h.get_id()       << "|"
                        << h.get_name()      << "|"
                        << h.get_location()  << "\n";
            }
    }
    //for rooms of each individual Hotels

    static void saveRooms(const vector<Hotel>& hotels) {
        ofstream f("rooms.txt");
        if (!f) { cerr << "[FileManager] Cannot write rooms.txt\n"; return; }
        f << "# Project_403 Rooms\n";
        for (const auto& h : hotels) {
            for (const auto* r : h.get_rooms()) {
                f << "ROOM|" << h.get_name()        << "|"
                              << r->get_room_ID()     << "|"
                              << r->get_type()        << "|"
                              << r->get_base_price()  << "|"
                              << (r->get_book_status() ? 1 : 0) << "|"
                              << r->get_booker_ID()   << "|"
                              << r->get_guest_count() << "\n";
            }
        }
    }

    //helper function to save everything at once
    
    static void saveAll(const vector<Guest>& guests,const vector<Hotel>& hotels) {
        saveGuests(guests);
        saveHotels(hotels);
        saveRooms(hotels);
    }

    //Load functions

    //Load Guests

        static vector<Guest> loadGuests() {
        vector<Guest> guests;
        ifstream f("guests.txt");
        if (!f)
        { 
            cerr<<"File could not be opened, resetting Guests."<<endl;
            return guests;
        }
        
        string line;
        Guest* cur = nullptr;  
        vector<BookingRecord> currentBookings; // Temp storage for bookings
        
        while (getline(f, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto fields = split(line, '|');
            if (fields.empty()) continue;
            
            if (fields[0] == "GUEST" && fields.size() == 12) //a guest should have 12 data, so a full field is a complete guest
                                                            //learned the use of this from AI
            {
                // if there a previous guest already, then store it
                if (cur) {
                    for (const auto& b : currentBookings) {
                        cur->addBookingRaw(b);
                    }
                    guests.push_back(*cur);
                    delete cur;
                    currentBookings.clear();
                }
                
                // Create new guest
                cur = new Guest(
                    stoi(fields[1]), fields[2], fields[3],
                    fields[4], fields[5], fields[6],
                    fields[7], fields[8], "placeholder"
                );
                cur->setPasswordHashRaw(fields[9]);
                cur->setProfileCreated(fields[10]);
                cur->setTier(static_cast<MemberTier>(stoi(fields[11])));
                
            } 
            else if (fields[0] == "BOOKING" && fields.size() == 8 && cur) //complete booking has 8 fields
            {
                Days d;

                BookingRecord b;
                b.hotelName = fields[1];
                b.roomID    = fields[2];
                b.roomType  = fields[3];
                b.checkIn   = d.stringToDate(fields[4]);
                b.checkOut  = d.stringToDate(fields[5]);
                b.totalCost = stod(fields[6]);
                b.active    = (fields[7] == "1");
                currentBookings.push_back(b);
                
            } else if (fields[0] == "END_GUEST" && cur) {
                // Add all bookings to guest
                for (const auto& b : currentBookings) {
                    cur->addBookingRaw(b);
                }
                guests.push_back(*cur);
                delete cur;
                cur = nullptr;
                currentBookings.clear();
            }
        }
        
        // Cleanup if file ends without END_GUEST
        if (cur) {
            for (const auto& b : currentBookings) {
                cur->addBookingRaw(b);
            }
            guests.push_back(*cur);
            delete cur;
        }
        
        return guests;
    }
    

    class HotelInfo //helper class which doesnt involve rooms for easy load
    {
        public:
        int id; 
        string name; 
        string location; 
    };

    //input loading for hotel
    
    static vector<HotelInfo> loadHotelInfo() {
        vector<HotelInfo> info;
        ifstream f("hotels.txt");
        if (!f) return info;
        string line;
        while (getline(f, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto fields = split(line, '|');
            if (fields[0] == "HOTEL" && fields.size() == 4)
                info.push_back({stoi(fields[1]), fields[2], fields[3]});
        }
        return info;
    }

    //input for rooms

    static void loadRoomStates(vector<Hotel>& hotels) {
        ifstream f("rooms.txt");
        if (!f) return;
        string line;
        while (getline(f, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto fields = split(line, '|');
            if (fields[0] == "ROOM" && fields.size() == 8) {
                string hotelName = fields[1];
                string roomID    = fields[2];
                bool   booked    = (fields[5] == "1");
                string booker    = fields[6];
                
                for (auto& h : hotels) {
                    if (h.get_name() == hotelName) {
                        Room* r = h.find_room(roomID);
                        if (r && booked) {
                            r->set_book_status(true);
                            r->set_booker_ID(booker);
                        }
                        break;
                    }
                }
            }
        }
    }


    static bool saveFilesExist(const string& filename) //check if file exists
    {
        ifstream f(filename);
        return f.good();
    }

};
