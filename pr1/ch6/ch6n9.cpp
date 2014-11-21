#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class fraction
{
private:
    int che;
    int zn;

public:
    void getNumber( )
    {
        char ch;
        cout << "\nInput number: \n";
        cin >> che >> ch >> zn;
    }

    void showNumber( )
    {
        cout << "\nsum is : " << che << "/" << zn << endl;
    }
    friend fraction operator+( const fraction &fr1, const fraction &fr2 )
    {
        fraction tmp;
        if( fr1.zn != fr2.zn ){
            cout << "\nfr1.zn != fr2.zn" << endl;
        }
        tmp.zn = fr1.zn;
        tmp.che = fr1.che + fr2.che;
        return tmp;
    }

    int nod(int a, int b );
};

int nod( int a, int b )
{
    while( a != b )
    {
        if( a > b )
        a = a - b;
        else b = b - a;
    }
    return a;
}

int main( )
{
    char ch;
    fraction d1, d2, d3;
    do{
        d1.getNumber( ); d2.getNumber( );
        d3 = d1 + d2;
        d3.showNumber( );
        cout << "\nrepit('y' or 'n')?"; cin >> ch;
    }while( ch != 'n' );
}
