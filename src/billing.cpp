#include"billing.hpp"

//Booking Class Functions

        Booking::Booking(Hotel* h, Room* r, int n):hotel(h), room(r), nights(n), totalPrice(0.0), discountedPrice(0.0), discountAmount(0), discountPercent(0){}
        //use srand(time(NULL)) in main
        Booking::~Booking(){}

        Room* Booking::getRoom() const{return room;}
        Hotel* Booking::getHotel() const{return hotel;}
        int Booking::getNights() const{return nights;}
        double Booking::getTotalPrice() const{return totalPrice;}
        double Booking::getDiscountedPrice() const{return discountedPrice;}
        double Booking::getDiscountAmount() const{return discountAmount;}
        int Booking::getDiscountPercent() const{return discountPercent;}

        //Setters
        void Booking::setRoom(Room* r){
            room=r;
        }
        void Booking::setHotel(Hotel* h){
            hotel=h;
        }
        void Booking::setNights(const Days& checkIn, const Days& checkOut) {
            int stayedNights=checkIn.noOfDays(checkOut);
            if(stayedNights<0){
                cout<<"Invalid stay dates.\n";
                nights=0;
            return;
            }
            checkInDate=checkIn;
            checkOutDate=checkOut;
            nights=stayedNights;
        }

        void Booking::calculateTotalPrice(){
            totalPrice=room->calculate_total_price()*nights;
            discountedPrice=totalPrice;
            cout<<"Total price: "<<totalPrice<<endl;
        }
        void Booking::applyVoucher(){
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

        string Booking::roomTypename(){
            switch(room->get_type()){
                case Economy: return "Economy";
                case Standard: return "Standard";
                case Premium: return "Premium";
                default: return "Unknown";
            }
        }

        void Booking::checkout(){
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

        void Booking::paymentDelay() {
            cout<<"Processing payment";
            for(int i=0; i<3; i++) {
                cout<<".";
                cout.flush();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            cout<<endl;
        }

        void Booking::paymentMethod(){
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

        void Booking::processCash(){
            paymentDelay();
            cout<<"Received "<<discountedPrice<<" in cash. Payment successful!"<<endl;
            cout<<"Thank you!"<<endl;
        }

        void Booking::processEbanking(){
            string accNumber;
            string pin;
            cout<<"\nEnter your bank account number: ";
            cin>>accNumber;
            cout<<"Enter your PIN: ";
            cin>>pin;
            paymentDelay();
            cout<<"Received "<<discountedPrice<<" via e-banking. \nThank you!"<<endl;
        }

