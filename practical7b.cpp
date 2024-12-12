#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
using namespace std;

class Kruskal
{
private:
    struct Edge
    {
        int v1, v2, cost;
    };

    vector<Edge> edges;
    int tot_edges, tot_nodes;

public:
    void getInput();
    void create();
    int findParent(int v, vector<int> &parent);
    void unionSets(int i, int j, vector<int> &parent);
    int minimum();
    void spanningTree();
};

void Kruskal::getInput()
{
    cout << "\nEnter total number of nodes: ";
    cin >> tot_nodes;
    cout << "Enter total number of edges: ";
    cin >> tot_edges;
    edges.resize(tot_edges);
}

void Kruskal::create()
{
    for (int k = 0; k < tot_edges; k++)
    {
        cout << "\nEnter edge " << k + 1 << " in (v1, v2) form: ";
        cin >> edges[k].v1 >> edges[k].v2;
        cout << "Enter corresponding cost: ";
        cin >> edges[k].cost;
    }
}

int Kruskal::findParent(int v, vector<int> &parent)
{
    if (parent[v] != v)
        parent[v] = findParent(parent[v], parent); // Path compression
    return parent[v];
}

void Kruskal::unionSets(int i, int j, vector<int> &parent)
{
    if (i < j)
        parent[j] = i;
    else
        parent[i] = j;
}

void Kruskal::spanningTree()
{
    vector<int> parent(tot_nodes);
    for (int i = 0; i < tot_nodes; i++)
        parent[i] = i;

    int edgeCount = 0, totalCost = 0;
    vector<pair<int, int>> mstEdges;

    while (edgeCount < tot_nodes - 1)
    {
        int minPos = minimum();
        if (minPos == -1)
            break;

        int v1 = edges[minPos].v1;
        int v2 = edges[minPos].v2;
        int cost = edges[minPos].cost;

        int parentV1 = findParent(v1, parent);
        int parentV2 = findParent(v2, parent);

        if (parentV1 != parentV2)
        {
            mstEdges.push_back({v1, v2});
            totalCost += cost;
            edgeCount++;
            unionSets(parentV1, parentV2, parent);
        }

        edges[minPos].cost = INT_MAX; // Mark the edge as used
    }

    if (edgeCount == tot_nodes - 1)
    {
        cout << "\nSpanning tree is:\n";
        cout << "----------------------------\n";
        for (const auto &edge : mstEdges)
        {
            cout << edge.first << " -- " << edge.second << endl;
        }
        cout << "----------------------------\n";
        cout << "Cost of spanning tree is: " << totalCost << endl;
    }
    else
    {
        cout << "There is no spanning tree (graph may be disconnected).\n";
    }
}

int Kruskal::minimum()
{
    int minCost = INT_MAX, minPos = -1;
    for (int i = 0; i < tot_edges; i++)
    {
        if (edges[i].cost < minCost)
        {
            minCost = edges[i].cost;
            minPos = i;
        }
    }
    return minPos;
}

int main()
{
    Kruskal obj;
    cout << "\nGraph Creation\n";
    obj.getInput();
    obj.create();
    obj.spanningTree();
    return 0;
}
