#include "payment.hpp"
#include<iostream>
#include<thread>
#include<chrono>
using namespace std;

static void paymentDelay(){         //help from geeksforgeeks and chatgpt(sleep for method)
    cout<<"Processing payment";
    for(int i=0; i<3; i++){
        cout<<".";
        cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout<<endl;
}

void cashPayment::process(double amount){
    paymentDelay();
    cout<<"Received "<<amount<<" in cash. Payment successful!"<<endl;
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
    cout<<"Received "<<amount<<" via e-banking. \nThank you!"<<endl;
}