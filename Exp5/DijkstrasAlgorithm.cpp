#include <iostream>
#include <vector>
#include <list>

#define INT_MAX 0x7FFFFFFF

using namespace std;

class MinHeap
{
    vector<pair<int, int>> heap;

public:
    void push(pair<int, int> value)
    {
        heap.push_back(value);
        int index = heap.size() - 1;

        // Heapify up to maintain the min-heap property
        while (index > 0 && heap[(index - 1) / 2].first > heap[index].first)
        {
            swap(heap[(index - 1) / 2], heap[index]);
            index = (index - 1) / 2;
        }
    }

    pair<int, int> pop()
    {
        pair<int, int> top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        int index = 0;
        // Heapify down to maintain the min-heap property
        while (true)
        {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int minIndex = index;

            if (leftChild < heap.size() && heap[leftChild].first < heap[minIndex].first)
                minIndex = leftChild;

            if (rightChild < heap.size() && heap[rightChild].first < heap[minIndex].first)
                minIndex = rightChild;

            if (minIndex != index)
            {
                swap(heap[index], heap[minIndex]);
                index = minIndex;
            }
            else
                break;
        }

        return top;
    }

    bool empty()
    {
        return heap.empty();
    }
};

class Graph
{
    int V;
    vector<list<pair<int, int>>> adj;

public:
    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w)
    {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void shortestPath(int source)
    {
        MinHeap minHeap;
        vector<int> dist(V, INT_MAX);

        minHeap.push(make_pair(0, source));
        dist[source] = 0;

        while (!minHeap.empty())
        {
            int u = minHeap.pop().second;

            for (pair<int, int> &edge : adj[u])
            {
                int v = edge.first;
                int weight = edge.second;

                if (dist[v] > dist[u] + weight)
                {
                    dist[v] = dist[u] + weight;
                    minHeap.push(make_pair(dist[v], v));
                }
            }
        }

        cout << "\n\nVertex   Distance from Source\n";
        for (int i = 0; i < V; i++)
            cout << i << "\t\t" << (dist[i] == INT_MAX ? -1 : dist[i]) << endl;
    }
};

int main()
{
    int V, E, u, v, w, source;

    cout << "Enter No. of Vertices and Edges: ";
    cin >> V >> E;
    Graph g(V);

    cout << "\nEnter Edges (first vertex, second vertex, weight):" << endl;
    for (int i = 0; i < E; ++i)
    {
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    cout << "\n\nEnter source vertex: ";
    cin >> source;

    g.shortestPath(source);
    return 0;
}
