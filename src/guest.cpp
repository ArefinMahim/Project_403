#include "guest.hpp"
#include <ctime>

// Return current date as formatted setting
static string todayString() {
    time_t t = time(NULL);
    tm *now = localtime(&t);
    char buf[12];
    snprintf(buf, sizeof(buf), "%02d-%02d-%04d", now->tm_mday, now->tm_mon + 1,
             now->tm_year + 1900);

    return string(buf);
}

// Guest Class Functions
Guest::Guest()
    : Person(), nid(""), roomNo(0), checkInDate(""), checkOutDate(""),
      username(""), passwordHash(""), profileCreatedDate(todayString()),
      tier(MemberTier::BRONZE) {}

Guest::Guest(int Pid, string first, string last, string ph, string mail,
             string addr, string Nid, int room, string checkin, string checkout)
    : Person(Pid, first, last, ph, mail, addr), nid(Nid), roomNo(room),
      checkInDate(checkin), checkOutDate(checkout), username(""),
      passwordHash(""), profileCreatedDate(todayString()),
      tier(MemberTier::BRONZE) {}

Guest::Guest(int Pid, string first, string last, string ph, string mail,
             string addr, string Nid, string uname, string password)
    : Person(Pid, first, last, ph, mail, addr), nid(Nid), roomNo(0),
      checkInDate(""), checkOutDate(""), username(uname),
      passwordHash(to_string(hashPassword(password))),
      profileCreatedDate(todayString()), tier(MemberTier::BRONZE) {}

// Getters
string Guest::getNid() const { return nid; }
int Guest::getRoomNo() const { return roomNo; }
string Guest::getCheckInDate() const { return checkInDate; }
string Guest::getCheckOutDate() const { return checkOutDate; }

// Setters
void Guest::setNid(const string Nid) { nid = Nid; }
void Guest::setRoomNo(const int RoomNo) { roomNo = RoomNo; }
void Guest::setCheckInDate(const string CheckInDate) {
    checkInDate = CheckInDate;
}
void Guest::setCheckOutDate(const string CheckOutDate) {
    checkOutDate = CheckOutDate;
}

// login getter
string Guest::getUsername() const { return username; }
string Guest::getPasswordHash() const { return passwordHash; }
string Guest::getProfileCreated() const { return profileCreatedDate; }
MemberTier Guest::getTier() const { return tier; }
const vector<BookingRecord> &Guest::getBookingHistory() const {
    return bookingHistory;
}

// login setter
void Guest::setPasswordHashRaw(const string &hash) { passwordHash = hash; }
void Guest::setProfileCreated(const string &date) { profileCreatedDate = date; }
void Guest::setTier(MemberTier t) { tier = t; }
bool Guest::verifyPassword(const string &pw) const {
    return passwordHash == to_string(hashPassword(pw));
}
void Guest::changePassword(const string &newPw) {
    passwordHash = to_string(hashPassword(newPw));
}

void Guest::addBookingRecord(const BookingRecord &b) {
    bookingHistory.push_back(b);
    int total = (int)bookingHistory.size();
    if (total >= 10)
        tier = MemberTier::PLATINUM;
    else if (total >= 5)
        tier = MemberTier::GOLD;
    else if (total >= 2)
        tier = MemberTier::SILVER;
    else
        tier = MemberTier::BRONZE;
}

void Guest::addBookingRaw(const BookingRecord &b) {
    bookingHistory.push_back(b);
}

// Display Guest Information
void Guest::DisplayInfo() {
    Person::DisplayInfo();
    cout << "NID: " << getNid() << endl;
    if (roomNo > 0)
        cout << "Room No: " << getRoomNo() << endl;
    if (!checkInDate.empty())
        cout << "Check-In-Date: " << getCheckInDate() << endl;
    if (!checkOutDate.empty())
        cout << "Chech-Out-Date: " << getCheckOutDate() << endl;

    if (!username.empty()) {
        cout << "Username: " << username << endl;
        cout << "Member Since: " << profileCreatedDate << endl;
        cout << "Member Tier: " << tierName(tier) << endl;
        cout << "Total Bookings: " << bookingHistory.size() << endl;
    }

    if (!bookingHistory.empty()) {
        cout << endl;
        cout << "--Booking History--" << endl;

        for (auto &b : bookingHistory) {
            cout << "[ " << (b.active ? "ACTIVE" : "PAST") << " ]"
                 << b.hotelName << " Room " << b.roomID << " (" << b.roomType
                 << ")"
                 << " " << b.checkIn << " -> " << b.chechOut << " $"
                 << (int)b.totalCost << endl;
        }
    }
}