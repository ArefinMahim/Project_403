#pragma once
#include"utility.cpp"
#include"rooms.cpp"
#include"hotel.cpp"
using namespace std;

class Booking{
    private:
        Room* room;
        Hotel* hotel;
        int nights;
        double totalPrice;
        double discountedPrice;
        double discountAmount;
        int discountPercent;
    public:
        Booking(Hotel* h, Room* r, int n):hotel(h), room(r), nights(n), totalPrice(0.0), discountedPrice(0.0), discountAmount(0), discountPercent(0){}
        //use srand(time(NULL)) in main
        ~Booking(){}

        Room* getRoom() const{return room;}
        Hotel* getHotel() const{return hotel;}
        int getNights() const{return nights;}
        double getTotalPrice() const{return totalPrice;}
        double getDiscountedPrice() const{return discountedPrice;}
        double getDiscountAmount() const{return discountAmount;}
        int getDiscountPercent() const{return discountPercent;}

        //Setters
        void setRoom(Room* r){
            room=r;
        }
        void setHotel(Hotel* h){
            hotel=h;
        }
        void setNights(int n){
            if(n>=0) nights=n;
        }

        void calculateTotalPrice(){
            totalPrice=room->calculate_total_price()*nights;
            discountedPrice=totalPrice;
            cout<<"Total price: "<<totalPrice<<endl;
        }
        void applyVoucher(){
            char choice;
            cout<<"\nDo you want to apply a voucher?(y/n): ";
            cin>>choice;
            if(choice=='n' || choice=='N'){
                return;
            }
            int attempts=3;
            while(attempts>0){
                string voucher;
                cout<<"Enter voucher code: ";
                cin>>voucher;
                if(voucher=="FABIAN"||
                voucher=="ISHMAM"||
                voucher=="SIDDIQUE"||
                voucher=="MAHIM"){
                    discountPercent=(rand()%50)+1;
                    discountAmount=totalPrice*(discountPercent/100.0);
                    discountedPrice=totalPrice-discountAmount;
                    cout<<"Voucher applied successfully! You got "<<discountPercent<<"% discount."<<endl;
                    cout<<"Discount amount: "<<discountAmount<<endl;
                    break;
                }
                else{
                    attempts--;
                    cout<<"Invalid voucher code. Attempts left: "<<attempts<<endl;
                    if(attempts==0){
                        cout<<"No attempts left. Proceeding without voucher.\n";
                        return;
                    }
                    cout<<"Do you want to try again? (y/n): ";
                    cin>>choice;
                    if(choice=='n'||choice=='N'){
                        return;
                    }
                }
            }
        }

        string roomTypename(){
            switch(room->get_type()){
                case Economy: return "Economy";
                case Standard: return "Standard";
                case Premium: return "Premium";
                default: return "Unknown";
            }
        }

        void checkout(){
            calculateTotalPrice();
            applyVoucher();
            cout<<"\n-----CHECKOUT-----"<<endl;
            cout<<"Hotel Name: "<<hotel->get_name()<<endl;
            cout<<"Room Type: "<<roomTypename()<<endl;
            cout<<"Number of Nights: "<<nights<<endl;
            cout<<"Total Price: "<<totalPrice<<endl;
            cout<<"Discount Amount: "<<discountAmount<<endl;
            cout<<"Final Price: "<<discountedPrice<<endl;

            paymentMethod();
        }

        void paymentDelay() {
            cout<<"Processing payment";
            for(int i=0; i<3; i++) {
                cout<<".";
                cout.flush();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            cout<<endl;
        }

        void paymentMethod(){
            int choice;
            while(true){
                cout<<"\nSelect Payment Method:"<<endl;
                cout<<"1. Cash"<<endl;
                cout<<"2. E-banking"<<endl;
                cout<<"Enter choice (1 or 2): ";
                cin>>choice;
                if(choice==1){
                    processCash();
                    break;
                }
                else if(choice==2){
                    processEbanking();
                    break;
                }
                else{
                    cout<<"Invalid choice. Please try again."<<endl;
                }
            }
        }

        void processCash(){
            paymentDelay();
            cout<<"Received "<<discountedPrice<<" in cash. Payment successful!"<<endl;
            cout<<"Thank you!"<<endl;
        }

        void processEbanking(){
            string accNumber;
            string pin;
            cout<<"\nEnter your bank account number: ";
            cin>>accNumber;
            cout<<"Enter your PIN: ";
            cin>>pin;
            paymentDelay();
            cout<<"Received "<<discountedPrice<<" via e-banking. \nThank you!"<<endl;
        }
};