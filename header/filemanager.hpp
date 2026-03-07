#pragma once
#include "guest.hpp"
//#include "admin.hpp"
#include "hotel.hpp"
#include "rooms.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class FileManager
{
    private:

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


};
