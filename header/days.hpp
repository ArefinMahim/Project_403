#pragma once
class Days{
    private:
        int date;
        int month;
        int year;
        bool isLeapYear(int y) const;
        int monthDays(int m, int y) const;
    public:
        Days();
        Days(int d, int m, int y);
        int getDay() const{return date;}
        int getMonth() const{return month;}
        int getYear() const{return year;}
        void setDate(int d, int m, int y);
        void addDays(int d);
        int noOfDays(const Days& toDate) const;
        friend ostream& operator<<(ostream &os, const Days &d);
        Days operator++(int);
        Days operator--(int);
<<<<<<< HEAD
        static Days stringToDate(const string &s);
=======
        Days Days::stringToDate(const string &s);
>>>>>>> bea76e6840dfb4c3047f6e38ecea53d57f49fdf5
        ~Days();
};