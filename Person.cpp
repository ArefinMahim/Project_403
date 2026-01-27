#pragma once 
#include<iostream>
#include<string>
using namespace std;

class Person
{
    protected:
        int id;
        string firstName;
        string lastName;
        string phone;
        string email;
        string address;

    public:
        
        Person():id(0), firstName(""), lastName(""), phone(""), email(""), address("") {

        Person(int id, string firstName, string lastName, string phone, string email, string address)
            :id(id), firstName(firstName), lastName(lastName), phone(phone), email(email), address(address) {}
        
}
