#include <iostream>
#include <vector>
using namespace std;

// Print all possible solutions
void printSolutions(vector<vector<int>> &result, int n)
{
    for (vector<int> &i : result)
    {
        int count = 0;
        for (int j : i)
        {
            if (j)
                cout << "Q ";
            else
                cout << ". ";
            count++;
            if (count == n)
            {
                count = 0;
                cout << endl;
            }
        }
        cout << endl;
    }
}

// Check if Queen is safe to place
bool isSafe(vector<int> &board, int n, int row, int col)
{
    int i, j;
    for (j = 0; j < n; j++)
        if (board[n * j + col] == 1)
            return false;

    i = row, j = col;
    while (i >= 0 && j >= 0)
    {
        if (board[n * i + j] == 1)
            return false;
        i--;
        j--;
    }

    i = row, j = col;
    while (i < n && j < n)
    {
        if (board[n * i + j] == 1)
            return false;
        i++;
        j++;
    }

    i = row, j = col;
    while (i >= 0 && j < n)
    {
        if (board[n * i + j] == 1)
            return false;
        i--;
        j++;
    }

    i = row, j = col;
    while (i < n && j >= 0)
    {
        if (board[n * i + j] == 1)
            return false;
        i++;
        j--;
    }
}

void placeQueen(vector<int> &board, int n, int row, vector<vector<int>> &ans)
{
    if (row == n)
    {
        // Found a possible board configuration
        ans.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (isSafe(board, n, row, col))
        {
            board[n * row + col] = 1;
            placeQueen(board, n, row + 1, ans); // place next queen
            board[n * row + col] = 0;
        }
    }
}

vector<vector<int>> solveNQueens(int n)
{
    vector<int> board(n * n, 0);
    vector<vector<int>> ans;

    placeQueen(board, n, 0, ans);
    return ans;
}

int main()
{
    int n;
    vector<vector<int>> possibleSolns;

    cout << "Enter No. of Queens: ";
    cin >> n;
    cout << endl;

    possibleSolns = solveNQueens(n);
    cout << "Solutions:\n";
    printSolutions(possibleSolns, n);
    return 0;
}
