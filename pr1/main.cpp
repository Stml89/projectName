#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    char ch;
    ifstream infile("TEST.TXT");
    if (infile != NULL) {
        while( infile ){
            infile.get(ch);
            cout << ch;
            }
        cout << endl;
    }
    else{
    cout << "bad file\n";
}
        return 0;
}
