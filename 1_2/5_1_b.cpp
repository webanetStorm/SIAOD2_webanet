#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

    
void TaskA()
{
    unsigned char bitArray = 0;
    int num;
    cout << "Введите числа от 0 до 7 (введите -1 для завершения ввода):\n";

    for ( int i = 0; i < 8; i++ )
    {
        cin >> num;

        if ( num == -1 )
            break;

        if ( num >= 0 and num <= 7 )
            bitArray |= ( 1 << ( 7 - num ) );
        else
            cout << "Число должно быть от 0 до 7.\n";
    }

    cout << "Битовое представление: " << bitset<8>( bitArray ) << "\nОтсортированный набор: ";

    for ( int i = 0; i < 8; i++ )
        if ( bitArray & ( 1 << i ) )
            cout << i << ' ';

    cout << endl;
}

void TaskB()
{
    unsigned long long bitArray = 0;
    int num;
    cout << "Введите числа от 0 до 63 (введите -1 для завершения ввода):\n";

    for ( int i = 0; i < 64; i++ )
    {
        cin >> num;

        if ( num == -1 )
            break;

        if ( num >= 0 and num <= 63 )
            bitArray |= ( 1ULL << ( 63 - num ) );
        else
            cout << "Число должно быть от 0 до 63.\n";
    }

    cout << "Битовое представление: " << bitset<64>( bitArray ) << "\nОтсортированный набор: ";

    for ( int i = 0; i < 64; i++ )
        if ( bitArray & ( 1ULL << i ) )
            cout << i << " ";

    cout << endl;
}

void TaskC()
{
    const int MAX_BITS = 64;
    vector<unsigned char> bitArray( 8, 0 );
    int num;

    cout << "Введите числа от 0 до 63 (введите -1 для завершения ввода):\n";

    while ( true )
    {
        cin >> num;

        if ( num == -1 )
            break;

        if ( num >= 0 and num < MAX_BITS )
            bitArray[( MAX_BITS - 1 - num ) / 8] |= ( 1 << ( ( MAX_BITS - 1 - num ) % 8 ) );
        else
            cout << "Число должно быть от 0 до 63.\n";
    }

    cout << "Битовое представление: ";
    for ( int i = 7; i >= 0; i-- )
        cout << bitset<8>( bitArray[i] ) << ' ';
    cout << endl;

    cout << "Отсортированный набор: ";
    for ( int i = 0; i < MAX_BITS; i++ )
        if ( bitArray[i / 8] & ( 1 << ( i % 8 ) ) )
            cout << i << ' ';

    cout << endl;
}


int main()
{
    setlocale( LC_ALL, "" );


    int menu;

    cout
        << "\t1 - Сортировка битовым массивом (8x0-7)\n"
        << "\t2 - Сортировка битовым массивом (64x0-63)\n"
        << "\t3 - Сортировка битовым массивом (64x0-63, линейный массив)\n"
        << "\t0 - Выход\n";


    while ( true )
    {
        cout << "\nВыберите действие: ";
        cin >> menu;

        switch ( menu )
        {
            case 1:
                TaskA();
                break;
            case 2:
                TaskB();
                break;
            case 3:
                TaskC();
                break;
            case 0:
                return 0;
            default:
                cout
                    << "Некорректный ввод\n"
                    << "\t1 - Сортировка битовым массивом (8x0-7)\n"
                    << "\t2 - Сортировка битовым массивом (64x0-63)\n"
                    << "\t3 - Сортировка битовым массивом (64x0-63, линейный массив)\n"
                    << "\t0 - Выход\n";
                break;
        }
    }


    return 0;
}
