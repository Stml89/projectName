#include <stdio.h>
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
    void show( Int _int )
    {
        printf( "\nShow func: ", _int );
        //std::cout << "\nShow func: " << _int;
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

//    ii3 == Int::plusInt( ii1, ii2 );
    printf( "\nii3 = %d ", ii3 );
    return 0;
}
