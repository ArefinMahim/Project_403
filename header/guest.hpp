#pragma once
#include "person.hpp"
using namespace std;

enum class MemberTier { BRONZE = 0, SILVER, GOLD, PLATINUM };

inline string tierName(MemberTier t) {
    switch (t) {
    case MemberTier::BRONZE:
        return "Bronze";
    case MemberTier::SILVER:
        return "Silver";
    case MemberTier::GOLD:
        return "Gold";
    case MemberTier::PLATINUM:
        return "Platinum";
    }

    return "Unknown";
}

struct BookingRecord {
    string hotelName;
    string roomID;
    string roomType;
    string checkIn;
    string chechOut;
    double totalCost;
    bool active;
};

class Guest : public Person {
  private:
    string nid;
    int roomNo;
    string checkInDate;
    string checkOutDate;

    // Login
    string username;
    string passwordHash;
    string profileCreatedDate;
    MemberTier tier;
    vector<BookingRecord> bookingHistory;

    static size_t hashPassword(const string &password) {
        size_t h = 5381;
        for (char c : password)
            h = ((h << 5) + h) + (unsigned char)c;

        return h;
    }

  public:
    // Constructors

    Guest();
    Guest(int Pid, string first, string last, string ph, string mail,
          string addr, string Nid, int room, string checkin, string checkout);

    Guest(int Pid, string first, string last, string ph, string mail,
          string addr, string Nid, string username, string password);
    
    // Virtual Destructor which will be overridden
    ~Guest() = default;

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

    // login getter
    string getUsername() const;
    string getPasswordHash() const;
    string getProfileCreated() const;
    MemberTier getTier() const;
    const vector<BookingRecord> &getBookingHistory() const;

    // login setter
    void setPasswordHashRaw(const string &hash);
    void setProfileCreated(const string &date);
    void setTier(MemberTier t);
    bool verifyPassword(const string &pw) const;
    void changePassword(const string &newPw);
    void addBookingRecord(const BookingRecord &b);
    void addBookingRaw(const BookingRecord &b);

    // Display Guest Information
    void DisplayInfo() override;
};