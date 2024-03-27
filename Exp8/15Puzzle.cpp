#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;

#define N 4

struct State
{
    vector<vector<int>> board;
    int x, y; // Position of the empty cell (0)
    int cost; // Cost of the current state (no. of misplaced tiles)
    int level;
    State *parent;
};

// Comparator for priority queue based on cost and level
struct CompareCost
{
    bool operator()(const State &s1, const State &s2) const
    {
        return (s1.cost + s1.level) > (s2.cost + s2.level);
    }
};

// Offsets for neighboring cells
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// Calculate the cost of a state (no. of misplaced tiles)
int calculateCost(const vector<vector<int>> &initial, const vector<vector<int>> &goal)
{
    int cost = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (initial[i][j] != 0 && initial[i][j] != goal[i][j])
                ++cost;
    return cost;
}

// Check if a cell is within the bounds of the puzzle grid
bool isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Print the current state of the board
void printBoard(const vector<vector<int>> &board)
{
    for (const vector<int> &row : board)
    {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
    cout << endl;
}

// Print the path from the initial state to the goal state
void printPath(const State &state)
{
    if (state.level == 0)
        return;
    printPath(*state.parent);
    printBoard(state.board);
}

// Branch and Bound algorithm
void solve(const vector<vector<int>> &initial, const vector<vector<int>> &goal, int x, int y)
{
    priority_queue<State, vector<State>, CompareCost> pq;

    State startState = {initial, x, y, calculateCost(initial, goal), 0, nullptr};
    pq.push(startState);

    cout << "Solution:" << endl;

    while (!pq.empty())
    {
        // Get the state with the lowest cost and level
        State curr = pq.top();
        pq.pop();

        // If the current state is the goal state, print the path and return
        if (curr.cost == 0)
        {
            printPath(curr);
            return;
        }

        // Generate child states by moving the empty cell
        for (int i = 0; i < 4; ++i)
        {
            cout << "Level: " << curr.level + 1 << endl;
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if (isSafe(newX, newY))
            {
                State nextState = {curr.board, newX, newY, 0, curr.level + 1, &curr};
                swap(nextState.board[curr.x][curr.y], nextState.board[newX][newY]);
                nextState.cost = calculateCost(nextState.board, goal);

                pq.push(nextState);
            }
        }
    }
}

int main()
{
    vector<vector<int>> initial(N, vector<int>(N));
    vector<vector<int>> goal = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}};

    cout << "Enter the initial state (space separated numbers, 0 represents empty cell):" << endl;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> initial[i][j];

    int emptyCellX, emptyCellY;
    cout << "Enter the row and column of the empty cell (0-indexed): ";
    cin >> emptyCellX >> emptyCellY;

    // Check if the empty cell position is valid
    if (!isSafe(emptyCellX, emptyCellY) || initial[emptyCellX][emptyCellY] != 0)
    {
        cout << "Invalid empty cell position." << endl;
        return -1;
    }

    cout << "Initial state:" << endl;

    // Solve the puzzle
    solve(initial, goal, emptyCellX, emptyCellY);
    return 0;
}
