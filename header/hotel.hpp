#pragma once
#include "utility.hpp"
#include "rooms.hpp"


class Hotel{
    private:
        int hotel_Id;
        string name;
        string location;
        static vector<int> id;
        vector<Room*> rooms;

    public:
        Hotel(string name, string location);

        int get_id()const;

        string get_name()const;

        string get_location()const;


        void set_name(string name);

        void set_location(string location);
        

        void add_room(Room& room);

        void print_details()const;
};