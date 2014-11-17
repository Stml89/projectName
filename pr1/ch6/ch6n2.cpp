/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESC = 27;

using namespace std;

class tollBooth
{
private:
    unsigned int sumOfCar;
    double sumOfCash;

public:
    tollBooth( ): sumOfCar( 0 ), sumOfCash( 0 )
    { }
    void payingCar( )
    {
        sumOfCar++;
        sumOfCash += 0.5;
    }
    tollBooth nopayCar( )
    {
        sumOfCar++;
    }
    void show( )const
    {
        printf( "\nTotal sum is: %d\n", sumOfCash );
        printf( "\ncars : %d\n", sumOfCar );
    }
};

int main( )
{
    char ch;
    tollBooth tB;

        do{
            printf( "najmite 'y' ili 'n'\n" );
            ch = getchar();

               if( ch == 'y' )//y
                    tB.payingCar( );

               else if( ch == 'n' )//n
                    tB.nopayCar( );
        }while( ch != ESC );
    tB.show( );
    return 0;
}
*/
