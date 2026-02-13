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
    int Room::get_total_room_count()
    {
        return Room::total_room_count;
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

    Standard_room::Standard_room(): Room(),priviledges({"null","null2.0"}){}

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

// Economy room functions

    Economy_room::Economy_room():Room(), has_window(false),shared_wifi(true),has_private_facilities(false){}

    void Economy_room::print_description() const
    {
        cout<<get_description()<<endl;
    }

    void Economy_room::print_status()
    {
        cout<<"Also empty for now"<<endl;
    }

    double Economy_room::calculate_total_price()
    {
        return get_base_price() * 2;
    }

    
    bool Economy_room::get_shared_wifi() const
    {
        return shared_wifi;
    }

    bool Economy_room::get_window() const
    {
        return has_window;
    }

    bool Economy_room::get_private_facilities() const
    {
        return has_private_facilities;
    }

    int Economy_room::get_economy_room_count()
    {
        return Economy_room_count;
    }


    void Economy_room::set_window(bool a)
    {
        has_window = a;
    }

    void Economy_room::set_shared_wifi(bool a)
    {
        shared_wifi = a;
    }

    void Economy_room::set_private_facilities(bool a)
    {
        has_private_facilities = a;
    }

    Economy_room::~Economy_room(){}

    int Economy_room::Economy_room_count =0;

    //Premium Room Functions

    Premium_room::Premium_room():Room(),has_dedicated_staff(true),is_connected_to({"spa","gym"}){}

    double Premium_room::calculate_total_price()
    {
        return get_base_price() * 4 * (1.2 * is_connected_to.size());
    }
    void Premium_room::print_description()
    {
        cout<<get_description()<<endl;
    }

    void Premium_room::print_status()
    {
        cout<<"Also also empty for now"<<endl;
    }

    void Premium_room::add_connection(string s)
    {
        is_connected_to.push_back(s);
    }

    void Premium_room::set_connection(vector<string> sv)
    {
        is_connected_to = sv;
    }

    void Premium_room::set_dedicated_staff(bool a)
    {
        has_dedicated_staff = a;
    }


    vector<string> Premium_room::get_connections()const
    {
        return is_connected_to;
    }
    
    bool Premium_room::get_dedicated_staff()
    {
        return has_dedicated_staff;
    }

    int Premium_room::get_premium_room_count()
    {
        return Premium_room_count;
    }

    Premium_room::~Premium_room(){}

    int Premium_room::Premium_room_count = 0;