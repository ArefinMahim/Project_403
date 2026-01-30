#pragma once

#include "Person.cpp"

using namespace std;

class Guest : public Person
{
    private:
    string nid;
    int roomNo;
    string checkInDate;
    string checkOutDate;

    public:

    // Constructors

    Guest(): Person(), nid(""), roomNo(0), checkInDate(""), checkOutDate("") {}

    Guest(int Pid, string first, string last, string ph, string mail, string addr, string Nid, int room, string checkin, string checkout)
    : Person(Pid, first, last, ph, mail, addr), nid(Nid), roomNo(room), checkInDate(checkin), checkOutDate(checkout) {}

    // Virtual Destructor which will be overridden

    ~Guest()=default;

    // Getters

    string getNid() const
    {
        return nid;
    }

    int getRoomNo() const
    {
        return roomNo;
    }

    string getCheckInDate() const
    {
        return checkInDate;
    }

    string getCheckOutDate() const
    {
        return checkOutDate;
    }

    // Setters

    void setNid(const string Nid)
    {
        nid=Nid;
    }

    void setRoomNo(const int RoomNo)
    {
        roomNo=RoomNo;
    }

    void setCheckInDate(const string CheckInDate)
    {
        checkInDate=CheckInDate;
    }

    void setCheckOutDate(const string CheckOutDate)
    {
        checkOutDate=CheckOutDate;
    }

    // Display Guest Information

    void DisplayInfo() override
    {
        Person::DisplayInfo();
        cout<<"NID: "<<getNid()<<"\n";
        cout<<"Room No: "<<getRoomNo()<<"\n";
        cout<<"Check-In Date: "<<getCheckInDate()<<"\n";
        cout<<"Check-Out Date: "<<getCheckOutDate()<<"\n";
    }


};