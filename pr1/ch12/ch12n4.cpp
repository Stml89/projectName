/*#include <fstream>
#include <iostream>
using namespace std;
const int SIZE = 10;

class person
{
protected:
    char name[SIZE];
    char secName[SIZE];
    unsigned long number;
public:
    friend istream& operator>>( istream&, person& );
    friend ostream& operator<<( ostream&, person& );
};
//-------------------------------------------------------
istream& operator>>( istream& f, person& per )
{
    f >> per.name >> per.secName >> per.number;
    return f;
}
//-------------------------------------------------------
ostream& operator<<( ostream& f, person& per )
{
    f << per.name << " " << per.secName << " " << per.number << endl;
    return f;
}
//-------------------------------------------------------
int main( )
{
    int i = 0;
    char ch;
    person pers;
    ofstream ofile;
    const char* fileName = "/home/sstamal/ch12n4.txt";

    ofile.open( fileName, ios::app | ios::out | ios::in );
    do{
        cout << "\nEnter person data ( Name secName Num ):";
        cin >> pers;
        ofile << pers;
        cout << "\nAdd other person( y / n )?";
        cin >> ch;
    } while ( ch == 'y' );
    ofile.close( );

    ifstream ifile;
    ifile.open( fileName );
    cout << "File:\n";
    while( true ) {
        i++;
        ifile >> pers;
        if( ifile.eof( ) )
            break;
        cout << i << ". " << pers;
    }
    cout << endl;
    return 0;
}*/
