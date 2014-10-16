#include <fstream>
#include <iostream>
using namespace std;

class time1
{
private:
    int h;
    int m;
    int s;
public:
    char get_time( time1 &tt );
    void put_time( time1 &tt );
    //void error( );
};

char time1::get_time( time1 &rr )
{
    char ch1;
    cout << "\nVvedite 4asi:"; cin >> rr.h;
    if( rr.h < 0 || rr.h > 23 ){
        cerr << "Format shout be: from 0 to 23";
    }
    cout << "\nVvedite miuti:"; cin >> rr.m;
    if( rr.m < 0 || rr.m > 59 ){
        cerr << "Format shout be: from 0 to 59";
    }
    cout << "\nVvedite sekundi:"; cin >> rr.s;
    if( rr.s < 0 || rr.s > 59 ){
        cerr << "Format shout be: from 0 to 59";
    }
    cout << "\nprodoljit ( y / n ) ?";cin >> ch1;
    return ch1;
}

void time1::put_time( time1 &te )
{
    if( te.h < 10 || te.m < 10 || te.s < 10){
        if( te.h < 10 ) {
            te.h.str();// +=
        } else if( te.m < 10 ){
            //te.m =
        } else if( te.s < 10 ){
            //te.s =
        }
    }
    cout << "\nvremya = " << te.h << ":" << te.m << ":" << te.s << endl;
}

int main( )
{
    char ch;
    time1 ti;
    do{
        ch = ti.get_time( ti );
    }while ( ch == 'y' );

    ti.put_time( ti );
    return 0;
}
