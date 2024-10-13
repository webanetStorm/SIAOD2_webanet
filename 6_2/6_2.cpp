#include <iostream>
#include <string>
#include <vector>

using namespace std;


int LinearSearch( string text, string pattern )
{
    int textLen = text.length(), patternLen = pattern.length();

    for ( int i = 0; i <= textLen - patternLen; i++ )
    {
        int j = 0;

        while ( j < patternLen and text[i + j] == pattern[j] )
            j++;

        if ( j == patternLen )
            return i;
    }
    return -1;
}

vector<int> BuildShiftTable( string pattern )
{
    int patternLen = pattern.length();
    vector<int> shiftTable( 256, patternLen );

    for ( int i = 0; i < patternLen - 1; i++ )
        shiftTable[(unsigned char)( pattern[i] )] = patternLen - 1 - i;

    return shiftTable;
}

int BMHSearchLastOccurrence( string text, string pattern )
{
    vector<int> shiftTable = BuildShiftTable( pattern );
    int textLen = text.length(), patternLen = pattern.length(), i = textLen - patternLen;

    while ( i >= 0 )
    {
        int j = patternLen - 1;

        while ( j >= 0 and text[i + j] == pattern[j] )
            j--;

        if ( j < 0 )
            return i;

        i -= shiftTable[(unsigned char)( text[i + patternLen - 1] )];
    }

    return -1;
}


int main()
{
    setlocale( LC_ALL, "" );


    string text = "Это тестовый текст для поиска. И ещё один поиск", pattern = "поиск";
    int index, menu;

    while ( true )
    {
        cout << "\tМеню:\n\t1 - Линейный поиск\n\t2 - Поиск Бойера-Мура-Хорспула\n";
        cin >> menu;

        switch ( menu )
        {
            case 1:
                index = LinearSearch( text, pattern );
                break;
            case 2:
                index = BMHSearchLastOccurrence( text, pattern );
                break;
            default:
                cout << "Неизвестная команда\n";
                continue;
        }

        index != -1
            ? cout << "Первое вхождение подстроки найдено на позиции: " << index << "\n\n"
            : cout << "Подстрока не найдена\n\n";
    }


    return 0;
}
