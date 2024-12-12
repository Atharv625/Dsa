#include <iostream>
using namespace std;

class graph
{
    int g[20][20];
    int e, v;

public:
    void accept()
    {
        int src, dest, cost, i, j;
        cout << "\nEnter no. of vertices - ";
        cin >> v;
        cout << "\nEnter no. of edges ";
        cin >> e;

        for (i = 0; i < v; i++)
        {
            for (j = 0; j < v; j++)
            {
                g[i][j] = 0;
            }
        }

        for (i = 0; i < e; i++)
        {
            cout << "\nEnter source and destination - ";
            cin >> src >> dest;
            cout << "\nEnter the cost of edge - ";
            cin >> cost;
            g[src][dest] = cost;
            g[dest][src] = cost;
        }
    }

    void display()
    {
        int i, j;
        cout << "\nAdjacency Matrix:\n";
        for (i = 0; i < v; i++)
        {
            for (j = 0; j < v; j++)
            {
                cout << g[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void djikstra(int start)
    {
        int r[20][20], mindst, next, cnt, i, j;
        int visited[20] = {0}, distance[20], from[20];

        for (i = 0; i < v; i++)
        {
            for (j = 0; j < v; j++)
            {
                if (g[i][j] == 0)
                    r[i][j] = 9999;
                else
                    r[i][j] = g[i][j];
            }
        }

        for (i = 0; i < v; i++)
        {
            visited[i] = 0;
            from[i] = start;
            distance[i] = r[start][i];
        }

        distance[start] = 0;
        visited[start] = 1;
        cnt = v;

        while (cnt > 0)
        {
            mindst = 9999;
            for (i = 0; i < v; i++)
            {
                if (visited[i] == 0 && distance[i] < mindst)
                {
                    mindst = distance[i];
                    next = i;
                }
            }

            visited[next] = 1;

            for (i = 0; i < v; i++)
            {
                if (visited[i] == 0 && distance[i] > (mindst + r[next][i]))
                {
                    distance[i] = mindst + r[next][i];
                    from[i] = next;
                }
            }

            cnt--;
        }

        for (i = 0; i < v; i++)
        {
            cout << "\nDistance of " << i << " from " << start << " is " << distance[i] << endl;
            cout << "Path: " << i;
            j = i;
            while (j != start)
            {
                j = from[j];
                cout << " <- " << j;
            }
            cout << endl;
        }
    }
};

int main()
{
    int s;
    graph g;
    g.accept();
    g.display();
    cout << "\nEnter the starting vertex - ";
    cin >> s;
    g.djikstra(s);
    cout << endl;
    return 0;
}
