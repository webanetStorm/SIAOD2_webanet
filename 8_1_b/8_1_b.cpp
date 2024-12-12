#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;


struct Node
{

    char Symbol;

    int Frequency;

    Node* Left;

    Node* Right;


    Node( char sym, int freq ) : Symbol( sym ), Frequency( freq ), Left( nullptr ), Right( nullptr )
    {
    }

};


struct Compare
{

    bool operator()( Node* a, Node* b )
    {
        return a->Frequency > b->Frequency;
    }

};


Node* BuildHuffmanTree( const unordered_map<char, int>& freq )
{
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for ( auto& pair : freq )
        pq.push( new Node( pair.first, pair.second ) );

    while ( pq.size() > 1 )
    {
        Node* Left = pq.top(); pq.pop();
        Node* Right = pq.top(); pq.pop();

        Node* combined = new Node( '\0', Left->Frequency + Right->Frequency );
        combined->Left = Left;
        combined->Right = Right;

        pq.push( combined );
    }

    return pq.top();
}

void GenerateHuffmanCodes( Node* root, const string& code, unordered_map<char, string>& codes )
{
    if ( !root ) 
        return;

    if ( root->Symbol != '\0' )
        codes[root->Symbol] = code;

    GenerateHuffmanCodes( root->Left, code + "0", codes );
    GenerateHuffmanCodes( root->Right, code + "1", codes );
}

string Encode( const string& text, const unordered_map<char, string>& codes )
{
    string encodedText;

    for ( char c : text )
        encodedText += codes.at( c );

    return encodedText;
}

string Decode( const string& encodedText, Node* root )
{
    string decodedText;
    Node* current = root;

    for ( char bit : encodedText )
    {
        current = ( bit == '0' ) ? current->Left : current->Right;

        if ( current->Left == nullptr && current->Right == nullptr )
        {
            decodedText += current->Symbol;
            current = root;
        }
    }

    return decodedText;
}

int main()
{
    setlocale( LC_ALL, "" );


    string input = "Кот пошёл за молоком, А котята кувырком. Кот пришёл без молока, А котята ха-ха-ха.";

    unordered_map<char, int> freq;
    for ( char c : input )
    {
        freq[c]++;
    }

    Node* root = BuildHuffmanTree( freq );

    unordered_map<char, string> codes;
    GenerateHuffmanCodes( root, "", codes );

    string encodedText = Encode( input, codes );

    cout << "Коды символов (Хаффман):" << endl;
    for ( auto& pair : codes )
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << "\nЗакодированный текст:" << endl << encodedText << endl;

    string decodedText = Decode( encodedText, root );
    cout << "\nВосстановленный текст:" << endl << decodedText << endl;


    return 0;
}
