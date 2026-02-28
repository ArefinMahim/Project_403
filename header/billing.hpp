#pragma once
#include"utility.hpp"
#include"rooms.hpp"
#include"hotel.hpp"
#include"days.hpp"
using namespace std;

class Booking{
    private:
        Room* room;
        Hotel* hotel;
        Days checkInDate;
        Days checkOutDate;
        int nights;
        double totalPrice;
        double discountedPrice;
        double discountAmount;
        int discountPercent;
    public:
        Booking(Hotel* h, Room* r, int n);
        ~Booking();

        Room* getRoom() const;
        Hotel* getHotel() const;
        int getNights() const;
        double getTotalPrice() const;
        double getDiscountedPrice() const;
        double getDiscountAmount() const;
        int getDiscountPercent() const;

        //Setters
        void setRoom(Room* r);
        void setHotel(Hotel* h);
        void setNights(const Days& checkIn, const Days& checkOut);

        void calculateTotalPrice();

        void applyVoucher();

        string roomTypename() const;

        void checkout();

        void paymentDelay();

        void paymentMethod();

        void processCash();

        void processEbanking();
};