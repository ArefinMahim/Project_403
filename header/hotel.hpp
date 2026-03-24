#pragma once
#include "rooms.hpp"
#include "utility.hpp"

class Hotel {
  protected:
    int hotel_Id;
    string name;
    string location;
    int stars;
    static vector<int> id;
    vector<Room *> rooms;

  public:
    Hotel(string name, string location, int stars = 1);
    virtual ~Hotel();

    // getter
    int get_id() const;
    string get_name() const;
    string get_location() const;

    // setter
    void set_name(string name);
    void set_location(string location);

    void add_room(Room &room);

    const vector<Room *> &get_rooms() const; // return all rooms
    Room *find_room(const string &roomID);
    Room *find_room(int index);

    virtual int get_star_rating() const { return stars; }
    virtual void set_star_rating(int s) { stars = s; }
    virtual string get_amenities() const { return "Basic ameneties"; }
    virtual void print_details() const;

    // compare hotels by star rating
    bool operator>(const Hotel &other) const { return stars > other.stars; }
    bool operator<(const Hotel &other) const { return stars < other.stars; }
    bool operator==(const Hotel &other) const { return name == other.name; }

    // adding room using << operator
    Hotel &operator<<(Room &room) {
        add_room(room);
        return *this;
    }
};

// one star hotel
class OneStar_Hotel : public Hotel {
  public:
    OneStar_Hotel(string name, string location) : Hotel(name, location, 1) {}

    int get_star_rating() const override { return 1; }

    string get_amenities() const override { return "Wifi, Parking"; }

    void print_details() const override {
        cout << "[1-Star] " << name << " | " << location << endl;
        cout << "Amenities: " << get_amenities() << endl;
        cout << "Rooms: " << rooms.size() << endl;
    }
};

// two star hotel
class TwoStar_Hotel : public Hotel {
  public:
    TwoStar_Hotel(string name, string location) : Hotel(name, location, 2) {}

    int get_star_rating() const override { return 2; }

    string get_amenities() const override { return "Wifi, Parking, Breakfast"; }

    void print_details() const override {
        cout << "[2-Star] " << name << " | " << location << endl;
        cout << "Amenities: " << get_amenities() << endl;
        cout << "Rooms: " << rooms.size() << endl;
    }
};

// three star hotel
class ThreeStar_Hotel : public Hotel {
  public:
    ThreeStar_Hotel(string name, string location) : Hotel(name, location, 3) {}

    int get_star_rating() const override { return 3; }

    string get_amenities() const override {
        return "WiFi, Parking, Breakfast, Pool, Spa";
    }

    void print_details() const override {
        cout << "[3-Star] " << name << " | " << location << endl;
        cout << "Amenities: " << get_amenities() << endl;
        cout << "Rooms: " << rooms.size() << endl;
    }
};