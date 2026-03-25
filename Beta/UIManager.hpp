#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include "Page.hpp"

class UIManager {
private:
    Page page;

public:
    UIManager();

    void showWelcomePage();
    void showLoginPage() ;
    void showProfilePage(int userID,
                         const std::string& tier);

    void showHotelPage(int hotelID,
                       const std::string& name,
                       const std::string& description);
};

#endif