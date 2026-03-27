#pragma once
#include "hotel.hpp"
#include "rooms.hpp"
#include "guest.hpp"
#include "admin.hpp"
#include "billing.hpp"
#include "filemanager.hpp"
#include "utility.hpp"
 
using namespace std;

class HotelSystem
{
    private:

    vector<Hotel *> hotels;
    vector<Guest>   guests;
    vector<Admin>   admins;

    string makeID(Hotel* h, int& counter)
    {
        return ((h->get_name()[0])+to_string(counter++));
    }


    void makedefaultRooms(Hotel *h,int e_n,int s_n,int p_n) 
    {
        static int roomCounter = 1;

        for (int i = 0; i < e_n; i++) {
            Economy_room *r = new Economy_room();
            r->manual_alter_room_ID(makeID(h,roomCounter));
            r->set_base_price(60);
            r->set_guest_count(2);
            r->set_description("Cozy economy room with shared WiFi.");
            r->set_window(i % 2 == 0);
            h->add_room(*r);
        }

        for (int i = 0; i < s_n; i++) {
            Standard_room *r = new Standard_room();
            r->manual_alter_room_ID(makeID(h,roomCounter));
            r->set_base_price(120);
            r->set_guest_count(2);
            r->set_description("Comfortable standard room.");
            r->set_priviledges({"Free Breakfast", "Room Service", "Mini-bar"});
            h->add_room(*r);
        }

        for (int i = 0; i < p_n; i++) {
            Premium_room *r = new Premium_room();
            r->manual_alter_room_ID(makeID(h,roomCounter));
            r->set_base_price(250);
            r->set_guest_count(4);
            r->set_description("Luxurious premium suite.");
            r->set_dedicated_staff(true);
            h->add_room(*r);
        }
    }
    
    void makeDemoData() 
    {
        auto *h1 = new ThreeStar_Hotel("Grand Horizon", "Dhaka");
        makedefaultRooms(h1,3,3,3);
        hotels.push_back(h1);

        auto *h2 = new TwoStar_Hotel("Lakeside Inn", "Chittagong");
        makedefaultRooms(h2,2,2,2);
        hotels.push_back(h2);

        auto *h3 = new OneStar_Hotel("Budget Stay", "Sylhet");
        makedefaultRooms(h3,1,1,1);
        hotels.push_back(h3);
    }

    int generateGuestID()
    {
        int maxID = 1000;
        for (auto& g : guests)
            if (g.getId() > maxID) maxID = g.getId();
        return maxID + 1;
    }

    public:

    void save()
    {
        FileManager::saveAll(guests,hotels,admins);
    }

    void load()
    {
        admins = FileManager::loadAdmins();
        if (admins.empty()) {
            admins.push_back(Admin(1, "Admin", "User", "01458793524",
                                "admin@hotel.com", "Hotel HQ",
                                "admin", "admin123"));
            FileManager::saveAdmins(admins);
        }

        vector<FileManager::HotelInfo> hotelInfos = FileManager::loadHotelInfo(); 
        if (hotelInfos.empty()) {
            makeDemoData();
        }
        else {
            for (auto &info : hotelInfos) {
                    Hotel *h = nullptr;
                    if      (info.stars == 1) h = new OneStar_Hotel(info.name, info.location);
                    else if (info.stars == 2) h = new TwoStar_Hotel(info.name, info.location);
                    else                      h = new ThreeStar_Hotel(info.name, info.location);
                    makedefaultRooms(h,2,3,1);
                    hotels.push_back(h);
                }
                FileManager::loadRoomStates(hotels);
        }

        guests = FileManager::loadGuests();
    }

    HotelSystem()
    {
        load();
    }

    ~HotelSystem()
    {
        save();
        for(auto *h : hotels)
        {
            for(auto *r: h->get_rooms())
            {
                delete r;
            }
            delete h;
        }
    }

    vector<Hotel*>& getHotels() 
    {
        return hotels; 
    }
    vector<Guest>& getGuests() 
    {
        return guests;
    }
    vector<Admin>& getAdmins()
    {
        return admins;
    }

