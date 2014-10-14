#include <iostream>
using namespace std;

int main(int argc, char* argv[] )
{
    cout << "\nargc = " << argc << endl; // число аргументов
    for(int j=0; j<argc; j++)
    // вывести аргументы
    cout << "Аргумент " << j << " = " << argv[j] << endl;
return 0;
}
