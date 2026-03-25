#ifndef COLOREDPAGE_HPP
#define COLOREDPAGE_HPP

#include "Page.hpp"

class ColoredPage : public Page {
public:
    explicit ColoredPage(int w = 80);

    void setColor(const std::string& colorCode) const;
    void resetColor() const;
};

#endif