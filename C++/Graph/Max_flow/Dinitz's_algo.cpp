#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int inf = 2e9;

struct Edge { int from, to, flow, capacity; };
class Graph
{
public:
    int n, S, T;
    vector<Edge> edges;
    vector<vector<int>> graph;

    Graph(int n, int S, int T): n(n), S(S), T(T) {
        graph.resize(n);
    }

    void add_direct_edge(int from, int to, int capacity)
    {
        graph[x].push_back(edges.size());
        edges.push_back(Edge{from, to, 0, capacity});
        graph[y].push_back(edges.size());
        edges.push_back(Edge{to, from, 0, 0});
    }

    int max_flow()
    {
        int total_flow = 0;
        while (true)
        {
            vector<vector<int>> layered(n);
            if (!bfs(layered))
                break;
            int flow;
            while (flow = dfs(S, inf, layered))
                total_flow += flow;
        }
        return total_flow;
    }
    
    void clear_flow()
    {
        for (Edge& e : edges)
            e.flow = 0;
    }
private:
    bool bfs(vector<vector<int>> &layered)
    {
        vector<int> dist(n, inf);
        queue<int> qu;
        qu.push(S);
        dist[S] = 0;

        while (!qu.empty())
        {
            int v = qu.front();
            qu.pop();
            for (auto &ind : graph[v])
            {
                Edge e = edges[ind];
                if (e.capacity - e.flow > 0 && dist[e.to] > dist[v] + 1)
                {
                    dist[e.to] = dist[v] + 1;
                    qu.push(e.to);
                }
                if (e.capacity - e.flow > 0 && dist[e.to] == dist[v] + 1)
                {
                    layered[v].push_back(ind);
                }
            }
        }
        return (dist[T] < inf);
    }

    int dfs(int v, int flow_limit, vector<vector<int>> &layered)
    {
        if (v == T)
            return flow_limit;

        while (!layered[v].empty())
        {
            int ind = layered[v].back();
            layered[v].pop_back();

            Edge e = edges[ind];
            if (e.capacity == e.flow)
                continue;
            int flow = dfs(e.to, min(flow_limit, e.capacity - e.flow), layered);
            if (flow == 0)
                continue;
            edges[ind].flow += flow;
            edges[ind ^ 1].flow -= flow;
            layered[v].push_back(ind);
            return flow;
        }
        return 0;
    }
};

signed main()
{
    int n, m, S, T;
    cin >> n >> S >> T;
    Graph my_graph(n, S, T);
    
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        my_graph.add_direct_edge(from, to, capacity);
    }
    
    cout << my_graph.max_flow() << '\n';

    return 0;
}
