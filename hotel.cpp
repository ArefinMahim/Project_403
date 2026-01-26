#pragma once
#include "utility.cpp"
#include "rooms.cpp"
using namespace std;

class Hotel{
    private:
        int hotel_Id;
        string name;
        string location;
        static vector<int> id;
        vector<Room> rooms;

    public:
        Hotel(string name, string location){
            srand(time(NULL));
            int h_id=rand()%(9999-1000+1)+1000;

            while(1){
                auto it=find(id.begin(), id.end(), h_id);

                if(it!=id.end()){
                    h_id=rand()%(9999-1000+1)+1000;
                }

                else{
                    hotel_Id=h_id;
                    id.push_back(h_id);
                    break;
                }
            }

            this->name=name;
            this->location=location;
        }

        int get_id()const{
            return hotel_Id;
        }

        string get_name()const{
            return name;
        }

        string get_location()const{
            return location;
        }

        void set_name(string name){
            this->name=name;
        }

        void set_location(string location){
            this->location=location;
        }

        void add_room(Room& room){
            rooms.push_back(room);
        }

        void print_details()const{
            cout<<"Hotel ID: "<<hotel_Id<<endl;
            cout<<"Hotel Name: "<<name<<endl;
            cout<<"Hotel Location: "<<location<<endl;
            cout<<"Number of Rooms: "<<rooms.size()<<endl;
        }
};