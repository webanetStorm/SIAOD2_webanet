#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <fstream>
#include <locale>
#include <cmath>
#include "Windows.h"
#include <string>

using namespace std;

struct Node
{
    char character;
    int frequency;
    Node *left, *right;

    Node( char character, int frequency )
    {
        left = right = nullptr;
        this->character = character;
        this->frequency = frequency;
    }
};

struct Compare
{
    bool operator()( Node* left, Node* right )
    {
        return left->frequency > right->frequency;
    }
};

void generateHuffmanCodes( Node* root, string code, map<char, string>& huffmanCodes )
{
    if ( !root ) return;

    if ( !root->left && !root->right )
    {
        huffmanCodes[root->character] = code;
    }

    generateHuffmanCodes( root->left, code + "0", huffmanCodes );
    generateHuffmanCodes( root->right, code + "1", huffmanCodes );
}

map<char, string> buildHuffmanTree( const string& text )
{

    map<char, int> frequencyMap;
    for ( char ch : text )
    {
        frequencyMap[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for ( auto pair : frequencyMap )
    {
        minHeap.push( new Node( pair.first, pair.second ) );
    }

    while ( minHeap.size() != 1 )
    {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        int sum = left->frequency + right->frequency;
        Node* newNode = new Node( L'\0', sum );
        newNode->left = left;
        newNode->right = right;
        minHeap.push( newNode );
    }

    map<char, string> huffmanCodes;
    generateHuffmanCodes( minHeap.top(), "", huffmanCodes );

    return huffmanCodes;
}

string encodeText( const string& text, map<char, string>& huffmanCodes )
{
    string encodedText = "";
    for ( char ch : text )
    {
        encodedText += huffmanCodes[ch];
    }
    return encodedText;
}

string decodeText( const string& encodedText, map<string, char>& reverseHuffmanCodes )
{
    string decodedText = "";
    string codeBuffer = "";
    for ( char bit : encodedText )
    {
        codeBuffer += bit;
        if ( reverseHuffmanCodes.find( codeBuffer ) != reverseHuffmanCodes.end() )
        {
            decodedText += reverseHuffmanCodes[codeBuffer];
            codeBuffer.clear();
        }
    }
    return decodedText;
}

double calculateAverageCodeLength( const map<char, string>& huffmanCodes, const map<char, int>& frequencyMap, int totalSymbols )
{
    double sumCodeLengths = 0.0;

    for ( const auto& pair : huffmanCodes )
    {
        char symbol = pair.first;
        int codeLength = pair.second.length();
        int frequency = frequencyMap.at( symbol );

        sumCodeLengths += codeLength * frequency;
    }

    return sumCodeLengths / totalSymbols;
}

double calculateVariance( const map<char, string>& huffmanCodes, const map<char, int>& frequencyMap, int totalSymbols, double averageLength )
{
    double squaredDifferenceSum = 0.0;

    for ( const auto& pair : huffmanCodes )
    {
        char symbol = pair.first;
        int codeLength = pair.second.length();
        int frequency = frequencyMap.at( symbol );

        double difference = codeLength - averageLength;
        squaredDifferenceSum += frequency * pow( difference, 2 );
    }

    return squaredDifferenceSum / totalSymbols;
}


int main()
{
    SetConsoleCP( 1251 );
    SetConsoleOutputCP( 1251 );

    string inputFilename = "input.txt";
    ifstream inputFile( inputFilename );
    if ( !inputFile.is_open() )
    {
        cout << "Ошибка открытия файла..." << endl;
        return 1;
    }

    string inputText;
    getline( inputFile, inputText, '\0' );
    inputFile.close();

    // Строим дерево Хаффмана и получаем коды
    map<char, string> huffmanCodes = buildHuffmanTree( inputText );

    wcout << L"Коды Хаффмана для каждого символа:\n";
    for ( const auto& pair : huffmanCodes )
    {
        string characterRepresentation = pair.first == '\n' ? "\\n" : string( 1, pair.first );
        cout << "\'" << characterRepresentation << "\': " << pair.second << endl;
    }

    // Кодируем текст
    string encodedText = encodeText( inputText, huffmanCodes );

    // Записываем закодированный текст в файл
    ofstream encodedFile( L"encoded.txt" );
    encodedFile << encodedText;
    encodedFile.close();

    // Создаем обратное отображение кодов для декодирования
    map<string, char> reverseHuffmanCodes;
    for ( const auto& pair : huffmanCodes )
    {
        reverseHuffmanCodes[pair.second] = pair.first;
    }

    // Декодируем текст
    string decodedText = decodeText( encodedText, reverseHuffmanCodes );

    // Записываем декодированный текст в файл
    ofstream decodedFile( "decoded.txt" );
    decodedFile << decodedText;
    decodedFile.close();

    // Подсчитываем частоты символов
    map<char, int> frequencyMap;
    for ( wchar_t ch : inputText )
    {
        frequencyMap[ch]++;
    }

    int totalSymbols = inputText.length();

    // Рассчитываем среднюю длину кода
    double averageCodeLength = calculateAverageCodeLength( huffmanCodes, frequencyMap, totalSymbols );
    cout << "Средняя длина кода: " << averageCodeLength << endl;

    // Рассчитываем дисперсию длины кода
    double variance = calculateVariance( huffmanCodes, frequencyMap, totalSymbols, averageCodeLength );
    cout << "Дисперсия: " << variance << endl;

    // Размер исходного и сжатого текста
    size_t originalSize = inputText.length() * 8;
    size_t compressedSize = encodedText.length();
    cout << "Размер исходного текста: " << originalSize << " бит\n";
    cout << "Размер сжатого текста: " << compressedSize << " бит\n";
    cout << "Коэффициент сжатия: " << static_cast<double>( originalSize ) / compressedSize << endl;

    return 0;
}