    void addHotel(const string &name, const string &location, int stars = 3) {
        Hotel *h = nullptr;
        if      (stars == 1) h = new OneStar_Hotel(name, location);
        else if (stars == 2) h = new TwoStar_Hotel(name, location);
        else                 h = new ThreeStar_Hotel(name, location);
        makedefaultRooms(h,4,3,2);
        hotels.push_back(h);
        save();
    }

    void removeHotel(const string &name) {
        for (auto it = hotels.begin(); it != hotels.end(); ++it) {
            if ((*it)->get_name() == name) {
                for (auto *r : (*it)->get_rooms())
                {
                    delete r;
                }
                delete *it;
                hotels.erase(it);
                save();
                return;
            }
        }
    }

    Hotel *findHotel(const string &name) {
        for (auto *h : hotels)
            if (h->get_name() == name)
                return h;
        return nullptr;
    }

    bool usernameExists(const string &username) const {
        for (auto &g : guests)
            if (g.getUsername() == username)
                return true;
        return false;
    }

    void registerGuest(const string &first, const string &last,const string &phone, const string &email,const string &address, const string &nid,
        const string &username, const string &password) 
    {
        Guest g(generateGuestID(), first, last, phone, email,
                address, nid, username, password);
        guests.push_back(g);
        save();
    }

    Guest *loginGuest(const string &username, const string &password) {
        for (auto &g : guests)
            if (g.getUsername() == username && g.verifyPassword(password))
                return &g;
        return nullptr;
    }

    Admin *loginAdmin(const string &username, const string &password) {
        for (auto &a : admins)
            if (a.getUsername() == username && a.authenticate(password))
                return &a;
        return nullptr;
    }

    Guest *findGuest(const string &username) {
        for (auto &g : guests)
            if (g.getUsername() == username)
                return &g;
        return nullptr;
    }

    void removeGuest(const string &username) {
        for (auto it = guests.begin(); it != guests.end(); ++it) {
            if (it->getUsername() == username) {
                guests.erase(it);
                save();
                return;
            }
        }
    }

    Booking *createBooking(Guest* guest, Hotel* hotel,const string &roomID,const Days &checkIn, const Days &checkOut) 
    {
        if (!hotel || !guest) return nullptr;

        Room *r = hotel->find_room(roomID);
        if (!r || r->get_book_status()) return nullptr;

        int nights = checkIn.noOfDays(checkOut);
        if (nights <= 0) return nullptr;

        Booking *b = new Booking(hotel, r, nights);
        b->setNights(checkIn, checkOut);
        return b;
    }

    void confirmBooking(Guest *guest, Hotel *hotel, Room *room,const Days &checkIn, const Days &checkOut,double finalPrice) {
        room->set_book_status(true);
        room->set_booker_ID(guest->getUsername());

        BookingRecord rec;
        rec.hotelName = hotel->get_name();
        rec.roomID    = room->get_room_ID();
        rec.roomType  = (room->get_type() == Economy)  ? "Economy":(room->get_type() == Standard) ? "Standard":"Premium";
        rec.checkIn   = checkIn;
        rec.checkOut  = checkOut;
        rec.totalCost = finalPrice;
        rec.active    = true;

        guest->addBookingRecord(rec);
        save();
    }


    void cancelRoomBooking(Hotel *hotel, const string &roomID) {
        if (!hotel) return;

        Room *r = hotel->find_room(roomID);
        if (!r) return;

        string bookerUsername = r->get_booker_ID();

        r->set_book_status(false);
        r->set_booker_ID("");

        for (auto &g : guests) {
            if (g.getUsername() != bookerUsername) continue;

            vector<BookingRecord> updated = g.getBookingHistory();
            for (auto &b : updated)
                if (b.roomID == roomID && b.hotelName == hotel->get_name() && b.active)
                    b.active = false;

            Guest blank(g.getId(), g.getFirstName(), g.getLastName(),
                        g.getPhone(), g.getEmail(), g.getAddress(),
                        g.getNid(), g.getUsername(), "placeholder");
            blank.setPasswordHashRaw(g.getPasswordHash());
            blank.setProfileCreated(g.getProfileCreated());
            blank.setTier(g.getTier());

            for (auto &b : updated)
                blank.addBookingRaw(b);

            g = blank;
            break;
        }
        save();
    }
};

