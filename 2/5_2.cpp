#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <map>

using namespace std;


struct City
{

    int Code;

    char Name[15];

};


void CreateBinaryFile( string filename, int numRecords )
{
    ofstream file( filename, ios::binary );

    if ( file.is_open() )
    {
        City city;

        for ( int i = 0; i < numRecords; i++ )
        {
            city.Code = i + 1;
            snprintf( city.Name, sizeof( city.Name ), "City_%d", i + 1 );
            file.write( (char*)( &city ), sizeof( City ) );
        }

        file.close();
        cout << "Бинарный файл создан\n";
    }
    else
    {
        cout << "Файл не удалось открыть\n";
    }
}

bool LinearSearch( string filename, int key, City& result )
{
    ifstream file( filename, ios::binary );

    if ( file.is_open() )
    {
        City city;

        while ( file.read( (char*)&city, sizeof( City ) ) )
        {
            if ( city.Code == key )
            {
                result = city;
                return true;
            }
        }
    }

    return false;
}

bool FibonacciSearch( vector<pair<int, streampos>> offsetTable, int key, int& index )
{
    int fibMMm2 = 0, fibMMm1 = 1, fibM = fibMMm2 + fibMMm1, n = offsetTable.size(), offset = -1;

    while ( fibM < n )
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    while ( fibM > 1 )
    {
        int i = min( offset + fibMMm2, n - 1 );

        if ( offsetTable[i].first < key )
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if ( offsetTable[i].first > key )
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

    if ( fibMMm1 and offsetTable[offset + 1].first == key )
    {
        index = offset + 1;
        return true;
    }

    return false;
}

vector<pair<int, streampos>> CreateOffsetTable( string filename )
{
    ifstream file( filename, ios::binary );
    vector<pair<int, streampos>> offsetTable;
    City city;

    while ( file.read( (char*)&city, sizeof( City ) ) )
    {
        offsetTable.push_back( { city.Code, file.tellg() - static_cast<streampos>( sizeof( City ) ) } );
    }

    file.close();

    return offsetTable;
}

bool ReadRecordByOffset( string filename, int index, City& result )
{
    ifstream file( filename, ios::binary );

    if ( file.is_open() )
    {
        file.seekg( index * sizeof( City ), ios::beg );
        file.read( (char*)&result, sizeof( City ) );

        return true;
    }

    return false;
}

int main()
{
    setlocale( LC_ALL, "" );


    srand( time( 0 ) );

    string filename = "cities.dat";
    int numRecords, key, menu;
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

                auto start = chrono::high_resolution_clock::now();

                LinearSearch( filename, key, result )
                    ? cout << "Город найден: Код: " << result.Code << ", Название: " << result.Name << endl
                    : cout << "Город с таким кодом не найден\n";

                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> timeTaken = end - start;
                cout << "Время выполнения линейного поиска: " << timeTaken.count() << " секунд\n";

                break;
            }
            case 3:
            {
                auto offsetTable = CreateOffsetTable( filename );
                int index;

                cout << "Введите код города для поиска: ";
                cin >> key;
                auto start = chrono::high_resolution_clock::now();

                FibonacciSearch( offsetTable, key, index )
                    ? ReadRecordByOffset( filename, offsetTable[index].second, result )
                        ? cout << "Город найден: Код: " << result.Code << ", Название: " << result.Name << endl
                        : cout << "Ошибка чтения записи\n"
                    : cout << "Город с таким кодом не найден\n";

                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> timeTaken = end - start;
                cout << "Время выполнения поиска Фибоначчи: " << timeTaken.count() << " секунд\n";

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
