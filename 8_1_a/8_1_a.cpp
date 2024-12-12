#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;


struct Node
{

    char Symbol;

    double Probability;

    string Code;

};


void ShannonFano( vector<Node>& nodes, int start, int end )
{
    if ( start >= end ) 
        return;

    double totalProb = 0.0;
    for ( int i = start; i <= end; i++ ) 
        totalProb += nodes[i].Probability;

    double halfProb = 0.0;
    int splitIndex = start;
    for ( int i = start; i <= end; i++ )
    {
        halfProb += nodes[i].Probability;
        if ( halfProb >= totalProb / 2 )
        {
            splitIndex = i;
            break;
        }
    }

    for ( int i = start; i <= splitIndex; i++ ) 
        nodes[i].Code += "0";
    for ( int i = splitIndex + 1; i <= end; i++ ) 
        nodes[i].Code += "1";

    ShannonFano( nodes, start, splitIndex );
    ShannonFano( nodes, splitIndex + 1, end );
}


int main()
{
    setlocale( LC_ALL, "" );


    string input = "Кот пошёл за молоком, А котята кувырком. Кот пришёл без молока, А котята ха-ха-ха.";
    map<char, double> freq;

    for ( char c : input ) 
        freq[c]++;

    vector<Node> nodes;
    for ( auto& pair : freq )
    {
        nodes.push_back( { pair.first, pair.second / input.size(), "" } );
    }

    sort( nodes.begin(), nodes.end(), []( Node a, Node b )
    {
        return a.Probability > b.Probability;
    } );

    ShannonFano( nodes, 0, nodes.size() - 1 );

    cout << "Результаты кодирования методом Шеннона-Фано:" << endl;
    cout << setw( 10 ) << "Символ" << setw( 15 ) << "Частота" << setw( 15 ) << "Код" << endl;
    for ( auto& node : nodes )
    {
        cout << setw( 10 ) << ( node.Symbol == ' ' ? "<пробел>" : string( 1, node.Symbol ) )
            << setw( 15 ) << node.Probability
            << setw( 15 ) << node.Code << endl;
    }

    cout << "\nЗакодированный текст: ";
    for ( char c : input )
    {
        for ( auto& node : nodes )
        {
            if ( node.Symbol == c )
            {
                cout << node.Code;
                break;
            }
        }
    }
    cout << endl;


    return 0;
}
