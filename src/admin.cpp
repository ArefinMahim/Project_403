#include "admin.hpp"
#include "rooms.hpp"
#include "hotel.hpp"
#include "guest.hpp"
#include "person.hpp"
#include "rooms.hpp"
#include<iostream>

using namespace std;

Admin::Admin(): Person(), username("admin"), password("12345"){}

Admin::Admin(int id, string first, string last, string phone, string email, string address, string username, string password)
: Person(id, first, last, phone, email, address), username(username), password(password) {}

string Admin::getUsername() const
{
    return username;
}

string Admin::getPassword() const
{
    return password;
}

bool Admin::authenticate(string pass) const
{
    return pass==password;
}

//Hotel Part

void Admin::listHotels(const vector<Hotel*>& hotels) const
{
    cout<<"\n------Hotels------";

    for(const auto* h:hotels)
    {
        if(h)
        {
            cout<<"ID: "<<h->get_id()
            <<" | Name: "<<h->get_name()
            <<" | Location: "<<h->get_location()<<"\n";
        }
    }
}

void Admin::addHotel(vector<Hotel*>& hotels) 
{
    string name, location, stars, e_n, s_n, p_n;

    cout<<"Enter hotel name: ";
    getline(cin>>ws, name);

    if(name.empty())
    {
        cout<<"Hotel name cannot be empty.\n";
        return;
    }

    cout<<"Enter location: ";
    getline(cin>>ws, location);

    if(location.empty())
    {
        cout<<"Location cannot be empty.\n";
        return;
    }

    Hotel* newHotel=new Hotel(name, location);
    hotels.push_back(newHotel);

    cout<<"Hotel added successfully.\n";
}

void Admin::removeHotel(vector<Hotel*>& hotels, int hotelId) 
{
    for (int i=0; i<hotels.size(); i++) {
        if (hotels[i]->get_id()==hotelId) {
            delete hotels[i];
            hotels.erase(hotels.begin()+i);
            cout << "Hotel removed.\n";
            return;
        }
    }
    cout << "Hotel not found.\n";
}

// Room Part

void Admin::listRooms(const vector<Room*>& rooms) const
{
    cout<<"\n------Rooms------\n";

    for(const auto* r:rooms)
    {
        if(r)
        {
            r->print_description();
        }
    }
}

void Admin::addRoom(vector<Room*> & rooms)
{
    int type;
    cout<<"Choose room type (1=Economy, 2=Standard, 3=Premium): ";
    cin>>type;

    Room* newRoom= nullptr;

    if(type==1) newRoom= new Economy_room();
    else if(type==2) newRoom= new Standard_room();
    else if (type==3) newRoom= new Premium_room(); 

    else
    {
        cout<<"Invalid Type.\n";
        return;
    } 

    string id;
    int price;

    cout<<"Enter Room Id: ";
    cin>>id;
    cout<<"Enter Base Price: ";
    cin>>price;

    newRoom->manual_alter_room_ID(id);
    newRoom->set_base_price(price);

    rooms.push_back(newRoom);

    cout<<"Room added successfully.\n";
}

void Admin::removeRoom(vector<Room*>& rooms, string roomId)
{
    for(int i=0; i<rooms.size(); i++)
    {
        if(rooms[i]->get_room_ID()==roomId)
        {
            delete rooms[i];
            rooms.erase(rooms.begin()+i);
            cout<<"Room Removed.\n";
            return;
        }

        cout<<"Room Not Found.\n";
    }
}

// Guest Part

void Admin::listGuests(const vector<Guest>& guests) const
{
    cout<<"\n------Guests------\n";

    for(const auto& g:guests)
    {
        g.DisplayInfo();
    }
}

void Admin::removeGuest(vector<Guest>& guests, int guestId) 
{
    for (int i= 0; i<guests.size(); i++) {
        if (guests[i].getId()==guestId) {
            guests.erase(guests.begin()+i);
            cout << "Guest removed.\n";
            return;
        }
    }
    cout <<"Guest not found.\n";
}

// Admin Menu

void Admin::runConsole(vector<Hotel*>& hotels,vector<Room*>& rooms,vector<Guest>& guests)
{
    int choice;

    while(true)
    {
        cout<<"\n========ADMIN PANEL========\n";
        cout<<"1. List Hotels\n";
        cout <<"2. Add Hotel\n";
        cout <<"3. Remove Hotel\n";
        cout <<"4. List Rooms\n";
        cout <<"5. Add Room\n";
        cout <<"6. Remove Room\n";
        cout <<"7. List Guests\n";
        cout <<"8. Remove Guest\n";
        cout <<"0. Exit\n";
        cout <<"Choice: ";
        cin >> choice;

        if(choice==0) break;

        else if(choice==1) listHotels(hotels);

        else if(choice==2) addHotel(hotels);

        else if(choice==3)
        {
            int id;
            cout<<"Enter Hotel Id: ";
            cin>>id;
            removeHotel(hotels, id);
        }

        else if(choice==4) listRooms(rooms);
        else if(choice==5) addRoom(rooms);

        else if(choice==6)
        {
            string id;
            cout<<"Enter Room Id: ";
            cin>>id;
            removeRoom(rooms, id);
        }

        else if(choice==7) listGuests(guests);

        else if(choice==8)
        {
            int id;
            cout<<"Enter Guest Id: ";
            cin>>id;
            removeGuest(guests, id);
        }

        else cout<<"Invalid Operation.\n";
    }
}

