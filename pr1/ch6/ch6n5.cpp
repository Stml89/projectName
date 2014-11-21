/*#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int dd, mm, yy;
char ch;
////////////////////////////////////
class date
{
private:
    int day;
    int mon;
    int year;
public:
    void getDate( );
    void showDate( );
};

void date::getDate( )
{
    cout << " Input number for a month: ";
        cin >> mon;
    if( mon <= 0 || mon >= 13  ){
        cout << "wrong month!\n";
//        exit( 0 );
    }
    cout << endl;

    cout << " Input number for a day: ";
        cin >> day;
    if( day <= 0 || day >= 32 ){
        cout << "wrong day!\n";
    }
    cout << endl;

    cout << " Input number for a year: ";
        cin >> year;    cout << endl;
}

void date::showDate( )
{
    cout << mon << "/" << day << "/" << year << endl;
}

///////////////////////////////////
int main( )
{
    date d1;

    d1.getDate();
    d1.showDate();
}*/
