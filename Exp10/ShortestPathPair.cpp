#include <iostream>
#include <vector>
#include <algorithm>

#define INF 99999

using namespace std;

void printMatrix(vector<vector<int>> &dist)
{
    int V = dist.size();
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall(vector<vector<int>> &dist)
{
    int V = dist.size();
    for (int k = 0; k < V; k++)
    {
        // Update shortest paths considering vertex k
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
        cout << "\nMatrix after considering vertex " << k + 1 << ":\n";
        printMatrix(dist);
    }
}

int main()
{
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));

    cout << "Enter the adjacency matrix (Enter -1 for unreachable edges):\n";
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cin >> graph[i][j];
            if (graph[i][j] == -1)
                graph[i][j] = INF;
        }
    }

    floydWarshall(graph);
    return 0;
}
