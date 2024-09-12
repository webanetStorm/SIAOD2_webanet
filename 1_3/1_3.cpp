#include <algorithm>
#include <iostream>
#include <fstream>
#include <bitset>
#include <chrono>
#include <vector>
#include <random>

using namespace std;


constexpr size_t BITSET_SIZE = 5e6;


void GenerateInputFile()
{
    const string FILE_NAME = "input.txt";
    vector<int> numbers( BITSET_SIZE );

    for ( size_t i = 0; i < BITSET_SIZE; i++ )
        numbers[i] = i;

    random_device rd;
    mt19937 g( rd() );
    shuffle( numbers.begin(), numbers.end(), g );

    ofstream outFile( FILE_NAME );
    if ( !outFile )
    {
        cerr << "Не удалось открыть файл для записи" << endl;
        return;
    }

    for ( auto num : numbers )
        outFile << num << '\n';

    outFile.close();
    cout << "Файл " << FILE_NAME << " успешно создан с " << BITSET_SIZE << " уникальными числами" << endl;
}

void TaskA()
{
    bitset<BITSET_SIZE> bitArray;
    string inputFileName = "input.txt", outputFileName = "output.txt";

    ifstream inputFile( inputFileName );
    if ( !inputFile )
    {
        cerr << "Не удалось открыть входной файл" << endl;
        return;
    }

    auto start = chrono::high_resolution_clock::now();

    unsigned int number;
    while ( inputFile >> number )
        if ( number < BITSET_SIZE )
            bitArray.set( number );

    inputFile.close();

    ofstream outputFile( outputFileName );
    if ( !outputFile )
    {
        cerr << "Не удалось открыть выходной файл" << endl;
        return;
    }

    for ( size_t i = 0; i < BITSET_SIZE; i++ )
        if ( bitArray[i] )
            outputFile << i << endl;

    outputFile.close();

    chrono::duration<double> duration = chrono::high_resolution_clock::now() - start;
    cout << "Время выполнения программы: " << duration.count() << " секунд" << endl;
}


void TaskB()
{
    cout << "Объем памяти, занимаемый битовым массивом: " << BITSET_SIZE / 8 << " байт." << endl;
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
                GenerateInputFile();
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
