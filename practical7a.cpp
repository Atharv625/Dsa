#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
using namespace std;

class Graph
{
private:
    vector<vector<int>> adjacencyMatrix;
    int vertices;

public:
    Graph(int n);
    void accept();
    void display() const;
    void prims() const;
};

Graph::Graph(int n) : vertices(n)
{
    adjacencyMatrix.resize(n, vector<int>(n, 0));
}

void Graph::accept()
{
    int edges, src, dest, cost;

    cout << "Enter the number of edges: ";
    cin >> edges;

    for (int i = 0; i < edges; i++)
    {
        cout << "Enter source, destination, and cost: ";
        cin >> src >> dest >> cost;

        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices)
        {
            adjacencyMatrix[src][dest] = cost;
            adjacencyMatrix[dest][src] = cost; // For an undirected graph
        }
        else
        {
            cout << "Invalid vertices! Please enter valid indices.\n";
            i--; // Retry the current iteration
        }
    }
}

void Graph::display() const
{
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            cout << adjacencyMatrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void Graph::prims() const
{
    vector<bool> visited(vertices, false);
    int totalCost = 0;

    int src;
    cout << "\nEnter start vertex: ";
    cin >> src;

    if (src < 0 || src >= vertices)
    {
        cout << "Invalid start vertex!" << endl;
        return;
    }

    visited[src] = true;

    cout << "\nEdges in the MST:\n";

    for (int count = 0; count < vertices - 1; count++)
    {
        int minCost = INT_MAX;
        int u = -1, v = -1;

        for (int i = 0; i < vertices; i++)
        {
            if (visited[i])
            {
                for (int j = 0; j < vertices; j++)
                {
                    if (!visited[j] && adjacencyMatrix[i][j] && adjacencyMatrix[i][j] < minCost)
                    {
                        minCost = adjacencyMatrix[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u != -1 && v != -1)
        {
            cout << "Edge from " << u << " to " << v << " with cost: " << minCost << endl;
            totalCost += minCost;
            visited[v] = true;
        }
        else
        {
            cout << "Graph is disconnected, unable to form a complete MST." << endl;
            break;
        }
    }

    cout << "\nTotal cost of MST: " << totalCost << endl;
}

int main()
{
    int vertices;

    cout << "Enter the number of vertices: ";
    cin >> vertices;

    if (vertices <= 0)
    {
        cout << "Invalid number of vertices!" << endl;
        return 1;
    }

    Graph g(vertices);
    g.accept();
    g.display();
    g.prims();

    return 0;
}
