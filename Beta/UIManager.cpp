 #include "UIManager.hpp"
#include <vector>

UIManager::UIManager() : page(80) {}

void UIManager::showWelcomePage() {

    std::vector<std::string> body = {
        "",
        "Welcome to the Hotel Booking System",
        "",
        "1. Login",
        "2. Sign Up",
        "3. Exit"
    };

    page.buildPage("WELCOME PAGE", body);
}

void UIManager::showLoginPage()  {

    std::vector<std::string> body = {
        "",
        "Enter Credentials:",
        "",
        "User ID: __________",
        "Password: __________",
        "",
        "1. Login",
        "2. Back"
    };

    page.buildPage("LOGIN PAGE", body);
}

void UIManager::showProfilePage(int userID,
                                const std::string& tier){

    std::vector<std::string> body = {
        "User ID: " + std::to_string(userID),
        "Membership Tier: " + tier,
        "",
        "1. View Available Hotels",
        "2. View Booked Rooms",
        "3. Logout"
    };

    page.buildPage("PROFILE PAGE", body);
}

void UIManager::showHotelPage(int hotelID,
                              const std::string& name,
                              const std::string& description){

    std::vector<std::string> body = {
        "Hotel ID: " + std::to_string(hotelID),
        "Name: " + name,
        "",
        description,
        "",
        "1. View Rooms",
        "2. Back"
    };

    page.buildPage("HOTEL DETAILS", body);
}