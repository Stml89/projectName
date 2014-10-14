/*// englcon.cpp
// constructors, adds objects using member function
#include <iostream>
#include <fstream>
using namespace std;
////////////////////////////////////////////////////////////////
class Distance                     //English Distance class
   {
   private:
      int feet;
      float inches;
   public:                         //constructor (no args)
      Distance() : feet(0), inches(0.0)
         {  }
                                   //constructor (two args)
      Distance(int ft, float in)  : feet(ft), inches(in)
         {  }

      void getdist()               //get length from user
         {
         cout << "\nEnter feet: ";  cin >> feet;
         cout << "Enter inches: ";  cin >> inches;
         }

      void showdist()              //display distance
         { cout << feet << "\'-" << inches << '\"'; }

      void add_dist(Distance,  Distance); //const;    //declaration
   };
//--------------------------------------------------------------
                                   //add lengths d2 and d3
void Distance::add_dist(Distance d2,  Distance d3) //const
   {
   inches = d2.inches + d3.inches; //add the inches
   feet = 0;                       //(for possible carry)
   if(inches >= 12.0)              //if total exceeds 12.0,
      {                            //then decrease inches
      inches -= 12.0;              //by 12.0 and
      feet++;                      //increase feet
      }                            //by 1
   feet += d2.feet + d3.feet;      //add the feet
   }
////////////////////////////////////////////////////////////////
int main()
{
    char ch;
    Distance dist1;          //define two lengths
    //Distance dist2(11, 6.25);       //define and initialize dist2
    fstream file;

    file.open("SOMEfile", ios::app | ios::out | ios::in | ios::binary );
    do                             //data from user to file
      {
      cout << "\nEnter some data:";
      dist1.getdist();            //get one person's data

      file.write( reinterpret_cast<char*>( &dist1 ), sizeof( dist1 ) );
      cout << "Enter another person (y/n)? ";
      cin >> ch;
      }
    while(ch == 'y');

    file.seekg(0);
    file.read( reinterpret_cast<char*>( &dist1 ), sizeof( dist1 ) );
    while( !file.eof() )           //quit on EOF
       {
       cout << "\nDistance from file:";        //display person
       dist1.showdist();            //read another person
       file.read( reinterpret_cast<char*>( &dist1 ), sizeof( dist1 ) );
       }

   cout << endl;
   return 0;
}*/
