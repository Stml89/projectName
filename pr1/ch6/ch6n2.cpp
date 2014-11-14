#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class tollBooth
{
public:
    unsigned int sumOfCar;
    double sumOfCash;

private:
    tollBooth( ): sumOfCar( 0 ), sumOfCash( 0 )
    { }
    tollBooth payingCar( tollBooth &sumCar, tollBooth &sumcash )
    {
        sumCar++;
        sumcash += 0.5;
        return tollBooth;
    }
    tollBooth nopayCar( tollBooth &sumCar)
    {
        sumCar++;
        return tollBooth;
    }

};

int main()
{
    tollBooth tB;

}
