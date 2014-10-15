#include <fstream>
#include <iostream>
using namespace std;
const int SIZE = 20;

class person
{
protected:
    char name[SIZE];
    char secName[SIZE];
    int number;
public:
    friend istream& operator>>( istream&, person& );
    friend ostream& operator<<( ostream&, person& );
};
//-------------------------------------------------------
istream& operator>>( istream& f, person& per )
{
    const char* space = "-";
    //f >> "Name: " >> per.name >> "secName: " >> per.secName >> "number: " >> per.number >> endl;
    f >> per.name >> per.secName >> per.number;
    return f;
}
//-------------------------------------------------------
ostream& operator<<( ostream& f, person& per )
{
    f << "Name: " << per.name << "secName: " << per.secName << "number: " << per.number << endl;
    f << per.name << " " << per.secName << " " << per.number;
    return f;
}
//-------------------------------------------------------
int main( )
{
    int i = 0;
    char ch;
    person pers;
    ofstream ofile;
    const char* fileName = "ch12n4.txt";

    ofile.open( fileName );//, ios::app | ios::out | ios::in );
    do{
        cout << "\nEnter person data:";
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
        cout << i << "." << pers << endl;
    }
    cout << endl;
    return 0;
}
