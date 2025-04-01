#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int inf = 2e9;

struct Edge {
    int to, capacity, cost, flow, rev;
};

struct Graph {
    int n, S, T;
    vector <vector <Edge>> graph;

    Graph(int n, int S, int T): n(n), S(S), T(T) {
        graph.resize(n);
    }

    void add_direct_edge(int u, int v, int capacity, int cost) {
        Edge a = {v, capacity, cost, 0, graph[v].size()};
        Edge b = {u, 0, -cost, 0, graph[u].size()};
        graph[u].push_back(a);
        graph[v].push_back(b);
    }

    pair<int, int> min_cost_max_flow() {
        int ans1 = 0, ans2 = 0, res;
        vector<int> dist(n), par(n), ind(n);
        vector<char> used(n);

        while (true)
        {
            fill(dist.begin(), dist.end(), inf);
            fill(used.begin(), used.end(), 0);
            dist[S] = 0;
            queue<int> q;
            q.push(S);
            used[S] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                used[u] = 0;
                for (int i = 0; i < graph[u].size(); ++i) {
                    Edge &e = graph[u][i];
                    if (e.flow < e.capacity && dist[u] + e.cost < dist[e.to]) {
                        dist[e.to] = dist[u] + e.cost;
                        par[e.to] = u;
                        ind[e.to] = i;
                        if (!used[e.to]) {
                            q.push(e.to);
                            used[e.to] = 1;
                        }
                    }
                }
            }

            if (dist[T] == inf)
                break;

            int flow = inf;
            for (int u = T; u != S; u = par[u]) {
                Edge &e = graph[par[u]][ind[u]];
                flow = min(flow, e.capacity - e.flow);
            }

            res = 0;
            for (int u = T; u != S; u = par[u]) {
                Edge &e = graph[par[u]][ind[u]];
                e.flow += flow;
                graph[u][e.rev].flow -= flow;
                res += e.cost;
            }

            ans1 += res * flow;
            ans2 += flow;
        }
        return {ans1, ans2};
    }
};

signed main()
{
    int n, m;
    cin >> n >> m;

    Graph g(n, 0, n - 1);

    for (int i = 0; i < m; i++) {
        int from, to, capacity, cost;
        cin >> from >> to >> capacity >> cost;
        from--; to--;
        g.add_direct_edge(from, to, capacity, cost);
    }

    auto [cost, flow] = g.min_cost_max_flow();
    cout << cost << ' ' << flow << '\n';

    return 0;
}
