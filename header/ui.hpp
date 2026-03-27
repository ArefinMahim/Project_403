#pragma once
#include "hotelsystem.hpp"
#include "utility.hpp"
#include <iomanip>
#include <limits>
using namespace std;

// ANSI color
namespace C {
static const string RST = "\033[0m"; // reset formatting
static const string BOLD = "\033[1m";
static const string RED = "\033[91m";
static const string GRN = "\033[92m";
static const string YEL = "\033[93m";
static const string BLU = "\033[94m";
static const string MAG = "\033[95m";
static const string CYN = "\033[96m";
static const string WHT = "\033[97m";
static const string GRY = "\033[90m";
} // namespace C

class UI {
  private:
    HotelSystem &sys;
    Guest* currentGuest;
    Admin* currentAdmin;
    static const int W = 62;

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void line(char c = '=') {
        cout << C::CYN << string(W, c) << C::RST << endl;
    }

    void header(const string &title, const string &col = C::CYN) {
        cout << endl;
        cout << col << string(W, '=') << C::RST << endl;
        int pad = (W - (int)title.size()) / 2;
        cout << col << "|" << string(pad - 1, ' ') << C::BOLD << title << C::RST
             << col << string(W - pad - (int)title.size() - 1, ' ') << "|"
             << C::RST << endl;
        cout << col << string(W, '=') << C::RST << endl;
    }

    void dubheader(const string &t, const string &col = C::YEL) {
        cout << col << string(W, '-') << C::RST << endl;
        cout << col << " " << t << C::RST << endl;
        cout << col << string(W, '-') << C::RST << endl;
    }

    void info(const string &label, const string &val, const string &lc = C::CYN,
              const string &vc = C::WHT) {
        cout << " " << lc << left << setw(22) << label << C::RST << vc << val
             << C::RST << endl;
    }

    void opt(int n, const string &text, const string &col = C::WHT) {
        cout << " " << C::CYN << "[" << n << "]" << col << text << C::RST
             << endl;
    }

    void ok(const string &msg) {
        cout << endl;
        cout << C::GRN << "[OK] " << msg << C::RST << endl << endl;
    }

    void err(const string &msg) {
        cout << endl;
        cout << C::RED << "[ERROR] " << msg << C::RST << endl << endl;
    }

    void warn(const string &msg) {
        cout << endl;
        cout << C::YEL << "[WARNING] " << msg << C::RST << endl << endl;
    }

    string prompt(const string &label) {
        cout << endl;
        cout << C::YEL << label << " : " << C::WHT;
        string s;
        getline(cin, s);
        return trim(s);
    }

    string trim(const string &s) {
        size_t b = s.find_first_not_of(" \t\r\n");
        size_t e = s.find_last_not_of(" \t\r\n");
        return (b == string::npos) ? "" : s.substr(b, e - b + 1);
    }

    int getInt(const string &label, int lo, int hi) {
        while (true) {
            string s = prompt(label);
            try {
                int v = stoi(s);
                if (v >= lo && v <= hi)
                    return v;
            } catch (...) {
            }
            err("Enter a number between " + to_string(lo) + " and " +
                to_string(hi));
        }
    }

    void pause() {
        cout << endl;
        cout << C::GRY << "[ Press ENTER to continue ]" << C::RST << endl;
    }

    // Parse Days date from user input "dd/mm/yyyy"
    Days promptDate(const string &label) {
        while (true) {
            string s = prompt(label + " (DD/MM/YYYY) ");
            if (s.size() == 10 && s[2] == '/' && s[5] == '/') {
                try {
                    int d = stoi(s.substr(0, 2));
                    int m = stoi(s.substr(3, 2));
                    int y = stoi(s.substr(6, 4));
                    if (d >= 1 && d <= 31 && m >= 1 && m <= 12 && y > 2025)
                        return Days(d, m, y);
                } catch (...) {
                }
            }
            err("Invalid Date. Use DD/MM/YYYY");
        }
    }

    string roomTypeName(int t) {
        if (t == Economy)
            return "Economy";
        if (t == Standard)
            return "Standard";
        return "Premimum";
    }

    //display star
    string starDisplay(int rating) {
        string s = "";
        for (int i = 1; i <= 3; i++)
            s += (i <= rating) ? "★" : "☆";
        return s;
    }

    // Welcome Page
    bool showWelcomePage() {
        clearScreen();
        header("WELCOME TO PROJECT_403", C::CYN);
        cout << endl;
        cout << C::WHT << "We present you with a Hotel Booking System" << C::RST
             << endl
             << endl;

        opt(1, "Login");
        opt(2, "Sign Up");
        opt(0, "Exit", c::RED);
        cout << endl;

        int c = getInt("Choice", 0, 2);
        if (c == 0)
            return false;
        if (c == 1)
            return showLoginPage();
        if (c == 2)
            return showSignUpPage();

        return true;
    }

