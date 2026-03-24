#include"utility.hpp"
#include"days.hpp"
using namespace std;

Days::Days():date(1), month(1), year(2000){}
Days::Days(int d, int m, int y){
    setDate(d,m,y);
}

bool Days::isLeapYear(int y) const{
    return ((y%4==0 && y%100!=0) || (y%400==0));
}
int Days::monthDays(int m, int y) const{
    static int month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(m==2 && isLeapYear(y)) return 29;
    return month[m-1];
}
void Days::setDate(int d, int m, int y){
    if(m<1 || m>12 || y<2000 || d<1 || d>monthDays(m,y)) throw runtime_error("Invalid date");
    date=d;
    month=m;
    year=y;
}
void Days::addDays(int d){
    while(d>0){
        int daysLeftinMonth=monthDays(month,year)-date;
        if(d>daysLeftinMonth){
            d=d-(daysLeftinMonth+1);
            date=1;
            month++;
            if(month>12){
                month=1;
                year++;
            }
        }
        else{
            date+=d;
            d=0;
        }
    }
}
int Days::noOfDays(const Days& toDate) const{
    Days fromDate=*this;
    Days endDate=toDate;
    int totalDays=0;
    if(fromDate.year>endDate.year ||
      (fromDate.year==endDate.year && fromDate.month>endDate.month) ||
      (fromDate.year==endDate.year && fromDate.month==endDate.month && fromDate.date>endDate.date)){
        return -1; //end date < startrt date
    }
    if(fromDate.year==endDate.year && fromDate.month==endDate.month){
        return endDate.date-fromDate.date;
    }
    totalDays+=monthDays(fromDate.month,fromDate.year)-fromDate.date;
    int currentMonth=fromDate.month+1;
    int currentYear=fromDate.year;
    if(currentMonth>12){
        currentMonth=1;
        currentYear++;
    }
    while(currentYear<endDate.year || (currentYear==endDate.year && currentMonth<endDate.month)){
        totalDays+=monthDays(currentMonth,currentYear);
        currentMonth++;
        if(currentMonth>12){
            currentMonth=1;
            currentYear++;
        }
    }
    totalDays+=endDate.date;
    return totalDays;
}
ostream& operator<<(ostream &os, const Days &d){
    os<<d.date<<"/"<<d.month<<"/"<<d.year;
    return os;
}
Days Days::operator++(int){
    Days temp=*this;
    addDays(1);
    return temp;
}
Days Days::operator--(int){
    Days temp=*this;
    date--;
    if(date<1){
        month--;
        if(month<1){
            month=12;
            year--;
        }
        date=monthDays(month, year);
    }
    return temp;
}

Days stringToDate(const string &s){
    int d,m,y;
    char slash1, slash2;
    stringstream ss(s);
    ss>>d>>slash1>>m>>slash2>>y;
    if(ss.fail() || slash1!='-' || slash2!='-') throw runtime_error("Invalid date format");
    return Days(d,m,y);
}

Days::~Days(){}