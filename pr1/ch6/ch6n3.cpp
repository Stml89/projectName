#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Time
{
private:
    int h;
    int m;
    int s;

public:
    Time( ): h( 0 ), m( 0 ), s( 0 )
    { }
    Time(int hh, int mm, int ss ): h( hh ), m( mm ), s( ss )
    { }
    void show( ) const
    {
        if( h < 10 ){
            printf("0%d:", h);
        }
        else
            printf( "%d:", h);

        if( m < 10 ){
            printf("0%d:", m);
        }
        else
            printf("%d:", m);

        if( s < 10 ){
            printf("0%d", s);
        }
        else
            printf("%d", s);
        printf("\n");
    }

    friend Time operator+( const Time &t1, const Time &t2)
    {
        Time tmp;
        tmp.s = t1.s + t2.s;
            if( tmp.s > 59 ){
                tmp.s = tmp.s - 60;
                tmp.m++;
            }

        tmp.m += t1.m + t2.m;
            if( tmp.m > 59 ){
                tmp.m = tmp.m - 60;
                tmp.h++;
            }

        tmp.h += t1.h + t2.h;
            if( tmp.h > 23 ){
                printf( "Bolshe sutok" );
            }

        return tmp;
    }
};

int main( )
{
    Time tt1(2, 1, 2);
    Time tt2(12, 2, 0);
    Time tt3 = tt1 + tt2;

    tt3.show( );
    return 0;
}

