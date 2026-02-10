#pragma once
#include "person.hpp"
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

    Guest();
    Guest(int Pid, string first, string last, string ph, string mail, string addr, string Nid, int room, string checkin, string checkout);
    

    // Virtual Destructor which will be overridden

    ~Guest()=default;

    // Getters

    string getNid() const;

    int getRoomNo() const;

    string getCheckInDate() const;

    string getCheckOutDate() const;

    // Setters

    void setNid(const string Nid);

    void setRoomNo(const int RoomNo);

    void setCheckInDate(const string CheckInDate);

    void setCheckOutDate(const string CheckOutDate);

    // Display Guest Information

    void DisplayInfo() override;

};