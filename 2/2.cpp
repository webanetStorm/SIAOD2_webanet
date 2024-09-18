#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


struct City
{

    int cityCode;

    char cityName[50];

};


void CreateBinaryFile( string filename, int numRecords )
{
    ofstream outFile( filename, ios::binary );
    if ( !outFile )
    {
        cerr << "Ошибка при создании файла!" << endl;
        return;
    }

    City city;
    for ( int i = 0; i < numRecords; i++ )
    {
        city.cityCode = 10000 + rand() % 90000;
        snprintf( city.cityName, sizeof( city.cityName ), "City_%d", i + 1 );
        outFile.write( reinterpret_cast<const char*>( &city ), sizeof( City ) );
    }

    outFile.close();
    cout << "Бинарный файл создан." << endl;
}

bool LinearSearch( string filename, int key, City& result )
{
    ifstream inFile( filename, ios::binary );
    if ( !inFile )
    {
        cerr << "Ошибка при открытии файла!" << endl;
        return false;
    }

    City city;
    while ( inFile.read( reinterpret_cast<char*>( &city ), sizeof( City ) ) )
    {
        if ( city.cityCode == key )
        {
            result = city;
            return true;
        }
    }

    return false;
}

bool FibonacciSearch( vector<int> keys, int key, int& index )
{
    int fibMMm2 = 0, fibMMm1 = 1, fibM = fibMMm2 + fibMMm1, n = keys.size(), offset = -1;

    while ( fibM < n )
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    while ( fibM > 1 )
    {
        int i = min( offset + fibMMm2, n - 1 );

        if ( keys[i] < key )
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if ( keys[i] > key )
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
        {
            index = i;
            return true;
        }
    }

    if ( fibMMm1 and keys[offset + 1] == key )
    {
        index = offset + 1;
        return true;
    }

    return false;
}

vector<int> LoadKeys( string filename )
{
    ifstream inFile( filename, ios::binary );
    vector<int> keys;
    City city;

    while ( inFile.read( reinterpret_cast<char*>( &city ), sizeof( City ) ) )
    {
        keys.push_back( city.cityCode );
    }

    return keys;
}

bool ReadRecordByOffset( string filename, int index, City& result )
{
    ifstream inFile( filename, ios::binary );
    if ( !inFile )
    {
        cerr << "Ошибка при открытии файла!" << endl;
        return false;
    }

    inFile.seekg( index * sizeof( City ), ios::beg );
    inFile.read( reinterpret_cast<char*>( &result ), sizeof( City ) );

    return true;
}

int main()
{
    setlocale( LC_ALL, "" );

    srand( static_cast<unsigned>( time( 0 ) ) );

    string filename = "cities.dat";
    int numRecords = 1000, key, menu;
    City result;

    while ( true )
    {

        cout
            << "\t1 - Создать бинарный файл\n"
            << "\t2 - Линейный поиск\n"
            << "\t3 - Поиск Фибоначчи\n"
            << "\t0 - Выход\n";

        cin >> menu;


        switch ( menu )
        {
            case 1:
            {
                cout << "Введите количество записей: ";
                cin >> numRecords;

                CreateBinaryFile( filename, numRecords );

                break;
            }
            case 2:
            {
                cout << "Введите код города для поиска: ";
                cin >> key;

                LinearSearch( filename, key, result )
                    ? cout << "Город найден: Код: " << result.cityCode << ", Название: " << result.cityName << endl
                    : cout << "Город с таким кодом не найден." << endl;

                break;
            }
            case 3:
            {
                vector<int> keys = LoadKeys( filename );
                int index;

                cout << "Введите код города для поиска: ";
                cin >> key;

                FibonacciSearch( keys, key, index ) 
                    ? ReadRecordByOffset( filename, index, result )
                        ? cout << "Город найден: Код: " << result.cityCode << ", Название: " << result.cityName << endl
                        : cout << "Ошибка чтения записи." << endl
                    : cout << "Город с таким кодом не найден." << endl;

                break;
            }
            case 0:
            {
                return 0;
            }
            default:
            {
                cout << "Некорректный ввод\n";
            }
        }

    }

    return 0;
}
