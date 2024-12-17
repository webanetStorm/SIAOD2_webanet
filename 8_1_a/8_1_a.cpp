#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iomanip>
#include <tuple>

// ======== МЕТОД ШЕННОНА-ФАНО ========
struct Symbol
{
    char ch;
    int freq;
    std::string code;
};
bool compare( const Symbol &a, const Symbol &b )
{
    return a.freq > b.freq;
}
void shannonFano( std::vector<Symbol> &symbols, int start, int end )
{
    if ( start >= end ) return;
    int totalFreq = 0, splitFreq = 0, split = start;
    for ( int i = start; i <= end; i++ ) totalFreq += symbols[i].freq;
    while ( splitFreq < totalFreq / 2 && split < end ) splitFreq += symbols[split++].freq;
    for ( int i = start; i < split; i++ ) symbols[i].code += "0";
    for ( int i = split; i <= end; i++ ) symbols[i].code += "1";
    shannonFano( symbols, start, split - 1 );
    shannonFano( symbols, split, end );
}
void shannonFanoEncode( const std::string &text )
{
    std::map<char, int> freqMap;
    for ( char ch : text ) freqMap[ch]++;
    std::vector<Symbol> symbols;
    for ( auto &pair : freqMap ) symbols.push_back( { pair.first, pair.second, "" } );
    std::sort( symbols.begin(), symbols.end(), compare );
    shannonFano( symbols, 0, symbols.size() - 1 );

    std::string encodedText;
    for ( char ch : text )
        for ( auto &sym : symbols )
            if ( sym.ch == ch ) encodedText += sym.code;

    std::cout << "Закодированный текст (Шеннон-Фано): " << encodedText << "\n";
}

// ======== МЕТОД LZ77 ========
struct LZ77
{
    int offset, length;
    char nextChar;
};
void LZ77Encode( const std::string &input )
{
    int windowSize = 10;
    std::vector<LZ77> encoded;
    int pos = 0;
    while ( pos < input.size() )
    {
        int bestOffset = 0, bestLength = 0;
        for ( int back = 1; back <= windowSize && pos - back >= 0; back++ )
        {
            int matchLength = 0;
            while ( matchLength < input.size() - pos && input[pos - back + matchLength] == input[pos + matchLength] )
                matchLength++;
            if ( matchLength > bestLength )
            {
                bestOffset = back;
                bestLength = matchLength;
            }
        }
        char nextChar = ( pos + bestLength < input.size() ) ? input[pos + bestLength] : '\0';
        encoded.push_back( { bestOffset, bestLength, nextChar } );
        pos += bestLength + 1;
    }

    std::cout << "Закодированные блоки (LZ77):\n";
    for ( auto &block : encoded )
        std::cout << "(" << block.offset << ", " << block.length << ", " << block.nextChar << ")\n";
}

// ======== МЕТОД LZ78 ========
void LZ78Encode( const std::string &input )
{
    std::map<std::string, int> dictionary;
    std::vector<std::pair<int, char>> encoded;
    std::string current = "";
    int dictIndex = 1;

    for ( char ch : input )
    {
        current += ch;
        if ( dictionary.find( current ) == dictionary.end() )
        {
            dictionary[current] = dictIndex++;
            encoded.push_back( { dictionary[current.substr( 0, current.size() - 1 )], ch } );
            current = "";
        }
    }
    if ( !current.empty() ) encoded.push_back( { dictionary[current], '\0' } );

    std::cout << "Закодированные пары (LZ78):\n";
    for ( auto &pair : encoded )
        std::cout << "(" << pair.first << ", " << pair.second << ")\n";
}

// ======== MAIN ========
int main()
{
    setlocale( LC_ALL, "" );

    std::string text1 = "Кот пошёл за молоком, А котята кувырком. Кот пришёл без молока, А котята ха-ха-ха.";
    std::string binary = "10101001101100111010";
    std::string text2 = "bigbonebigborebigbo";

    std::cout << "==== ШЕННОН-ФАНО ====\n";
    shannonFanoEncode( text1 );

    std::cout << "\n==== LZ77 ====\n";
    LZ77Encode( binary );

    std::cout << "\n==== LZ78 ====\n";
    LZ78Encode( text2 );

    return 0;
}
