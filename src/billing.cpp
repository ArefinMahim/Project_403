#include "billing.hpp"
#include "payment.hpp"

template <typename T> T getValidInput() {
    T val;
    if (!(cin >> val)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Invalid input type.");
    }
    return val;
}

Booking::Booking(Hotel *h, Room *r, int n)
    : hotel(h), room(r), nights(n), totalPrice(0.0), discountedPrice(0.0),
      discountAmount(0), discountPercent(0) {}
// use srand(time(NULL)) in main
Booking::~Booking() {}

Room *Booking::getRoom() const { return room; }
Hotel *Booking::getHotel() const { return hotel; }
int Booking::getNights() const { return nights; }
double Booking::getTotalPrice() const { return totalPrice; }
double Booking::getDiscountedPrice() const { return discountedPrice; }
double Booking::getDiscountAmount() const { return discountAmount; }
int Booking::getDiscountPercent() const { return discountPercent; }

// Setters
void Booking::setRoom(Room *r) { room = r; }
void Booking::setHotel(Hotel *h) { hotel = h; }
void Booking::setNights(const Days &checkIn, const Days &checkOut) {
    int stayedNights = checkIn.noOfDays(checkOut);
    if (stayedNights < 0) {
        cerr << "Date error: Checkout date must be after checkin." << endl;
        nights = 0;
        return;
    }
    checkInDate = checkIn;
    checkOutDate = checkOut;
    nights = stayedNights;
}

void Booking::calculateTotalPrice() {
    if (!room)
        throw runtime_error(
            "The room is not set, failed to calculate total price.");
    totalPrice = room->calculate_total_price() * nights;
    discountedPrice = totalPrice;
    cout << left << setw(20) << "Total Price" << ": " << fixed
         << setprecision(2) << totalPrice << endl;
}
void Booking::applyVoucher() {
    if (totalPrice <= 0) {
        cout << "Error calculating total price. Cannot apply voucher." << endl;
        return;
    }

    char choice;
    cout<<endl;
    cout << "Do you want to apply a voucher?(y/n): ";
    choice = getValidInput<char>();
    if (choice == 'n' || choice == 'N') {
        return;
    }

    int attempts = 3;
    while (attempts > 0) {
        string voucher;
        cout << "Enter voucher code: ";
        cin >> voucher;
        if (voucher == "FABIAN" || voucher == "ISHMAM" ||
            voucher == "SIDDIQUE" || voucher == "MAHIM" ||
            voucher == "ABOUBAKAR") {
            discountPercent = (rand() % 50) + 1;
            discountAmount = totalPrice * (discountPercent / 100.0);
            discountedPrice = totalPrice - discountAmount;
            cout << "Voucher applied successfully! You got " << discountPercent
                 << "% discount." << endl;
            cout << left << setw(20) << "Discount Amount" << ": " << fixed
                 << setprecision(2) << discountAmount << endl;
            break;
        } else {
            attempts--;
            cout << "Invalid voucher code. Attempts left: " << attempts << endl;
            if (attempts == 0) {
                cout << "No attempts left. Proceeding without voucher.\n";
                return;
            }
            cout << "Do you want to try again? (y/n): ";
            choice = getValidInput<char>();
            if (choice == 'n' || choice == 'N') {
                return;
            }
        }
    }
}
string Booking::roomTypename() const {
    switch (room->get_type()) {
    case Economy:
        return "Economy";
    case Standard:
        return "Standard";
    case Premium:
        return "Premium";
    default:
        return "Unknown";
    }
}
void Booking::checkout() {
    try {
        if (!room || !hotel)
            throw runtime_error("Invalid booking details.");
        if (nights <= 0)
            throw runtime_error("Invalid number of nights.");
        if (room->get_book_status())
            throw runtime_error(
                "Room is already booked. Cannot proceed with checkout.");

        calculateTotalPrice();
        applyVoucher();

        cout<<endl;
        cout << "-----CHECKOUT-----" << endl;
        cout << left << setw(20) << "Hotel Name" << ": " << hotel->get_name()
             << endl;
        cout << left << setw(20) << "Room Type" << ": " << roomTypename()
             << endl;
        cout << left << setw(20) << "Number of Nights" << ": " << nights
             << endl;
        cout << left << setw(20) << "Total Price" << ": " << fixed
             << setprecision(2) << totalPrice << endl;
        cout << left << setw(20) << "Discount Amount" << ": " << discountAmount
             << endl;
        cout << left << setw(20) << "Final Price" << ": " << discountedPrice
             << endl;

        paymentMethod();
    } catch (const exception &e) {
        cerr << "Error during checkout: " << e.what() << endl;
    }
}
void Booking::paymentMethod() {
    int choice;
    Payment *payment = NULL;
    while (true) {
        cout << "\nSelect payment method:" << endl;
        cout << "1. Cash" << endl;
        cout << "2. E-banking" << endl;
        choice = getValidInput<int>();
        if (choice == 1) {
            payment = new cashPayment();
            break;
        } else if (choice == 2) {
            payment = new ebankingPayment();
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    if (payment) {
        payment->process(discountedPrice);
        room->set_book_status(true);
        delete payment;
    }
}