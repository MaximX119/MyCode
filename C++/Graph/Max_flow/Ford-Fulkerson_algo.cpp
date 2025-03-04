#include <iostream>
#include <vector>

using namespace std;

const int MAX_FLOW = 1e6;

struct Edge { int to, flow, capacity; };
struct Graph
{
    int n, S, T;
    vector<Edge> edges;
    vector<vector<int>> graph;

    Graph(int n, int S, int T): n(n), S(S), T(T) {
        graph.resize(n);
    }

    void add_direct_edge(int x, int y, int capacity)
    {
        graph[x].push_back(edges.size());
        edges.push_back(Edge{y, 0, capacity});
        graph[y].push_back(edges.size());
        edges.push_back(Edge{x, 0, 0});
    }

    bool try_aurgment(int v, vector<char>& used, int& flow_limit)
    {
        if (v == T)
            return true;
        if (used[v])
            return false;
        used[v] = true;
        for (int e : graph[v])
        {
            int residual = min(flow_limit, edges[e].capacity - edges[e].flow);
            if (residual > 0 && try_aurgment(edges[e].to, used, residual))
            {
                flow_limit = residual;
                edges[e].flow += residual;
                edges[e^1].flow -= residual;
                return true;
            }
        }
        return false;
    }

    int max_flow()
    {
        vector<char> used(n);
        int total_flow = 0;
        while (true)
        {
            fill(used.begin(), used.end(), 0);
            int flow_limit = MAX_FLOW;
            if (!try_aurgment(S, used, flow_limit))
                break;
            total_flow += flow_limit;
        }
        return total_flow;
    }

    void clear_flow()
    {
        for (Edge& e : edges)
            e.flow = 0;
    }
};

signed main()
{
    int n, S, T, m;
    cin >> n;
    Graph my_graph(n, S, T);

    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        my_graph.add_direct_edge(from, to, capacity);
    }

    cout << my_graph.max_flow();

    return 0;
}
