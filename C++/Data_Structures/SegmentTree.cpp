#include <iostream>
#include <vector>

using namespace std;

auto sum(auto a, auto b)
{
    return a + b;
}

auto Min(auto a, auto b)
{
    if (a < b)
        return a;
    return b;
}

template <typename Type>
class SegmentTree
{
private:
    Type e0;
    int MAXN;
    vector<Type> ar, push;
    Type (*f)(Type a, Type b);

    void push_me(int v, int l, int r)
    {
        ar[v] += push[v];
        if (l + 1 != r)
        {
            push[v * 2] += push[v];
            push[v * 2 + 1] += push[v];
        }
        push[v] = 0;
    }

    Type get(int v, int l, int r, int seg_l, int seg_r)
    {
        if (r <= seg_l || l >= seg_r)
            return e0;

        if (seg_l <= l && r <= seg_r)
            return ar[v];

        push_me(v * 2, l, (l + r) / 2);
        push_me(v * 2 + 1, (l + r) / 2, r);
        return f(get(v * 2, l, (l + r) / 2, seg_l, seg_r),
                 get(v * 2 + 1, (l + r) / 2, r, seg_l, seg_r));
    }

    void add(int v, int l, int r, int seg_l, int seg_r, Type val)
    {
        if (seg_r <= l || r <= seg_l)
            return;
        push_me(v, l, r);
        if (seg_l <= l && r <= seg_r)
        {
            push[v] = val;
            return;
        }
        add(v * 2, l, (l + r) / 2, seg_l, seg_r, val);
        add(v * 2 + 1, (l + r) / 2, r, seg_l, seg_r, val);
        push_me(v * 2, l, (l + r) / 2);
        push_me(v * 2 + 1, (l + r) / 2, r);
        ar[v] = f(ar[v * 2], ar[v * 2 + 1]);
    }

public:

    SegmentTree(int n, Type (*func)(Type a, Type b), Type e) {
        e0 = e;
        f = func;
        for (MAXN = 1; MAXN < n; MAXN <<= 1);
        ar.assign(MAXN * 2, e0);
        push.assign(MAXN * 2, 0);
    }

    void change(int i, Type val)
    {
        ar[i + MAXN] = val;
    }

    void update(int i, Type val)
    {
        i += MAXN;
        ar[i] = val;
        for (i /= 2; i > 0; i >>= 1)
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

    void add(int l, int r, Type val)
    {
        add(1, 0, MAXN, l, r, val);
    }
};

SegmentTree<double> SumTree(19, sum, 0);
SegmentTree<int> MinTree(37, Min, 2147483647);

int main()
{
    for (int i = 0; i < 19; i++)
        SumTree.change(i, (double)i * (double)i + 0.1);
    SumTree.build();

    for (int i = 0; i < 37; i++)
        MinTree.change(i, i);
    MinTree.build();

    cout << SumTree.get(7, 19) << ' ' << MinTree.get(25, 36) << '\n'; //2019.2 25

    SumTree.update(10, 101.01);
    MinTree.add(26, 36, -3);

    cout << SumTree.get(7, 19) << ' ' << MinTree.get(25, 36) << '\n'; //2020.11 23

    return 0;
}
