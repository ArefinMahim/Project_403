#include "ColoredPage.hpp"
#include <iostream>

#define RESET  "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[34m"

ColoredPage::ColoredPage(int w) : Page(w) {}

void ColoredPage::setColor(const std::string& colorCode) const {
    std::cout << colorCode;
}

void ColoredPage::resetColor() const {
    std::cout << RESET;
}