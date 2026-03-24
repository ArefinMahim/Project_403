#include "Page.hpp"

Page::Page(int w) {
    width = w;
}

void Page::clear() {
    cout << "\033[2J\033[1;1H";
}

void Page::drawBorder() {
    cout << string(width, '=') << endl;
}

void Page::drawTitle(string title) {
    int padding = (width - title.length()) / 2;
    cout << string(padding, ' ') << title << endl;
}

void Page::drawLine(string text, bool centered) {
    if (centered) {
        int padding = (width - text.length()) / 2;
        cout << string(padding, ' ') << text << endl;
    } else {
        cout << text << endl;
    }
}

void Page::drawMenu(vector<string> options) {
    for (int i = 0; i < options.size(); i++) {
        cout << i + 1 << ". " << options[i] << endl;
    }
}

void Page::buildPage(string title, vector<string> body) {

    clear();
    drawBorder();
    drawTitle(title);
    drawBorder();

    for (int i = 0; i < body.size(); i++) {
        cout << body[i] << endl;
    }

    drawBorder();
}