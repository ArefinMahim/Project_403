#pragma once
#include "person.hpp"
#include "hotel.hpp"
#include "rooms.hpp"
#include "guest.hpp"
#include<vector>
#include<string>

using namespace std;

class Admin: public Person
{
    private:
    string username;
    string password;

    public:

    Admin();

    Admin(int id, string first, string last, string phone, string email, string address, string username, string password);

    string getUsername() const;

    bool authenticate(string pass) const;

    // Hotel Authorization

    void listHotels(const vector<Hotel*> & hotels) const;
    void addHotel(vector<Hotel*>& hotels);
    void removeHotel(vector<Hotel*>& hotels, int hotelId);

    //Room Authorization

    void listRooms(const vector<Room*>& rooms) const;
    void addRoom(vector<Room*> & rooms);
    void removeRoom(vector<Room*> & rooms, string roomId);

    //Guest Authoriztion

    void listGuests(const vector<Guest>& guests) const;
    void removeGuest(vector<Guest> & guests, int guestId);

    
    // Console

    void runConsole(vector<Hotel*> & hotels, vector<Room*> & rooms, vector<Guest> & guests);
};