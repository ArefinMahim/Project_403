#include"utility.cpp"
#include"rooms.cpp"
using namespace std;

class Hotel{
    private:
        int hotel_ID;
        static vector<int> id;

        string name;
        string location;

        vector<Room*> rooms;

        int generate_id(){
            srand(time(NULL));
            int h_id=rand()%(9999-1000+1)+1000;

            while(1){
                auto it=find(id.begin(), id.end(), h_id);

                if(it!=id.end()){
                    h_id=rand()%(9999-1000+1)+1000;
                }

                else{
                    id.push_back(h_id);
                    return h_id;
                }
            }
        }

    public:
        Hotel(){
            hotel_ID=0;
            name="None";
            location="None";
        }
    
        Hotel(string name, string location){
            hotel_ID=generate_id();
            this->name=name;
            this->location=location;
        }

        int get_id()const{
            return hotel_ID;
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

        void add_room(Room* room){
            rooms.push_back(room);
        }

        void print_details()const{
            cout<<"Hotel ID: "<<hotel_ID<<endl;
            cout<<"Hotel Name: "<<name<<endl;
            cout<<"Hotel Location: "<<location<<endl;
            cout<<"Number of Rooms: "<<rooms.size()<<endl;
        }
};

vector<int> Hotel::id;