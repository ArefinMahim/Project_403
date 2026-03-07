#include"payment.hpp"
#include"utility.hpp"
using namespace std;

static void paymentDelay(){         //help from geeksforgeeks and chatgpt(sleep for method)
    cout<<"Processing payment";
    for(int i=0; i<3; i++){
        cout<<".";
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout<<endl;
}

void cashPayment::process(double amount){
    paymentDelay();
    cout<<"Received "<<fixed<<setprecision(2)<<amount<<" in cash. Payment successful!"<<endl;
    cout<<"Thank you!"<<endl;
}

void ebankingPayment::process(double amount){
    string accNumber;
    string pin;
    cout<<"\nEnter your bank account number: ";
    cin>>accNumber;
    cout<<"Enter your PIN: ";
    cin>>pin;
    paymentDelay();
    cout<<"Received "<<fixed<<setprecision(2)<<amount<<" via e-banking. \nThank you!"<<endl;
}