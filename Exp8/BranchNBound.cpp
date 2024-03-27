#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Item Structure
struct Item
{
    float weight;
    int value;
};

// Sorting items by value-to-weight ratio
bool cmp(Item a, Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Node Structure for branch and bound tree
struct Node
{
    int level;
    int profit;
    int bound;
    float weight;
};

// Calculate upper bound of profit for a node
int bound(Node u, int n, int cap, vector<Item> &items)
{
    if (u.weight >= cap)
        return 0;

    int profit_bound = u.profit;
    float totweight = u.weight;
    int j = u.level + 1;

    // Take items until the knapsack is full
    while ((j < n) && (totweight + items[j].weight <= cap))
    {
        totweight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }

    // If capacity is left, take a fraction of the next item
    if (j < n)
        profit_bound += (cap - totweight) * items[j].value / items[j].weight;

    return profit_bound;
}

// Function to solve the knapsack problem using branch and bound approach
int knapsack(int cap, vector<Item> &items, int n)
{
    // Sort items by their value-to-weight ratio
    sort(items.begin(), items.end(), cmp);

    // Create a queue for BFS traversal
    queue<Node> Q;
    Node u, v;

    // Initialize the root node
    u.level = -1;
    u.profit = u.weight = 0;

    // Push the root node into the queue
    Q.push(u);

    int maxProfit = 0;
    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();

        // If the current node is a leaf node, continue to the next node
        if (u.level == n - 1)
            continue;

        // Consider the next level node
        v.level = u.level + 1;

        // When the current item is included
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        if (v.weight <= cap && v.profit > maxProfit)
            maxProfit = v.profit;

        // Calculate the bound for the next level node
        v.bound = bound(v, n, cap, items);

        // If the bound is greater than the current maxProfit, push the node into the queue
        if (v.bound >= maxProfit)
            Q.push(v);

        // When the current item is excluded
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, cap, items);

        // If the bound is greater than the current maxProfit, push the node into the queue
        if (v.bound >= maxProfit)
            Q.push(v);
    }

    return maxProfit;
}

int main()
{
    int cap, numItems;

    cout << "Enter the weight capacity of the knapsack: ";
    cin >> cap;
    cout << "Enter the number of items: ";
    cin >> numItems;

    vector<Item> items(numItems);
    cout << "\nEnter the weights and values of the items:\n";
    for (int i = 0; i < numItems; ++i)
    {
        cout << "Item " << i + 1 << " weight: ";
        cin >> items[i].weight;
        cout << "Item " << i + 1 << " value: ";
        cin >> items[i].value;
    }

    cout << "\nMaximum possible profit = " << knapsack(cap, items, numItems);

    return 0;
}