    // Sign Up page
    void showSignUpPage() {
        clearScreen();
        header("CREATE ACCOUNT", C::GRN);

        string first = prompt("First Name");
        string last = prompt("Last Name");
        string phone = prompt("Phone Number");
        string email = prompt("Email");
        string address = prompt("Address");
        string nid = prompt("NID");
        string username = prompt("Username");
        string pw = prompt("Password");
        string pw2 = prompt("Confirm Password");

        if (first.empty() || username.empty() || pw.empty()) {
            err("All fields are required!");
            pause();
            return;
        }

        if (pw != pw2) {
            err("Passwords do not match");
            pause();
            return;
        }

        if (sys.usernameExists(username)) {
            err("Username already taken. Try another.");
            pause;
            return;
        }

        sys.registerGuest(first, last, phone, email, address, nid, username,
                          pw);
        ok("Account Created! Please Log in.");
        pause();
    }

    // login page
    void showLoginPage() {
        clearScreen();
        header("LOGIN", C::CYN);

        string uname = prompt("Username");
        string pw = prompt("Password");

        // admin login
        auto admin = sys.loginAdmin(uname, pw);
        if (admin) {
            currentAdmin = admin;
            currentGuest = NULL;
            showAdminPage();
            currentAdmin = NULL;
            return;
        }

        // guest login
        auto guest = sys.loginGuest(uname, pw);
        if (guest) {
            currentGuest = guest;
            currentAdmin = NULL;
            showProfilePage();
            currentGuest = NULL;
            return;
        }
        err("Invalid unsername or password");
        pause();
    }

    // admin
    void showAdminPage() {
        while (true) {
            clearScreen();
            header("ADMIN", C::MAG);
            info("Username", currentAdmin->getUsername());
            info("Name", currentAdmin->getFullName());
            cout << endl;

            opt(1, "View all Hotels and Rooms");
            opt(2, "Add Hotel");
            opt(3, "Remove Hotel");
            opt(4, "View all Guests");
            opt(5, "Remove Guest");
            opt(6, "Cancel a Booking");
            opt(0, "Logout", C::RED);
            cout << end;
        }

        int c = getInt("Choice", 0, 6);
        if (c == 0)
            break;
        if (c == 1)
            adminViewHotels();
        if (c == 2)
            adminAddHotel();
        if (c == 3)
            adminRemoveHotel();
        if (c == 4)
            adminViewGuests();
        if (c == 5)
            adminRemoveGuest();
        if (c == 6)
            adminCancelBooking();
    }

    void adminViewHotels() {
        clearScreen();
        header("ALL HOTELS", C::GRN);
        for (auto &h : sys.getHotels()) {
            subheader(starDisplay(h->get_star_rating())+" "+h->getName() + " | " + h->get_location());
            info("Amenities", h->get_amenities());
            
            int free = 0;
            for (auto *r : h->get_rooms())
                if (!r->get_book_status())
                    free++;
            info("Rooms", to_string(h->get_rooms().size()) + " total, " +
                              to_string(free) + "free");

            cout << endl;
            cout << C::BOLD << left << setw(14) << "Room ID" << setw(12)
                 << "Type" << setw(10) << "Price" << endl;
            cout << "Status" << : C::RST << endl;
            line('-');

            for (auto r* : h->get_rooms()) {
                string status =
                    r->get_book_status()
                        ? C::RED + "[BOOKED] by " + r->get_booker_ID() + C::RST
                        : C::GRN + "[FREE]" + C::RST;
            }
        }
        pause();
    }

    void adminAddHotel() {
        clearScreen();

        header("ADD HOTEL", C::GRN);
        string name = prompt("Hotel Name");
        string loc = prompt("Location");

        if (name.empty()) {
            err("Name cannot be empty.");
            pause();
            return;
        }

        //ask for star rating
        cout << endl;
        opt(1, " 1-Star  (WiFi, Parking)");
        opt(2, " 2-Star  (WiFi, Parking, Breakfast)");
        opt(3, " 3-Star  (WiFi, Parking, Breakfast, Pool, Spa)");
        cout << endl;
        int stars = getInt("Select Star Rating", 1, 3);

        sys.addHotel(name, loc);
        auto h=sys.findHotel(name);

        if(h) h->set_star_rating(stars);
        ok("Hotel \"" + name +
           "\" added with 10 rooms (4 Economy, 4 Standard, 2 Premium)");
        pause();
    }

