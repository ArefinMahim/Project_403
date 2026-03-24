#ifndef PAGE_HPP
#define PAGE_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Page {

protected:
    int width;

public:
    Page(int w = 80);

    void clear();
    void drawBorder();
    void drawTitle(string title);
    void drawLine(string text, bool centered = false);
    void drawMenu(vector<string> options);

    void buildPage(string title, vector<string> body);
};

#endif