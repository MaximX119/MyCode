#include <iostream>
#include <vector>

using namespace std;

void dfs(int v, vector<vector<int>>& g, vector<char>& used)
{
    used[v] = 1;
    for (int u : g[v])
    {
        if (!used[u])
            dfs(u, g, used);
    }
}

void dfs2(
    int v,
    int part,
    vector<vector<vector<int>>>& Graph,
    vector<vector<char>>& used
) {
    used[part][v] = 1;
    for (int i : Graph[part][v])
    {
        if (!used[part ^ 1][i])
        {
            dfs2(i, part ^ 1, Graph, used);
        }
    }
}

bool try_kuhn(
    int v,
    int UsedCount,
    vector<vector<int>>& g,
    vector<int>& used, vector<int>& mt
) {
    if (used[v] == UsedCount)
        return false;
    used[v] = UsedCount;

    for (int to : g[v])
    {
        if (mt[to] == -1)
        {
            mt[to] = v;
            return true;
        }
    }

    for (int to : g[v])
    {
        if (try_kuhn(mt[to], UsedCount, g, used, mt))
        {
            mt[to] = v;
            return true;
        }
    }

    return false;
}

vector<pair<int, int>> FindMatching(vector<vector<int>>& Graph)
{
    vector<int> mt, used;
    int UsedCount = 0, l = Graph.size(), r = l;
    mt.assign(r, -1);
    used.assign(l, 0);
    for (int v = 0; v < l; ++v)
    {
        UsedCount++;
        try_kuhn(v, UsedCount, Graph, used, mt);
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < r; i++)
    {
        if (mt[i] != -1)
            ans.emplace_back(mt[i], i);
    }
    return ans;
}

signed main()
{
    int n, m, x, y;
    cin >> n >> m;
    vector<vector<int>> Graph0(n);/// out -> in
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        x--; y--;
        Graph0[x].push_back(y);
    }

    vector<bool> used0(n);
    vector<vector<int>> Graph(n);
    for (int i = 0; i < n; i++)
    {
        used0.assign(n, 0);
        dfs(i, Graph0, used0);
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                if (used0[j])
                    Graph[i].push_back(j);
            }
        }
    }

    vector<pair<int, int>> Matching = FindMatching(Graph);
    vector<vector<vector<int>>> Graph2(2, vector<vector<int>>(n));
    vector<vector<bool>> MatchingVertex(2, vector<char>(n));
    for (auto i : Matching)
    {
        Graph2[1][i.second].push_back(i.first);
        MatchingVertex[0][i.first] = 1;
        MatchingVertex[1][i.second] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j : Graph[i])
        {
            Graph2[0][i].push_back(j);
        }
    }
    vector<vector<bool>> used(2, vector<char> (n));
    for (int i = 0; i < n; i++)
    {
        if (!used[0][i] && !MatchingVertex[0][i])
            dfs2(i, 0, Graph2, used);
    }

    vector<bool> ans(n, true);
    vector<int> VertexCover, Antichains;
    for (int i = 0; i < n; i++)
    {
        if (!used[0][i] || used[1][i])
            ans[i] = 0;
        if (ans[i])
            Antichains.push_back(i);
        else
            VertexCover.push_back(i);
    }
    return 0;
}
