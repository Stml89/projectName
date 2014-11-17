/*#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Int
{
private:
    int _int;

public:
    Int( ): _int( 0 )
    { }
    Int( int a ): _int( a )
    { }
    void show( )const
    {
        printf( "\nresalt is: %d\n", _int );
    }
    friend Int operator+(const Int &a, const Int &b)
    {
        return Int( a._int + b._int );
    }
};

int main( )
{
    Int ii1( 2 );
    Int ii2( 1 );
    Int ii3 = ii1 + ii2;

    ii3.show( );
    return 0;
}*/
