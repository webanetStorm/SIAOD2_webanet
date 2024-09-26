#include <algorithm>
#include <iostream>
#include <fstream>
#include <bitset>
#include <chrono>
#include <vector>
#include <random>

using namespace std;


constexpr size_t BITSET_SIZE = 1e7;

const string INPUT_FILE_NAME = "input.txt";


void GenerateInputFile()
{
    vector<int> numbers( BITSET_SIZE );

    for ( size_t i = 0; i < BITSET_SIZE; i++ )
        numbers[i] = i;

    random_device rd;
    mt19937 g( rd() );
    shuffle( numbers.begin(), numbers.end(), g );

    ofstream outFile( INPUT_FILE_NAME );
    if ( outFile.is_open() )
    {
        for ( auto num : numbers )
            outFile << num << '\n';

        outFile.close();
        cout << "Файл " << INPUT_FILE_NAME << " успешно создан с " << BITSET_SIZE << " уникальными числами\n";
    }
}

void TaskA()
{
    //bitset<BITSET_SIZE>* bitArray = new bitset<BITSET_SIZE>;
    vector<unsigned char> bitArray( BITSET_SIZE / 8 + 1, 0 );

    string outputFileName = "output.txt";
    ifstream inputFile( INPUT_FILE_NAME );


    if ( inputFile.is_open() )
    {
        unsigned int number;
        while ( inputFile >> number )
            if ( number < BITSET_SIZE )
                //bitArray->set( number );
                bitArray[number / 8] |= ( 1 << number % 8 );

        inputFile.close();


        auto start = chrono::high_resolution_clock::now();
        vector<int> result;

        for ( int byteIndex = 0; byteIndex < BITSET_SIZE / 8 + 1; byteIndex++ )
            for ( int bitIndex = 0; bitIndex < 8; bitIndex++ )
                if ( bitArray[byteIndex] & ( 1 << bitIndex ) )
                    result.push_back( byteIndex * 8 + bitIndex );

        //for ( size_t i = 0; i < BITSET_SIZE; i++ )
        //    if ( ( *bitArray )[i] )
        //        result.push_back( i );

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "Время выполнения программы: " << duration.count() << " секунд\n";


        ofstream outputFile( outputFileName );

        if ( outputFile.is_open() )
        {
            for ( int value : result )
                outputFile << value << endl;

            outputFile.close();
        }
    }

    //delete bitArray;
}

void TaskB()
{
    cout << "Объем памяти, занимаемый битовым массивом: " << BITSET_SIZE / 8 << " байт\n";
}

int main()
{
    setlocale( LC_ALL, "" );

    int menu;

    cout
        << "\t1 - Сортировка числового файла с битовым массивом\n"
        << "\t2 - Определение объема памяти битового массива\n"
        << "\t0 - Выход\n";


    while ( true )
    {
        cout << "\nВыберите действие: ";
        cin >> menu;

        switch ( menu )
        {
            case 1:
                // GenerateInputFile();
                TaskA();
                break;
            case 2:
                TaskB();
                break;
            case 0:
                return 0;
            default:
                cout << "Некорректный ввод\n"
                    << "\t1 - Сортировка числового файла с битовым массивом\n"
                    << "\t2 - Определение объема памяти битового массива\n"
                    << "\t0 - Выход\n";
                break;
        }
    }


    return 0;
}
