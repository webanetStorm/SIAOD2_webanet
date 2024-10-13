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
    const int ALPHABET_SIZE = 256;
    int m = pattern.length();
    vector<int> table( ALPHABET_SIZE, m );

    for ( int i = 0; i < m - 1; i++ )
        table[(unsigned char)pattern[i]] = m - 1 - i;

    return table;
}

int BMHSearch( string text, string pattern )
{
    int n = text.length(), m = pattern.length();

    if ( m > n )
        return -1;

    vector<int> badCharTable = BuildShiftTable( pattern );
    int i = 0;

    while ( i <= n - m )
    {
        int j = m - 1;

        while ( j >= 0 and pattern[j] == text[i + j] )
            j--;

        if ( j < 0 )
            return i;

        i += badCharTable[(unsigned char)text[i + m - 1]];
    }

    return -1;
}


int main()
{
    setlocale( LC_ALL, "" );


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
                index = LinearSearch( text, pattern );
                break;
            case 2:
                index = BMHSearch( text, pattern );
                break;
            default:
                cout << "Неизвестная команда\n";
                continue;
        }

        index != -1
            ? cout << "Первое вхождение подстроки найдено на позиции: " << index << endl
            : cout << "Подстрока не найдена\n";
    }


    return 0;
}
