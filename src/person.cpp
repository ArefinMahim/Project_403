#include"person.hpp"

//Person Class Functions

        Person::Person():id(0), firstName(""), lastName(""), phone(""), email(""), address("") {}

        Person::Person(int id, string firstName, string lastName, string phone, string email, string address)
            :id(id), firstName(firstName), lastName(lastName), phone(phone), email(email), address(address) {}
        

        // Getters

        int Person::getId() const { return id; }
        string Person::getFirstName() const { return firstName; }
        string Person::getLastName() const { return lastName; }
        string Person::getPhone() const { return phone; }
        string Person::getEmail() const { return email; }
        string Person::getAddress() const { return address;}
        string Person::getFullName() const { return firstName + " " + lastName; }

        // Setters
        void Person::setId(int newId)
        {
            id=newId;
        }

        void Person::setFirstName(const string Fname)
        {
            firstName=Fname;
        }

        void Person::setLastName(const string Lname)
        {
            lastName=Lname;
        }

        void Person::setPhone(const string ph)
        {
            phone=ph;
        }

        void Person::setEmail(const string mail)
        {
            email=mail;
        }

        void Person::setAddress(const string addr)
        {
            address=addr;
        }

        // Display Function

        void Person::DisplayInfo() 
        {
            cout<<"Id: "<<getId()<<"\n";
            cout<<"Name: "<<getFullName()<<"\n";
            cout<<"Phone: "<<getPhone()<<"\n";
            cout<<"Email: "<<getEmail()<<"\n";
            cout<<"Address: "<<getAddress()<<"\n";
        }

