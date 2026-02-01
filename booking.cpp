#pragma once
#include"utility.cpp"
#include"rooms.cpp"
#include"hotel.cpp"
#include"guest.cpp"
using namespace std;

class Booking{
    private:
        int booking_ID;
        static vector<int> id;

        Guest* guest;
        Hotel* hotel;
        Room* room;

        string check_in_date;
        string check_out_date;

        int nights;
        int cost;
        bool confirmed;

        int generate_id(){
            srand(time(NULL));
            int b_id=rand()%(99999-10000+1)+10000;

            while(1){
                auto it=find(id.begin(), id.end(), b_id);

                if(it!=id.end()){
                    b_id=rand()%(99999-10000+1)+10000;
                }

                else{
                    id.push_back(b_id);
                    return b_id;
                }
            }
        }

    public:
        Booking(){
            booking_ID=0;
            guest=NULL;
            hotel=NULL;
            room=NULL;
            check_in_date="None";
            check_out_date="None";
            nights=0;
            cost=0;
            confirmed=false;
        }

        Booking(Guest* guest, Hotel* hotel, Room* room, string check_in_date, string check_out_date, int nights, int cost, bool confirmed){
            booking_ID=generate_id();
            this->guest=guest;
            this->hotel=hotel;
            this->room=room;
            this->check_in_date=check_in_date;
            this->check_out_date=check_out_date;
            if(nights>0)    this->nights=nights;
            if(cost>=0)     this->cost=cost;
            this->confirmed=confirmed;
        }

        ~Booking(){
            cout<<"Booking with ID "<<booking_ID<<" is being deleted."<<endl;
        }

        void set_guest(Guest* guest){
            this->guest=guest;
        }

        void set_hotel(Hotel* hotel){
            this->hotel=hotel;
        }

        void set_room(Room* room){
            this->room=room;
        }

        void set_check_in_date(string date){
            this->check_in_date=date;
        }

        void set_check_out_date(string date){
            this->check_out_date=date;
        }

        void set_nights(int nights){
            if(nights>0) this->nights=nights;
        }

        void set_cost(int cost){
            if(cost>=0) this->cost=cost;
        }

        void set_confirmed(bool confirmed){
            this->confirmed=confirmed;
        }

        int get_booking_ID() const{
            return booking_ID;
        }

        Guest* get_guest() const{
            return guest;
        }

        Hotel* get_hotel() const{
            return hotel;
        }

        Room* get_room() const{
            return room;
        }

        string get_check_in_date() const{
            return check_in_date;
        }

        string get_check_out_date() const{
            return check_out_date;
        }

        int get_nights() const{
            return nights;
        }

        int get_cost() const{
            return cost;
        }

        bool is_confirmed() const{
            return confirmed;
        }

        void calculate_cost(){
            if(room==NULL || hotel==NULL){
                cout<<"Cannot calculate cost. Room or Hotel information is missing."<<endl;
                cost=0;
                return;
            }

            int per_night_cost=room->calculate_total_price();
            cost=per_night_cost*nights;
        }

        bool confim_booking(){
            if(guest==NULL || hotel==NULL || room==NULL){
                cout<<"Booking failed. Missing information."<<endl;
                confirmed=false;
                return false;
            }

            if(room->get_book_status()){
                cout<<"Room already booked"<<endl;
                confirmed=false;
                return false;
            }

            room->set_book_status(true);
            room->set_booker_ID(to_string(guest->getId()));

            cout<<"Booking confirmed for Guest ID "<<guest->getId()<<" in Hotel "<<hotel->get_name()<<" for Room ID "<<room->get_room_ID()<<endl;
            confirmed=true;
            return true;
        }

        void cancel_booking(){
            if(room!=NULL && room->get_book_status()){
                room->set_book_status(false);
                room->set_booker_ID("None");
            }

            confirmed=false;
            cout<<"Booking with ID "<<booking_ID<<" has been cancelled."<<endl;
        }

        void display_booking_info() const{
            cout<<"Booking ID: "<<booking_ID<<endl;
            if(guest!=NULL){
                cout<<"Guest Name: "<<guest->getFullName()<<"("<<guest->getId()<<")"<<endl<<endl;
            }
            if(hotel!=NULL){
                cout<<"Hotel Name: "<<hotel->get_name()<<endl;
                cout<<"Hotel Location: "<<hotel->get_location()<<endl<<endl;
            }
            if(room!=NULL){
                cout<<"Room ID: "<<room->get_room_ID()<<endl;
                cout<<"Room Type: ";
                switch(room->get_type()){
                    case Economy: cout<<"Economy"<<endl; break;
                    case Standard: cout<<"Standard"<<endl; break;
                    case Premium: cout<<"Premium"<<endl; break;
                    default: cout<<"Error"<<endl; break;
                }
                cout<<endl;
            }
            cout<<"Check-In Date: "<<check_in_date<<endl;
            cout<<"Check-Out Date: "<<check_out_date<<endl<<endl;
            cout<<"Nights: "<<nights<<endl;
            cout<<"Cost: "<<cost<<endl<<endl;
            cout<<"Confirmed: "<<(confirmed ? "Yes" : "No")<<endl;
        }
};

vector<int> Booking::id;