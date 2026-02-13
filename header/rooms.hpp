#pragma once

#include "utility.hpp"


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

    Room();

    virtual void print_description()const = 0;
    virtual void print_status() const =0;
    virtual double calculate_total_price() const =0;

    string get_room_ID()const;
    virtual int get_type()const;
    float get_base_price()const;
    string get_description()const;
    bool get_book_status()const;
    string get_booker_ID()const;
    int get_guest_count()const;
    static int get_total_room_count();


    void manual_alter_room_ID(string x);
    void set_type(int x);
    void set_base_price(int x);
    void set_description(string s);
    void set_book_status(bool a);
    void set_booker_ID(string s);
    void set_guest_count(int n);


    void book_room();


    virtual ~Room(){}

};

class Standard_room : public Room           //making room of standard type
{
    private:
    vector<string> priviledges;
    static int Standard_room_count;

    public:

    Standard_room();

    double calculate_total_price()const;

    void print_description()const;

    void print_status()const;

    vector<string> get_all_priviledges();

    string get_n_priviledge(int n);     //1 based indexing
    


    void push_priviledge(string s);
    
    void set_n_priviledge(int n,string s);
    

    void set_priviledges(vector<string> s);
    

};

class Economy_room : public Room
{
    private:

    bool has_window;
    bool shared_wifi;
    bool has_private_facilities;
    static int Economy_room_count;

    public:

    Economy_room();

    void print_description() const;

    void print_status();

    double calculate_total_price();

    
    bool get_shared_wifi() const;

    bool get_private_facilities() const;

    bool get_window()const;

    int get_economy_room_count();


    void set_window(bool a);

    void set_shared_wifi(bool a);

    void set_private_facilities(bool a);

    ~Economy_room();

};


class Premium_room:public Room
{
    private:

    vector<string> is_connected_to;
    bool has_dedicated_staff;
    static int Premium_room_count;

    public:

    Premium_room();

    double calculate_total_price();
    
    void print_description();

    void print_status();

    void add_connection(string s);

    void set_connection(vector<string> sv);

    void set_dedicated_staff(bool a);


    vector<string> get_connections()const;
    
    bool get_dedicated_staff();

    static int get_premium_room_count();

    ~Premium_room();


};
