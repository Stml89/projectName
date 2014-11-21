/*#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
char simv = '\xF8';

enum NWSE{
    N, W, S, E
};

class angle
{
private:
    int grud;
    float min;
    char NWSE;

public:
    angle( ): grud( 0 ), min( 0 ), NWSE( ' ' )
    { }
    angle( int a, float b, char c): grud( a ), min( b ), NWSE( c )
    { }
    void getKoord();
    void showKoord();
};

void angle::getKoord()
{
    cout << "Vvdetite koorditatu to4ki:\n";
    cout << "Vvedite grud\n"; cin >> grud;
    cout << "Vvedite minuti\n"; cin >> min;
    cout << "Vvedite napravlenie\n"; cin >> NWSE;
}

void angle::showKoord()
{
    cout << "koordinata to4ki = \n" << grud << simv << min << "\'" << " " << NWSE << endl;
}

int main( )
{
    angle ang(179, 88.77, 'N');
    angle ang1;

    ang.showKoord();

    for( int i = 0; i < 2; i++ ){
        ang1.getKoord();
        ang1.showKoord();
    }
    return 0;
}
*/
