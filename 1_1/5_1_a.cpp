#include <iostream>
#include <bitset>

using namespace std;


unsigned char SetBitToZero( unsigned char x )
{
	unsigned char mask = 1;

	return x &= ~( mask << 4 );
}

unsigned char SetBitToOne( unsigned char x )
{
	unsigned char mask = 1;

	return x |= ( mask << 6 );
}

void BitwiseOperations()
{
	const int n = sizeof( int ) * 8;
	unsigned int x = 25, maska = ( 1 << n - 1 );

	cout << "Начальный вид маски: " << bitset<n>( maska ) << endl << "Результат: ";

	for ( int i = 1; i <= n; i++ )
	{
		cout << ( ( x & maska ) >> ( n - i ) );
		maska = maska >> 1;
	}

	cout << endl;
}


int main()
{
	setlocale( LC_ALL, "" );


	int menu, x;

	cout
		<< "\t1 - Установить 5-й бит числа в 0\n"
		<< "\t2 - Установить 7-й бит числа в 1\n"
		<< "\t3 - Битовые операции (листинг 1)\n"
		<< "\t0 - Выход\n";


	while ( true )
	{
		cout << "\nВыберите действие: ";
		cin >> menu;

		switch ( menu )
		{

			case 1:
			{
				cout << "Введите число (0-255): ";
				cin >> x;

				int dx = SetBitToZero( x );
				cout << "Результат установки 5-го бита в 0: " << bitset<8>( x ) << " (" << (int)x << ") ---> " << bitset<8>( dx ) << " (" << (int)dx << ")" << endl;

				break;
			}

			case 2:
			{
				cout << "Введите число (0-255): ";
				cin >> x;

				int dx = SetBitToOne( x );
				cout << "Результат установки 7-го бита в 1: " << bitset<8>( x ) << " (" << (int)x << ") ---> " << bitset<8>( dx ) << " (" << (int)dx << ")" << endl;

				break;
			}

			case 3:
			{
				BitwiseOperations();

				break;
			}

			case 0:
			{
				return 0;
			}

			default:
			{
				cout
					<< "Некорректный ввод\n"
					<< "\t1 - Установить 5-й бит числа в 0\n"
					<< "\t2 - Установить 7-й бит числа в 1\n"
					<< "\t3 - Битовые операции (листинг 1)\n"
					<< "\t0 - Выход\n";

				break;
			}

		}
	}


	return 0;
}
