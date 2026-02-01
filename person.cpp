#pragma once 
#include"utility.cpp"
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
        
        Person():id(0), firstName(""), lastName(""), phone(""), email(""), address("") {}

        Person(int id, string firstName, string lastName, string phone, string email, string address)
            :id(id), firstName(firstName), lastName(lastName), phone(phone), email(email), address(address) {}
        

        virtual ~Person()=default;

        // Getters

        int getId() const { return id; }
        string getFirstName() const { return firstName; }
        string getLastName() const { return lastName; }
        string getPhone() const { return phone; }
        string getEmail() const { return email; }
        string getAddress() const { return address;}
        string getFullName() const { return firstName + " " + lastName; }

        // Setters
        void setId(int newId)
        {
            id=newId;
        }

        void setFirstName(const string Fname)
        {
            firstName=Fname;
        }

        void setLastName(const string Lname)
        {
            lastName=Lname;
        }

        void setPhone(const string ph)
        {
            phone=ph;
        }

        void setEmail(const string mail)
        {
            email=mail;
        }

        void setAddress(const string addr)
        {
            address=addr;
        }

        // Display Function

        virtual void DisplayInfo() 
        {
            cout<<"Id: "<<getId()<<"\n";
            cout<<"Name: "<<getFullName()<<"\n";
            cout<<"Phone: "<<getPhone()<<"\n";
            cout<<"Email: "<<getEmail()<<"\n";
            cout<<"Address: "<<getAddress()<<"\n";
        }

};

