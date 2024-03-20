#include <iostream>
#include <limits>
#include <vector>

using namespace std;

#define INT_MAX numeric_limits<int>::max()

// Function to find the minimum key vertex from the set of vertices not yet included in MST
int findMinKey(vector<int> &key, vector<bool> &mstSet)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < key.size(); v++)
    {
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Prim's algorithm to find the Minimum Spanning Tree (MST)
void primMST(vector<vector<int>> &graph, vector<int> &parent)
{
    int V = graph.size();
    vector<int> key(V, INT_MAX);
    vector<bool> mstSet(V, false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {
        int u = findMinKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
}

// Print the preorder traversal of the Minimum Spanning Tree
void printPreorderTraversal(vector<int> &parent)
{
    cout << "The preorder traversal of the tree is found to be - ";
    for (int i = 1; i < parent.size(); i++)
        cout << parent[i] << " -> ";
    cout << endl;
}

// Traveling Salesperson Approximation Algorithm
void tspApproximation(vector<vector<int>> &graph, int V)
{
    vector<int> parent(V);
    int root = 0;

    primMST(graph, parent);

    printPreorderTraversal(parent);

    // Print the Hamiltonian path (preorder traversal with the starting point added at the end)
    cout << "Adding the root node at the end of the traced path ";
    for (int i = 0; i < V; i++)
        cout << parent[i] << " -> ";
    cout << root << " -> " << parent[0] << endl;

    // Calculate and print the cost of the Hamiltonian path
    int cost = 0;
    for (int i = 1; i < V; i++)
        cost += graph[parent[i]][i];
    cout << "Sum of all the costs in the minimum spanning tree: " << cost << "." << endl;
}

int main()
{
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V, 0));
    cout << "Enter the adjacency matrix for the graph:" << endl;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];

    tspApproximation(graph, V);
    
    return 0;
}
