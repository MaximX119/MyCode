#include <iostream>
#include <vector>

using namespace std;

const int inf = 1e9;

struct Edge { int to, flow, cost; };
struct Graph
{
    int n, S, T;
    vector<Edge> edges;
    vector<vector<int>> graph;

    Graph(int n, int S, int T): n(n), S(S), T(T) {
        graph.resize(n);
    }

    void add_direct_edge(int x, int y, int cost)
    {
        graph[x].push_back(edges.size());
        edges.push_back(Edge{y, 0, cost});
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
            int residual = min(flow_limit, edges[e].cost - edges[e].flow);
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
            int flow_limit = inf;
            if (!try_aurgment(S, used, flow_limit))
                break;
            total_flow += flow_limit;
        }
        return total_flow;
    }
    void clear_flow()
    {
        for (Edge& e : Edges)
            flow[e] = 0;
    }
};

