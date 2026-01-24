#include <iostream>
#include <string>

using namespace std;

class Hotel;

enum Type {Premium, Standard, Economy};

class Room              //making the general room "type" class, an abstract class.
{
    private:
    
    string room_ID;
    int type;
    float base_price;
    string description;
    bool book_status;

    static int room_count;

    public:

    Room(): room_ID("null"),type(Standard), base_price(100),description("Empty room, yet to be fleshed out"), book_status(false){}

    virtual void print_description()const = 0;

    virtual string get_room_ID()const =0;
    virtual int get_type()const =0;
    virtual float get_base_price()const =0;
    virtual string get_description()const =0;
    virtual bool get_status()const = 0;

    virtual void manual_alter_room_ID(string x)=0;
    virtual void set_type(int x)=0;
    virtual void set_base_price(int x)=0;
    virtual void set_description(string s)=0;
    virtual void set_status(bool a)=0;


};

int Room::room_count = 0;