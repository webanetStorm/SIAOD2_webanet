#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


struct Edge
{

    int Src, Dest, Weight;

};

struct Subset
{

    int Parent, Rank;

};


class Graph
{

public:

    vector<Edge> Edges;

    int V, E;


    Graph( int V, int E ) : V( V ), E( E )
    {
    }

    void AddEdge( int Src, int Dest, int Weight )
    {
        Edges.push_back( { Src, Dest, Weight } );
    }

};


int Find( Subset subsets[], int i )
{
    if ( subsets[i].Parent != i )
        subsets[i].Parent = Find( subsets, subsets[i].Parent );

    return subsets[i].Parent;
}

void Union( Subset subsets[], int x, int y )
{
    int xroot = Find( subsets, x ), yroot = Find( subsets, y );

    if ( subsets[xroot].Rank < subsets[yroot].Rank )
    {
        subsets[xroot].Parent = yroot;
    }
    else if ( subsets[xroot].Rank > subsets[yroot].Rank )
    {
        subsets[yroot].Parent = xroot;
    }
    else
    {
        subsets[yroot].Parent = xroot;
        subsets[xroot].Rank++;
    }
}

void KruskalMST( Graph& graph )
{
    vector<Edge> result;
    int e = 0, i = 0;

    sort( graph.Edges.begin(), graph.Edges.end(), []( Edge a, Edge b )
    {
        return a.Weight < b.Weight;
    } );

    Subset* subsets = new Subset[graph.V + 1];
    for ( int v = 0; v <= graph.V; ++v )
    {
        subsets[v].Parent = v;
        subsets[v].Rank = 0;
    }

    while ( e < graph.V - 1 and i < graph.E )
    {
        Edge next_edge = graph.Edges[i++];

        int x = Find( subsets, next_edge.Src ), y = Find( subsets, next_edge.Dest );

        if ( x != y )
        {
            result.push_back( next_edge );
            Union( subsets, x, y );
            e++;
        }
    }

    cout << "Минимальное остовное дерево (MST):\n";
    for ( auto edge : result )
        cout << edge.Src << " -- " << edge.Dest << " == " << edge.Weight << endl;

    delete[] subsets;
}

Graph InputGraph()
{
    int V, E;

    cout << "Введите количество вершин: ";
    cin >> V;
    cout << "Введите количество ребер: ";
    cin >> E;

    Graph graph( V, E );

    cout << "Введите ребра (формат: src dest weight):\n";
    for ( int i = 0; i < E; i++ )
    {
        int Src, Dest, Weight;
        cin >> Src >> Dest >> Weight;
        graph.AddEdge( Src, Dest, Weight );
    }

    return graph;
}


int main()
{
    setlocale( LC_ALL, "" );


    cout << "Создание графа...\n";
    Graph graph = InputGraph();

    KruskalMST( graph );


    return 0;
}
