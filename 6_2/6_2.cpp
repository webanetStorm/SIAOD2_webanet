#include <unordered_map>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


int LinearSearch( string needle, string haystack )
{
    int haystackLength = haystack.length(), needleLength = needle.length();

    for ( int i = 0; i <= haystackLength - needleLength; i++ )
    {
        int j = 0;

        while ( j < needleLength and haystack[i + j] == needle[j] )
            j++;

        if ( j == needleLength )
            return i;
    }

    return -1;
}

unordered_map<char, int> CreateShiftTable( string needle )
{
    unordered_map<char, int> shiftTable;
    int needleLength = needle.length();

    for ( int i = 0; i < needleLength - 1; i++ )
        shiftTable[needle[i]] = needleLength - i - 1;

    return shiftTable;
}

int BMHSearch( string needle, string haystack )
{
    int haystackLength = haystack.length(), needleLength = needle.length(), lastOccurrence = -1, i = 0;

    if ( needleLength > haystackLength ) 
        return -1;

    unordered_map<char, int> shiftTable = CreateShiftTable( needle );

    while ( i <= haystackLength - needleLength )
    {
        int j = needleLength - 1;

        while ( j >= 0 and haystack[i + j] == needle[j] )
            j--;

        j == -1
            ? lastOccurrence = i++
            : i += shiftTable.count( haystack[i + needleLength - 1] ) ? shiftTable[haystack[i + needleLength - 1]] : needleLength;
    }

    return lastOccurrence;
}


int main()
{
    SetConsoleCP( 1251 );
    SetConsoleOutputCP( 1251 );


    string text, pattern;
    int index, menu;

    cout << "Введите текст: ";
    getline( cin, text );

    cout << "Введите образец: ";
    getline( cin, pattern );


    while ( true )
    {
        cout << "\tМеню:\n\t1 - Линейный поиск\n\t2 - Поиск Бойера-Мура-Хорспула\nВыберите действие: ";
        cin >> menu;

        switch ( menu )
        {
            case 1:
                index = LinearSearch( pattern, text );
                break;
            case 2:
                index = BMHSearch( pattern, text );
                break;
            default:
                cout << "Неизвестная команда\n";
                continue;
        }

        index != -1
            ? cout << "Найдено вхождение подстроки на позиции: " << index << endl
            : cout << "Подстрока не найдена\n";
    }


    return 0;
}
