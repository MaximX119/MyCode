#include<iostream>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include<vector>

using namespace std;

double const pi = acos(-1);

struct Vectors
{
    double x, y;
    Vectors() {}
    Vectors(double x, double y) : x(x), y(y) {}
    Vectors operator + (const Vectors& other) const
    {
        return Vectors(x + other.x, y + other.y);
    }
    Vectors operator - (const Vectors& other) const
    {
        return Vectors(x - other.x, y - other.y);
    }
    Vectors operator * (const int& k) const
    {
        return Vectors(x * k, y * k);
    }
    double scl(const Vectors& other) const
    {
        return x * other.x + y * other.y;
    }
    double vct(const Vectors& other) const
    {
        return x * other.y - y * other.x;
    }
    double len2() const
    {
        return x * x + y * y;
    }
    Vectors ort_vec() const
    {
        return Vectors(-y, x);
    }
    friend istream& operator >> (istream& in, Vectors& p)
    {
        return in >> p.x >> p.y;
    }

    friend ostream& operator << (ostream& out, Vectors& p)
    {
        return out << p.x << ' ' << p.y << '\n';
    }
};

vector<Vectors> convex_hull(vector<Vectors> ar) {
    int min_i = 0;
    for (int i = 1; i < (int)ar.size(); ++i)
        if (ar[i].x < ar[min_i].x || ar[i].x == ar[min_i].x && ar[i].y < ar[min_i].y)
            min_i = i;
    swap(ar[0], ar[min_i]);
    Vectors o = ar[0];
    sort(ar.begin() + 1, ar.end(), [&o](const Vectors& a, const Vectors& b) {
        double v = (a - o).vct(b - o);
        if (v != 0)
            return v > 0;
        return (a - o).len2() < (b - o).len2();
    });
    vector<Vectors> ans;
    for (Vectors p : ar) {
        while (ans.size() >= 2 && (ans.back() - ans[ans.size() - 2]).vct(p - ans.back()) <= 0)
            ans.pop_back();
        ans.push_back(p);
    }
    return ans;
}

int main()
{
    cin.tie(0);cout.tie(0);
    ios_base::sync_with_stdio(0);


  
    return 0;
}
