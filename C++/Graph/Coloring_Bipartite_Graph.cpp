#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int Left, Right, Color;
    Edge() {}
    Edge(int Left, int Right): Left(Left), Right(Right){}
};

int FreeColor(int v, int part, vector<vector<vector<pair<int, int>>>>& VertexToColor)
{
    for (int c = 0; c < VertexToColor[part][v].size(); c++)
    {
        if (VertexToColor[part][v][c].first == -1)
            return c;
    }
}

void invert_path(
    int Vertex,
    int a_now,
    int b_next, int part,
    vector<Edge>& Edges,
    vector<vector<vector<pair<int, int>>>>& VertexToColor
) {
    if (VertexToColor[part][Vertex][a_now] == make_pair(-1, -1))
    {
        VertexToColor[part][Vertex][b_next] = {-1, -1};
        return;
    }
    int Next = VertexToColor[part][Vertex][a_now].first,
    e = VertexToColor[part][Vertex][a_now].second;

    invert_path(Next, b_next, a_now, part ^ 1, Edges, VertexToColor);

    Edges[e].Color = b_next;
    VertexToColor[part][Vertex][a_now] = {-1, -1};
    VertexToColor[part][Vertex][b_next] = {Next, e};
    VertexToColor[part ^ 1][Next][b_next] = {Vertex, e};
}

void ColoringtGraph(vector<Edge>& Edges, vector<vector<vector<pair<int, int>>>>& VertexToColor)
{
    int ColorCount = VertexToColor[0][0].size();

    for (int j = 0; j < Edges.size(); j++)
    {
        Edge e = Edges[j];
        int left = e.Left, right = e.Right;
        int a = FreeColor(left, 0, VertexToColor);
        if (VertexToColor[1][right][a].first == -1)
        {
            VertexToColor[0][left][a] = {right, j};
            VertexToColor[1][right][a] = {left, j};
            Edges[j].Color = a;
            continue;
        }
        int b = FreeColor(right, 1, VertexToColor);
        if (VertexToColor[0][left][b].first == -1)
        {
            VertexToColor[0][left][b] = {right, j};
            VertexToColor[1][right][b] = {left, j};
            Edges[j].Color = b;
            continue;
        }
        
        invert_path(left, b, a, 0, Edges, VertexToColor);
        VertexToColor[0][left][b] = {right, j};
        VertexToColor[1][right][b] = {left, j};
        Edges[j].Color = b;
    }
}

int main()
{
    int l, r, m, x, y;
    vector<vector<vector<pair<int, int>>>> Graph(2);
    vector<vector<int>> Degree(2);

    cin >> l >> r >> m;
    Graph[0].resize(l);
    Graph[1].resize(r);
    Degree[0].resize(l);
    Degree[1].resize(r);
    vector<Edge> Edges(m);

    int ColorCount = -1;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        x--; y--;
        Edges[i] = Edge(x, y);
        Graph[0][x].push_back({y, i});
        Graph[1][y].push_back({x, i});
        Degree[0][x]++;
        Degree[1][y]++;
        ColorCount = max(ColorCount, Degree[0][x]);
        ColorCount = max(ColorCount, Degree[1][y]);
    }

    vector<vector<vector<pair<int, int>>>> VertexToColor(2);
    VertexToColor[0].resize(l, vector<pair<int, int>> (ColorCount, {-1, -1}));
    VertexToColor[1].resize(r, vector<pair<int, int>> (ColorCount, {-1, -1}));

    ColoringtGraph(Edges, VertexToColor);

    cout << ColorCount << '\n';
    for (Edge e : Edges)
        cout << e.Color + 1 << ' ';
    return 0;
}
