#include "header/person.hpp"
#include "header/guest.hpp"

using namespace std;

int main()
{
    Person p1(1, "Arefin", "Mahim", "01319998958", "arefinmahim14@gmail.com", "Aftabnagar, Dhaka");
    p1.DisplayInfo();

    Guest g1(2, "Fabian", "Mahdi", "01670165797", " fabianmahdi@gmail.com", "Elephant Road, Dhaka", "12345", 302, "15-01-2026", "20-01-2026");
    g1.DisplayInfo();
    return 0;
}
