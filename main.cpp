#include "header/hotelsystem.hpp"
#include "header/ui.hpp"
 
using namespace std;
 
int main() {
    srand(time(NULL));   
 
    HotelSystem sys;     
    UI ui(sys);
    ui.run();           
 
    return 0;
}