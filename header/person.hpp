#pragma once 

#include"utility.hpp"
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
        
        Person();

        Person(int id, string firstName, string lastName, string phone, string email, string address);
        

        virtual ~Person()=default;

        // Getters

        int getId() const;
        string getFirstName() const;
        string getLastName() const;
        string getPhone() const;
        string getEmail() const;
        string getAddress() const;
        string getFullName() const;

        // Setters
        void setId(int newId);

        void setFirstName(const string Fname);

        void setLastName(const string Lname);

        void setPhone(const string ph);

        void setEmail(const string mail);

        void setAddress(const string addr);

        // Display Function

        virtual void DisplayInfo();

};

