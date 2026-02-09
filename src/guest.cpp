#include "guest.hpp"


//Guest Class Functions

    Guest::Guest(): Person(), nid(""), roomNo(0), checkInDate(""), checkOutDate("") {}

    Guest::Guest(int Pid, string first, string last, string ph, string mail, string addr, string Nid, int room, string checkin, string checkout)
    : Person(Pid, first, last, ph, mail, addr), nid(Nid), roomNo(room), checkInDate(checkin), checkOutDate(checkout) {}

    // Getters

    string Guest::getNid() const
    {
        return nid;
    }

    int Guest::getRoomNo() const
    {
        return roomNo;
    }

    string Guest::getCheckInDate() const
    {
        return checkInDate;
    }

    string Guest::getCheckOutDate() const
    {
        return checkOutDate;
    }

    // Setters

    void Guest::setNid(const string Nid)
    {
        nid=Nid;
    }

    void Guest::setRoomNo(const int RoomNo)
    {
        roomNo=RoomNo;
    }

    void Guest::setCheckInDate(const string CheckInDate)
    {
        checkInDate=CheckInDate;
    }

    void Guest::setCheckOutDate(const string CheckOutDate)
    {
        checkOutDate=CheckOutDate;
    }

    // Display Guest Information

    void Guest::DisplayInfo()
    {
        Person::DisplayInfo();
        cout<<"NID: "<<getNid()<<"\n";
        cout<<"Room No: "<<getRoomNo()<<"\n";
        cout<<"Check-In Date: "<<getCheckInDate()<<"\n";
        cout<<"Check-Out Date: "<<getCheckOutDate()<<"\n";
    }