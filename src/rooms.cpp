#include "rooms.hpp"

//Room class functions

Room::Room(): room_ID("null"),type(Standard), base_price(100),description("Empty room, yet to be fleshed out"), book_status(false),booker_ID("null"),max_guest_count(0){}

    string Room::get_room_ID()const
    {
        return room_ID;
    }
    int Room::get_type()const
    {
        return type;
    }
    float Room::get_base_price()const
    {
        return base_price;
    }
    string Room::get_description()const
    {
        return description;
    }
    bool Room::get_book_status()const
    {
        return book_status;
    }
    string Room::get_booker_ID()const
    {
        return booker_ID;
    }
    int Room::get_guest_count()const
    {
        return max_guest_count;
    }

    void Room::manual_alter_room_ID(string x)
    {
        room_ID = x;
    }
    void Room::set_type(int x)
    {
        type = x;
    }
    void Room::set_base_price(int x)
    {
        base_price =x;
    }
    void Room::set_description(string s)
    {
        description = s;
    }
    void Room::set_book_status(bool a)
    {
        book_status = a;
    }
    void Room::set_booker_ID(string s)
    {
        booker_ID =s;
    }
    void Room::set_guest_count(int n)
    {
        max_guest_count = n;
    }

    void Room::book_room()
    {
        if(book_status)
        {
            cout<<"Booking failed, Room \""<<room_ID<<"\" is already booked";
        }
        else{
            cout<<"Booking successful, Room \""<<room_ID<<"\" has been booked.";
            book_status = true;
        }
    }

int Room::total_room_count = 0;         

//Standard Room class functions


double Standard_room::calculate_total_price()const
    {
        return get_base_price() * 3.0;  //3.0 has just been put as a buffer number, after implementing date class, we will use that to determine total cost
    }

    void Standard_room::print_description()const
    {
        cout<<get_description()<<endl;      //extra information based on the room type will be added
    }
    void Standard_room::print_status()const
    {
        cout<<"blank for now"<<endl;
    }

    vector<string> Standard_room::get_all_priviledges()
    {
        return priviledges;
    }
    string Standard_room::get_n_priviledge(int n)      //1 based indexing
    {
        return priviledges[n-1];
    }


    void Standard_room::push_priviledge(string s)
    {
        priviledges.push_back(s);
    }
    void Standard_room::set_n_priviledge(int n,string s)
    {
        if(n>priviledges.size())
        {
            cout<<"Error in setting priviledge. Out of scope"<<endl;
        }
        priviledges[n-1] = s;
    }

    void Standard_room::set_priviledges(vector<string> s)
    {
        priviledges = s;
    }

int Standard_room::Standard_room_count = 0;
