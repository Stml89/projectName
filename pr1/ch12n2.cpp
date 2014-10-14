// otype.cpp
// Имитация команды TYPE
#include <fstream>
#include <iostream>
using namespace std;


int main(int argc, char* argv[] )
{
    if( argc != 2 )
    {
        cerr << "\nФормат команды: otype имя_файла\n";
        //exit(-1);
    }
    for(;;){
        cout << "2131231";
    }
        char ch;
        // символ для считывания
        ifstream infile;
        // создать входной файл
        infile.open( "SOMEfile", ios::app | ios::out | ios::in | ios::binary ); // открыть файл
        if( !infile )
        // проверить на наличие ошибок
        {
        cerr << "\nНевозможно открыть " << argv[1];
        //exit(-1);
        }
        while( infile.get(ch) != 0 ) // считать символ
        cout << ch;
        // отобразить символ
        return 0;
}
