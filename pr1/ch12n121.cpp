#include <fstream>      // для файловых потоков
#include <iostream>
#include <string>
//#include <process.h>      // для exit()
#include <string.h>
#include <stdlib.h>
#include <algorithm>
const int IDN = 5;
const int MAXEM = 100;  // максимальное число людей
using namespace std;
///////////////////////////////////////////////////////////
class names            // класс person
{
  protected:
    string name;       // имя человека
    static int n;    // текущее число людей
    static names* arrap[]; //массив указателей на
                              // класс работников
    unsigned long No;     // его номер

  public:
    void getData()      // получить данные о человеке
    {
        cout << "\n  Введите имя: "; cin >> name;
        cout << "  Введите номер: "; cin >> No;
    }
    void showData()     // вывод данных о человеке
    {
        cout << "\n  Имя: " << name;
        cout << "\n  Номер (XXXX): " << No;
    }
    void write_format()
    {
        ofstream outfile ("name.txt"); //создать объект ofstream
        outfile << No << ' ' << name << endl;
        outfile.close();
        cout << "Файл записан.";
    }
    static void read_specific();
    static void add();
    static void Display();
    static void write();
    static void read();
};
//---------------------------------------------------------
void names::read_specific()
{
    const int MAX = 100;
    char buffer[MAX];
    char buffer2[MAX];
    char id;
    while (true)
    {
        cout << "Введите номер сотрудника: ";

        cin >> id;
        if ( cin.good( ) )
        {
            cin.clear();
            ifstream infile;
            infile.open( "name.txt" );
            if( !infile )           // проверить на наличие ошибок
            {
                cerr << "\nНевозможно открыть name.txt";
                exit(-1);
            }
            while( !infile.eof( ) )
            {
                infile.getline( buffer, MAX );
                for( int i = 0; i < strlen( buffer ); i++ ){
                    if( buffer[ i ] != ' ' ){
                        buffer2[ i ] = buffer[ i ];
                    }
                    else if( buffer[ i ] == '\n' ){
                        cout << "this string does not have a space";
                    }
                    else{
                        continue;
                    }
                }
                cout << "\nEEEE "<< buffer2;
            }
            cout << "\n  Таких людей нет.\n";
        }
        else
        {
            cin.clear();
            cout<<"Неправильно введен номер."<<endl;
            cin.ignore( 10, '\n' );
        }
    }
}
//---------------------------------------------------------
//статические переменные
int names::n;                  // текущее число работников
names* names::arrap[MAXEM]; // массив указателей на
                                  // класс работников
//---------------------------------------------------------
//добавить человека  в список (хранится в ОП)
void names::add( )
{
    arrap[n] = new names;
    arrap[n++]->getData( );  //Получить данные от пользователя
}
//---------------------------------------------------------
//Вывести данные обо всех людях
void names::Display()
  {
  for(int j=0; j<n; j++)
    {
    cout<<(j+1);                // вывести номер
    arrap[j]->showData();           // Вывод данных
    cout<<endl;
    }
  }
//---------------------------------------------------------
//Записать все объекты, хранящиеся в памяти, в файл
void names::write()
{
  cout<<"Идет запись " << n << " работников.\n";
  ofstream ouf;           // открыть ofstream в двоичном виде
  ouf.open("name.txt");
  if(!ouf)
    { cout<<"\nНевозможно открыть файл\n"; return; }
  for(int j=0; j<n; j++)
  {
      ouf << arrap[j]->No << ' ' << arrap[j]->name;
      if (j<n-1)
          ouf<<endl;
  }
    if( !ouf )
      { cout<<"\nЗапись в файл невозможна\n"; return; }
}
//---------------------------------------------------------
//чтение всех данных из файла в память
void names::read()
{
  ifstream inf;           // открыть ifstream в двоичном виде
  inf.open("name.txt");
  if(!inf)
    { cout << "\nНевозможно открыть файл\n"; return; }
  n = 0;                  // В памяти работников нет
  while(true)
  {
      if(inf.eof())
          break;
      if(!inf)              // ошибка чтения типа
      { cout << "\nНевозможно чтение типа\n"; return; }
      arrap[n] = new names;
      inf >> arrap[n]->No >> arrap[n]->name;

      if(!inf)              // ошибка, но не EOF
      { cout << "\nЧтение данных из файла невозможно\n"; return; }
      n++;                  // счетчик работников увеличить
  }
  cout << "Идет чтение " << n << " работников\n";
}
///////////////////////////////////////////////////////////
int main()
  {
  setlocale (LC_ALL, "russian");
  char ch;
   while(true)
    {
    cout << "'a' – добавление сведений о работнике"
          "\n'd' - вывести сведения обо всех работниках"
          "\n'w' – записать все данные в файл"
          "\n'r' – прочитать все данные из файла"
          "\n'f' – найти определенного работника"
          "\n'x' - выход"
          "\nВаш выбор: ";
    cin >> ch;
    switch(ch)
      {
      case 'a':           // добавить работника
        names::add(); break;
      case 'd':           // вывести все сведения
        names::Display(); break;
      case 'w':           // запись в файл
        names::write(); break;
      case 'r':           // чтение всех данных из файла
        names::read(); break;
      case 'f':           // чтение всех данных из файла
        names::read_specific(); break;
      case 'x': exit(0);  // выход
      default: cout << "\nНеизвестная команда";
      }  //end switch
    }  //end while

  cout << endl;
  system("pause");
  return 0;
  }
