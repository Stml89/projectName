#ifndef VERYLONG_H
#define VERYLONG_H

// class specifier for very long integer type
#include <iostream>
#include <string.h>         //for strlen(), etc.
//#include <stdlib.h>         //for ltoa()
#include <stdio.h>
using namespace std;

const int SZ = 1000;
        //maximum digits in verylongs

class verylong
   {
   private:
      char vlstr[SZ];       //verylong number, as a string
      int vlen;             //length of verylong string
      verylong multdigit(const int) const;   //prototypes for
      verylong mult10(const verylong) const; //private functions
   public:
      void strrev(char *s);
      verylong() : vlen(0)             //no-arg constructor
         { vlstr[0]='\0'; }
      verylong(const char s[SZ])       //one-arg constructor
         { strcpy(vlstr, s); vlen=strlen(s); }   //for string
      verylong(const unsigned long n)  //one-arg constructor
         {                                       //for long int
         snprintf(vlstr, sizeof(vlstr), "%lu", n);
        // ltoa(n, vlstr, 10);           //convert to string
         //strrev(vlstr);                //reverse it
         strrev(vlstr);
         vlen=strlen(vlstr);           //find length
         }
      void putvl() const;              //display verylong
      void getvl();                    //get verylong from user
      verylong operator + (const verylong); //add verylongs
      verylong operator * (const verylong); //multiply verylongs
   };
#endif // VERYLONG_H