    void adminRemoveHotel() {
        clearScreen();

        header("REMOVE HOTEL", C::RED);
        string name = prompt("Hotel name to remove");

        if (!sys.findHotel(name)) {
            err("Hotel not found");
            pause();
            return;
        }

        sys.removeHotel(name);
        ok("Hotel removed");
        pause();
    }

    void adminViewGuest() {
        clearScreen();

        header("ALL GUESTS", C::CYN);
        auto &guests = sys.getGuests();
        if (guests.empty()) {
            warn("No registered guests yet");
            pause();
            return;
        }

        for (auto &g : guests) {
            line('-');
            info("Name", g->getFullName());
            info("Username", g->getUsername());
            info("Email", g->getEmail());
            info("Phone", g->getPhone());
            info("NID", g->getNid());
            info("Tier", tierName(g->getTier()));
            info("Bookings", to_string(g->getBookingHistory().size()).size());
        }

        line();
        pause();
    }

    void adminRemoveGuest() {
        clearScreen();

        header("REMOVE GUEST", C::RED);
        string uname = prompt("Guest username to remove");

        if (!sys.findGuest(uname)) {
            err("Guest not found");
            pause();
            return;
        }

        sys.removeGuest(uname);
        ok("Guest removed");
        pause();
    }

    void adminCancelBooking() {
        clearScreen();

        header("CANCEL ROOM BOOKING", C::YEL);
        string hname = prompt("Hotel Name");
        auto hotel = sys.findHotel(hname);

        if (!hotel) {
            err("Hotel not found");
            pause();
            return;
        }

        string roomID = prompt("Room ID");
        Room *r = hotel->find_room(roomID);

        if (!r) {
            err("Room not found");
            pause();
            return;
        }

        if (!r->get_book_status()) {
            warn("Room is not currently booked");
            pause();
            return;
        }

        sys.cancelRoomBooking(hotel, roomID);
        ok("Booking for room " + roomID + "has been cancelled");
        pause();
    }

    // guest page
    void showProfilePage() {
        while (true) {
            clearScreen();

            header("GUEST PROFILE", C::CYN);
            info("Name", currentGuest->getFullName());
            info("Username", currentGuest->getUserame());
            info("Email", currentGuest->getEmail());
            info("Phone", currentGuest->getPhone());
            info("Address", currentGuest->getAddress());
            info("NID", currentGuest->getNid());
            info("Memeber Since", currentGuest->getProfileCreated());
            info("Memeber Tier", tierName(currentGuest->getTier()));
            info("Name", to_string(currentGuest->getBookingHistory()));

            auto &hist = currentGuest->getBookingHistory();
            if (!hist.empty()) {
                subheader("BOOKING HISTORY", C::YEL);

                for (auto &b : hist) {
                    string tag = b.active ? C::GRN + "[ACTIVE]" + C::RST
                                          : C::RED + "[PAST]" + C::RST;

                    cout << " " << tag << " " << C::CYN << b.hotelName << C::RST
                         << " Room " << b.roomID << " (" << b.roomTypeMM << ")"
                         << " " << b.checkIn << " -> " << b.checkOut << " $"
                         << (int)b.totalCost << endl;
                }
            }

            cout << endl;
            opt(1, "Browse & Book Hotels");
            opt(0, "Logout");
            cout << endl;

            int c = getInt("Choice", 0, 1);
            if (c == 0)
                break;
            if (c == 1)
                showAvailableHotelsPage();
        }
    }

    // available hotels
    void showAvailableHotelsPage() {
        clearScreen();

        header("AVAILABLE HOTELS", C::GRN);
        auto &hotels = sys.getHotels();
        for (int i = 0; i < (int)hotels.size(); i++) {
            auto &h = hotels[i];
            int freee = 0;

            for (auto *t : h->get_rooms())
                if (!r->get_book_status())
                    free++;

            cout << " " << C::CYN << "[" << (i + 1) << "]"
                 << C::BOLD << h->get_name() << C::RST
                 << " " << C::YEL << starDisplay(h->get_star_rating()) << C::RST
                 << " " << C::GRY << h->get_location() << C::RST
                 << " " << C::GRN << to_string(free) << " rooms free"
                 << C::RST << endl;
            cout <<" "<<C::GRY<<h->get_amenities()<<C::RST<<endl;
        }

        cout << endl;
        opt(0, "Back to Profile", C::RED);
        cout << endl;

        int c = getInt("Select Hotel (0 to go back)", 0, (int)hotels.size());
        if (c == 0)
            return;
        showParticularHotelPage(hotels[c - 1]);
    }

