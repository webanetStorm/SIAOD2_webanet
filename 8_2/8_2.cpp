#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


const int N = 8;


bool IsSafe( vector<int> board, int row, int col )
{
    for ( int i = 0; i < row; i++ )
    {
        if ( board[i] == col or abs( board[i] - col ) == abs( i - row ) )
        {
            return false;
        }
    }

    return true;
}

void SolveNQueens( int row, vector<int> board, int& solutions, int& checks )
{
    if ( row == N )
    {
        solutions++;
        return;
    }

    for ( int col = 0; col < N; col++ )
    {
        checks++;

        if ( IsSafe( board, row, col ) )
        {
            board[row] = col;
            SolveNQueens( row + 1, board, solutions, checks );
        }
    }
}


int main()
{
    setlocale( LC_ALL, "" );

    vector<int> board( N, -1 );
    int solutions = 0, checks = 0;

    SolveNQueens( 0, board, solutions, checks );

    cout << "Число решений: " << solutions << endl;
    cout << "Число проверок: " << checks << endl;

    return 0;
}
