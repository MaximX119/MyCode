#include <iostream>
#include <vector>

using namespace std;

const int MAXN = (1 << 17);

auto Max(auto a, auto b)
{
    if (a > b)
        return a;
    return b;
}

template <typename Type>
class SegmentTree
{
private:
    Type get(int v, int l, int r, int seg_l, int seg_r)
    {
        if (r <= seg_l || l >= seg_r) {
            return e0;
        }
        if (seg_l <= l && r <= seg_r) {
            return ar[v];
        }
        return f(get(v * 2, l, (l + r) / 2, seg_l, seg_r),
            get(v * 2 + 1, (l + r) / 2, r, seg_l, seg_r));
    }

public:
    Type e0;
    Type ar[MAXN * 2];
    Type (*f)(Type a, Type b);

    SegmentTree() {}

    SegmentTree(Type (*func)(Type a, Type b), Type e) {
        e0 = e;
        f = func;
        fill(ar, ar + (MAXN * 2), e0);
    }

    void update(int i, Type val)
    {
        i += MAXN;
        ar[i] = val;
        for (i /= 2; i > 0; i /= 2)
        {
            ar[i] = f(ar[2 * i], ar[2 * i + 1]);
        }
    }

    Type get(int l, int r)
    {
        return get(1, 0, MAXN, l, r);
    }

    void build()
    {
        for (int i = MAXN - 1; i > 0; --i)
        {
            ar[i] = f(ar[2 * i], ar[2 * i + 1]);
        }
    }
};

template <typename Type>
class HeavyLightDecomposition
{
private:

    Type e0;
    Type (*f)(Type a, Type b);
    SegmentTree<Type> segtree;
    vector<int> size, parent, head, height, tin;

    void first_init_dfs(int v, vector<vector<int>> &graph)
    {
        size[v] = 1;
        int max_chld = -1, i = 0;
        for (int u : graph[v])
        {
            if (u != parent[v]) {
                parent[u] = v;
                height[u] = height[v] + 1;
                first_init_dfs(u, graph);
                size[v] += size[u];
                if (max_chld == -1 || size[u] > size[graph[v][max_chld]])
                    max_chld = i;
            }
            ++i;
        }
        if (graph[v].size() > 0 && max_chld != -1)
            swap(graph[v][0], graph[v][max_chld]);
    }

    void second_init_dfs(int v, int &timee, vector<vector<int>> &graph, vector<Type> &weight)
    {
        tin[v] = timee;
        segtree.ar[MAXN + timee++] = weight[v];
        for (int u : graph[v])
        {
            if (u != parent[v])
            {
                if (u == graph[v][0])
                    head[u] = head[v];
                else
                    head[u] = u;
                second_init_dfs(u, timee, graph, weight);
            }
        }
    }
public:

    HeavyLightDecomposition(Type (*func)(Type a, Type b), Type e, vector<vector<int>> &graph, vector<Type> &weight)
    {
        int n = weight.size();
        size.resize(n); parent.resize(n);
        head.resize(n); height.resize(n);
        tin.resize(n);
        parent[0] = 0;
        height[0] = 0;
        e0 = e;

        segtree.e0 = e;
        segtree.f = func;
        fill(segtree.ar, segtree.ar + (MAXN * 2), e0);

        first_init_dfs(0, graph);
        int timee = 0;
        second_init_dfs(0, timee, graph, weight);
        segtree.build();
    }

    void update(int v, int val)
    {
        segtree.update(tin[v], val);
    }

    int get(int v, int u)
    {
        Type ans = e0;
        while (head[v] != head[u])
        {
            if (height[head[v]] < height[head[u]])
                swap(v, u);
            ans = max(ans, segtree.get(tin[head[v]], tin[v] + 1));
            v = parent[head[v]];
        }
        return max(ans, segtree.get(min(tin[u], tin[v]), max(tin[u], tin[v]) + 1));
    }
};

signed main()
{
    vector<int> weight = {7, 8, 6, 5};
    vector<vector<int>> graph = {{1, 2}, {}, {3}, {}};
  
    HeavyLightDecomposition<int> my_hld(Max, -100, graph, weight);
    cout << my_hld.get(0, 3) << '\n'; // 7
    cout << my_hld.get(2, 3) << '\n'; // 6
    cout << my_hld.get(1, 3) << '\n'; // 8

    my_hld.update(0, 19);

    cout << my_hld.get(0, 3) << '\n'; // 19

    return 0;
}
