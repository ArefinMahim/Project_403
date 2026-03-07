#pragma once
#include "hotelsystem.hpp"
#include "utility.hpp"
#include <iomanip>
#include <limits>
using namespace std;

//ANSI color
namespace C{
    static const string RST = "\033[0m";    //reset formatting
    static const string BOLD = "\033[1m";
    static const string RED = "\033[91m";
    static const string GRN = "\033[92m";
    static const string YEL = "\033[93m";
    static const string BLU = "\033[94m";
    static const string MAG = "\033[95m";
    static const string CYN = "\033[96m";
    static const string WHT = "\033[97m";
    static const string GRY = "\033[90m";
}

class UI{
    private:
        HotelSystem& sys;
        shared_ptr<Guest> currentGuest;
        shared_ptr<Admin> currentAdmin;
        static const int W=62;

        void clearScreen(){
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }

        void line(char c = '='){
            cout<<C::CYN<<string(W, c)<<C::RST<<endl;
        }

        void header(const string& title, const string& col = C::CYN){
            cout<<endl;
            cout<<col<< string(W, '=')<<C::RST<<endl;
            int pad = (W - (int)title.size())/2;
            cout<<col<<"|"<<string(pad-1, ' ')
                <<C::BOLD<<title<<C::RST
                <<col<<string(W-pad-(int)title.size()-1, ' ')
                <<"|"<<C::RST<<endl;
            cout<<col<<string(W, '=')<<C::RST<<endl;
        }

        void dubheader(const string& t, const string& col=C::YEL){
            cout<<col<<string(W, '-')<<C::RST<<endl;
            cout<<col<<" "<<t<<C::RST<<endl;
            cout<<col<<string(W, '-')<<C::RST<<endl;
        }

        void info(const string& label, const string& val, const string& lc=C::CYN, const string& vc=C::WHT){
            cout<<" "<<lc<<left<<setw(22)<<label
                <<C::RST<<vc<<val<<C::RST<<endl;
        }

        void opt(int n, const string& text, const string& col=C::WHT){
            cout<<" "<<C::CYN<<"["<<n<<"]"<<col<<text<<C::RST<<endl;
        }

        void ok(const string& msg){
            cout<<endl;
            cout<<C::GRN<<"[OK] "<<msg<<C::RST<<endl<<endl;
        }

        void err(const string& msg){
            cout<<endl;
            cout<<C::RED<<"[ERROR] "<<msg<<C::RST<<endl<<endl;
        }

        void warn(const string& msg){
            cout<<endl;
            cout<<C::YEL<<"[WARNING] "<<msg<<C::RST<<endl<<endl;
        }

        string prompt(const string& label){
            cout<<endl;
            cout<<C::YEL<<label<<" : "<<C::WHT;
            string s;
            getline(cin, s);
            return trim(s);
        }

        string trim(const string& s){
            size_t b=s.find_first_not_of(" \t\r\n");
            size_t e=s.find_last_not_of(" \t\r\n");
            return (b==string::npos) ? "" : s.substr(b, e-b+1);
        }

        int getInt(const string& label, int lb, int hi){
            while(true){
                string s=prompt (label);
                try{
                    int v=stoi=(s);
                    if(v>=lo && v<=hi)  return v;
                }
                catch(...){}
                err("Enter a number between "+to_string(lo)+" and "+to_string(hi));
            }
        }

        void pause(){
            cout<<endl;
            cout<<C::GRY<<"[ Press ENTER to continue ]"<<C::RST<<endl;
        }

        //Parse Days date from user input "dd/mm/yyyy"
        Days promptDate(const string& label){
            while(true){
                string s=prompt(label+" (DD/MM/YYYY) ");
                if(s.size()==10 && s[2]=='/' && s[5]=='/'){
                    try{
                        int d=stoi(s.substr(0, 2));
                        int m=stoi(s.substr(3, 2));
                        int y=stoi(s.substr(6, 4));
                        if(d>=1 && d<=31 && m>=1 && m<=12 && y>2025)
                            return Days(d, m, y);
                    }
                    catch(...){}
                }
                err("Invalid Date. Use DD/MM/YYYY");
            }
        }

        string roomTypeName(int t){
            if(t==Economy)  return "Economy";
            if(t==Standard) return "Standard";
            return "Premimum";
        }

    public:
        
};