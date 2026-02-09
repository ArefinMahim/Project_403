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

    double calculate_total_price()const;

    void print_description()const;

    void print_status()const;

    vector<string> get_all_priviledges();

    string get_n_priviledge(int n);     //1 based indexing
    


    void push_priviledge(string s);
    
    void set_n_priviledge(int n,string s);
    

    void set_priviledges(vector<string> s);
    

};


