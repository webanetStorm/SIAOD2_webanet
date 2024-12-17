#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <iomanip>

// ======== ШЕННОН-ФАНО ========
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
std::string shannonFanoCompress( const std::string &text, std::map<char, std::string> &codeMap )
{
    std::map<char, int> freqMap;
    for ( char ch : text ) freqMap[ch]++;
    std::vector<Symbol> symbols;
    for ( auto &pair : freqMap ) symbols.push_back( { pair.first, pair.second, "" } );
    std::sort( symbols.begin(), symbols.end(), compare );
    shannonFano( symbols, 0, symbols.size() - 1 );
    for ( auto &sym : symbols ) codeMap[sym.ch] = sym.code;
    std::string encoded;
    for ( char ch : text ) encoded += codeMap[ch];
    return encoded;
}
std::string shannonFanoDecompress( const std::string &encoded, std::map<std::string, char> &reverseMap )
{
    std::string decoded, buffer;
    for ( char bit : encoded )
    {
        buffer += bit;
        if ( reverseMap.find( buffer ) != reverseMap.end() )
        {
            decoded += reverseMap[buffer];
            buffer.clear();
        }
    }
    return decoded;
}

// ======== ХАФФМАН ========
struct HuffmanNode
{
    char ch;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode( char c, int f, HuffmanNode *l = nullptr, HuffmanNode *r = nullptr ) : ch( c ), freq( f ), left( l ), right( r )
    {
    }
};
struct CompareNode
{
    bool operator()( HuffmanNode *a, HuffmanNode *b )
    {
        return a->freq > b->freq;
    }
};
void buildHuffmanTree( const std::map<char, int> &freqMap, HuffmanNode *&root )
{
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, CompareNode> pq;
    for ( auto &pair : freqMap ) pq.push( new HuffmanNode( pair.first, pair.second ) );
    while ( pq.size() > 1 )
    {
        HuffmanNode *left = pq.top(); pq.pop();
        HuffmanNode *right = pq.top(); pq.pop();
        pq.push( new HuffmanNode( '\0', left->freq + right->freq, left, right ) );
    }
    root = pq.top();
}
void generateHuffmanCodes( HuffmanNode *node, const std::string &code, std::map<char, std::string> &codeMap )
{
    if ( !node ) return;
    if ( node->ch != '\0' ) codeMap[node->ch] = code;
    generateHuffmanCodes( node->left, code + "0", codeMap );
    generateHuffmanCodes( node->right, code + "1", codeMap );
}
std::string huffmanCompress( const std::string &text, std::map<char, std::string> &codeMap )
{
    std::map<char, int> freqMap;
    for ( char ch : text ) freqMap[ch]++;
    HuffmanNode *root = nullptr;
    buildHuffmanTree( freqMap, root );
    generateHuffmanCodes( root, "", codeMap );
    std::string encoded;
    for ( char ch : text ) encoded += codeMap[ch];
    return encoded;
}

// ======== MAIN ========
int main()
{
    setlocale( LC_ALL, "" );

    std::string text = "Фамилия Имя Отчество";
    std::map<char, std::string> shannonCodeMap, huffmanCodeMap;

    // Шеннон-Фано
    std::cout << "=== ШЕННОН-ФАНО ===\n";
    std::string shannonEncoded = shannonFanoCompress( text, shannonCodeMap );
    std::cout << "Закодированный текст: " << shannonEncoded << "\n";

    // Хаффман
    std::cout << "\n=== ХАФФМАН ===\n";
    std::string huffmanEncoded = huffmanCompress( text, huffmanCodeMap );
    std::cout << "Закодированный текст: " << huffmanEncoded << "\n";

    // Коэффициенты сжатия
    int originalSize = text.size() * 8;
    std::cout << "\nРазмер исходного текста: " << originalSize << " бит\n";
    std::cout << "Размер текста (Шеннон-Фано): " << shannonEncoded.size() << " бит\n";
    std::cout << "Размер текста (Хаффман): " << huffmanEncoded.size() << " бит\n";

    return 0;
}
