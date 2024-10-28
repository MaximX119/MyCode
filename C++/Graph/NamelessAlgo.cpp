#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

vector<vector<int> > Graph;
map<pair<int, int>, int> Edges;
vector<int> TopSortIndex, InComingDegree, Parent;
vector<long long> Distance;

void TopSort()
{
    queue<int> VertexWithZeroDegree;
    for (int i = 0; i < TopSortIndex.size(); i++)
    {
        if (InComingDegree[i] == 0)
        {
            VertexWithZeroDegree.push(i);
        }
    }
    int NextIndex = 0;
    while (VertexWithZeroDegree.size() > 0)
    {
        int Vertex = VertexWithZeroDegree.front();
        VertexWithZeroDegree.pop();
        TopSortIndex[NextIndex++] = Vertex;
        for (int i = 0; i < Graph[Vertex].size(); i++){
            InComingDegree[Graph[Vertex][i]]--;
            if (InComingDegree[Graph[Vertex][i]] == 0)
            {
                VertexWithZeroDegree.push(Graph[Vertex][i]);
            }
        }
    }
}

void NamelessAlgo(int start)
{
    TopSort();
    for (int i = 0; i < Distance.size(); i++)
    {
        Distance[i] = -1;
    }

    Distance[start] = 0;

    for (int i = 0; i < TopSortIndex.size(); i++)
    {
        int Vertex = TopSortIndex[i];
        if (Distance[Vertex] != -1)
        {
            for (int j = 0; j < Graph[Vertex].size(); j++)
            {
                int Vertex2 = Graph[Vertex][j];
                if (Distance[Vertex2] > Distance[Vertex] + Edges[{Vertex, Vertex2}] || Distance[Vertex2] == -1)
                {
                    Distance[Vertex2] = Distance[Vertex] + Edges[{Vertex, Vertex2}];
                    Parent[Vertex2] = Vertex;
                }
            }
        }
    }
}

int main()
{
    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);

    

    return 0;
}
