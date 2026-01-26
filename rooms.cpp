#include "utility.cpp"
using namespace std;

class Hotel;

enum Type {Economy =1, Standard, Premium};

class Room              //making the general room "type" class, an abstract class.
{
    private:
    
    string room_ID;
    int type;
    float base_price;
    string description;
    bool book_status;
    string booker_ID;
    int max_guest_count;
    //need a booking date and duration


    static int total_room_count;

    public:

    Room(): room_ID("null"),type(Standard), base_price(100),description("Empty room, yet to be fleshed out"), book_status(false),booker_ID("null"),max_guest_count(0){}

    virtual void print_description()const = 0;
    virtual void print_status() const =0;
    virtual double calculate_total_price() const =0;

    string get_room_ID()const
    {
        return room_ID;
    }
    virtual int get_type()const
    {
        return type;
    }
    float get_base_price()const
    {
        return base_price;
    }
    string get_description()const
    {
        return description;
    }
    bool get_book_status()const
    {
        return book_status;
    }
    string get_booker_ID()const
    {
        return booker_ID;
    }
    int get_guest_count()const
    {
        return max_guest_count;
    }

    void manual_alter_room_ID(string x)
    {
        room_ID = x;
    }
    void set_type(int x)
    {
        type = x;
    }
    void set_base_price(int x)
    {
        base_price =x;
    }
    void set_description(string s)
    {
        description = s;
    }
    void set_book_status(bool a)
    {
        book_status = a;
    }
    void set_booker_ID(string s)
    {
        booker_ID =s;
    }
    void set_guest_count(int n)
    {
        max_guest_count = n;
    }

    void book_room()
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


    virtual ~Room(){}

};


int Room::total_room_count = 0;         

class Standard_room : public Room           //making room of standard type
{
    private:
    vector<string> priviledges;
    static int Standard_room_count;

    public:

    double calculate_total_price()const
    {
        return get_base_price() * 3.0;  //3.0 has just been put as a buffer number, after implementing date class, we will use that to determine total cost
    }

    void print_description()const
    {
        cout<<get_description()<<endl;      //extra information based on the room type will be added
    }
    void print_status()const
    {
        cout<<"blank for now"<<endl;
    }

    vector<string> get_all_priviledges()
    {
        return priviledges;
    }
    string get_n_priviledge(int n)      //1 based indexing
    {
        return priviledges[n-1];
    }


    void push_priviledge(string s)
    {
        priviledges.push_back(s);
    }
    void set_n_priviledge(int n,string s)
    {
        if(n>priviledges.size())
        {
            cout<<"Error in setting priviledge. Out of scope"<<endl;
        }
        priviledges[n-1] = s;
    }

    void set_priviledges(vector<string> s)
    {
        priviledges = s;
    }

};

int Standard_room::Standard_room_count = 0;