    // particular hotel page
    void showParticularHotelPage(Hotel* hotel) {
        while (true) {
            clearScreen();

            header(hotel->get_name() + " " + starDisplay(hotel->get_star_rating()), C::GRN);
            info("Location", hotel->get_location());
            info("Amenities", hotel->get_amenities());
            cout << endl;

            subheader("ROOMS", C::CYN);
            cout << " " << C::BOLD << left << setw(14) << "Room ID" << setw(12)
                 << "Type" << setw(12) << "Price/Night" << setw(8) << "Guests"
                 << "Status" << C::RST << endl;

            line('-');
            for (auto *r : hotel->get_rooms()) {
                string status = r->get_book_status()
                                    ? C::RED + "[BROKEN]" + C::RST
                                    : C::GRN + "[FREE]" + C::RST;
                cout << "  " << C::CYN << left << setw(14) << r->get_room_ID()
                     << C::WHT << setw(12) << roomTypeName(r->get_type())
                     << setw(12) << ("$" + to_string((int)r->get_base_price()))
                     << setw(8) << r->get_guest_count() << status << endl;
            }

            line('-');
            cout << endl;
            opt(1, "Select a Room to Book");
            opt(0, "Back to Hotels", C::RED);
            cout << endl;

            int c = getInt("Choice", 0, 1);
            if (c == 0)
                return;

            string roomID = promt("Enter Room ID");
            Room *room = hotel->find_room(roomID);

            if (!room) {
                err("Room not found");
                pause();
                continue;
            }

            if (room->get_book_status()) {
                err("Room is already booked");
                pause();
                continue;
            }

            showIndividualRoomPage(hotel, room);
        }
    }

    // individual room page
    void showIndividualRoomPage(Hotel* hotel, Room *room) {
        clearScreen();

        header("ROOM DETAILS", C::YEL);
        info("Room ID", room->get_room_ID());
        info("Type", roomTypeName(room->get_type()));
        info("Base Price",
             "$" + to_string((int)room->get_base_price()) + " / night");
        info("Max Guests", to_string(room->get_guest_count()));
        info("Description", room->get_description());
        info("Status", room->get_book_status() ? "BOOKED" : "FREE");

        // room specific details
        if (room->get_type() == Standard) {
            Standard_room *sr = dynamic_cast<Standard_room *>(room);

            if (sr) {
                auto privs = sr->get_all_privilages();
                string ps;

                for (auto &p : privs)
                    ps += p + " ";
                info("Privilages", ps);
            }
        } else if (room->get_type() == Premium) {
            Premium_room *pr = dynamic_cast<Premium_room *>(room);
            if (pr) {
                string conns;
                for (auto &s : pr->get_connections())
                    conns += s + "  ";
                info("Connected to", conns);
                info("Dedicated Staff",
                     pr->get_dedicated_staff() ? "Yes" : "No");
            }
        } else {
            Economy_room *er = dynamic_cast<Economy_room *>(room);
            if (er) {
                info("Window", er->get_window() ? "Yes" : "No");
                info("Shared WiFi", er->get_shared_wifi() ? "Yes" : "No");
                info("Private Facilities",
                     er->get_private_facilities() ? "Yes" : "No");
            }
        }

        cout << endl;
        opt(1, "Book this room");
        opt(0, "Back", C::RED);
        cout << endl;

        int c = getInt("Choice", 0, 1);
        if (c == 0)
            return;
        showCheckoutPage(hotel, room);
    }

    // checkout
    void showCheckOutPage(Hotel* hotel, Room *room) {
        clearScreen();

        header("CHECKOUT & CONFIRMATION", C::MAG);

        Days checkIn = promptDate("Check-In Date");
        Days checkOut = promptDate("Check-Out Date");

        int nights = checkIn.noOfDays(checkOut);
        if (nights <= 0) {
            err("Check-out must be after check-in");
            pause();
            return;
        }

        // create booking via hotel system
        Booking *booking = sys.createBooking(
            currentGuest, hotel, room->get_room_ID(), chcekIn, checkOut);
        if (!booking) {
            err("Booking failed. Room not available");
            pause();
            return;
        }

        booking->checkout();

        if (room->get_book_status) {
            sys.confirmBooking(currentGuest, hotel, room, checkIn, checkOut,
                               booking->getDiscountedPrice());
            ok("Booking Confirmed! Enjoy your stay at " + hotel)
        } else {
            warn("Payment was not completed. Booking not confirmed");
        }

        delete booking;
        pause();
    }

  public:
    explicit UI(HotelSysytem &s) : sys(s) {}

    void run() {
        while (showWelcomePage()) {
        }
        header("Goodbye!", C::CYN);
        cout << endl;
        cout << "Thank you for using Project_403!" << endl;
    }
};