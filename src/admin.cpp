#include "admin.hpp"
#include<iostream>

using namespace std;

Admin::Admin(): Person(), username("admin"), password("12345"){}

Admin::Admin(int id, string first, string last, string phone, string email, string address, string username, string password)
: Person(id, first, last, phone, email, address), username(user), password(pass) {}

string Admin::getUsername() const
{
    return username;
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
    string name, location;

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
            cout<<"Room ID: "<<r->get_room_ID()
            <<" | Price: "<<r->get_base_price()
            <<" | Booked: "<<(r->get_book_status() ? "Yes": "No")<<endl;
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
}