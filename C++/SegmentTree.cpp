#include <iostream>

using namespace std;

typedef long long my_type;

const my_type MAXN = (1 << 17);

my_type sum(my_type a, my_type b)
{
    return a + b;
}

int Min(int a, int b)
{
    return min(a, b);
}

template <typename Type>
class SegmentTree
{
private:
    Type e0;
    long long push[MAXN * 2];
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
        if (r <= seg_l || l >= seg_r) {
            return e0;
        }
        if (seg_l <= l && r <= seg_r) {
            return ar[v];
        }
        push_me(v * 2, l, (l + r) / 2);
        push_me(v * 2 + 1, (l + r) / 2, r);
        return f(get(v * 2, l, (l + r) / 2, seg_l, seg_r),
            get(v * 2 + 1, (l + r) / 2, r, seg_l, seg_r));
    }

    void add(int v, int l, int r, int seg_l, int seg_r, int x)
    {
        if (seg_r <= l || r <= seg_l)
            return;
        push_me(v, l, r);
        if (seg_l <= l && r <= seg_r)
        {
            push[v] = x;
            return;
        }
        add(v * 2, l, (l + r) / 2, seg_l, seg_r, x);
        add(v * 2 + 1, (l + r) / 2, r, seg_l, seg_r, x);
        push_me(v * 2, l, (l + r) / 2);
        push_me(v * 2 + 1, (l + r) / 2, r);
        ar[v] = f(ar[v * 2], ar[v * 2 + 1]);
    }

    int index(int v, int l, int r, int k)
    {
        if (ar[v] < k)
            return -1;
        if (l + 1 == r)
            return l;
        if (ar[2 * v] >= k)
            return index(v * 2, l, (l + r) / 2, k);
        return index(2 * v + 1, (l + r) / 2, r, k - ar[v * 2]);
    }



public:
    Type ar[MAXN * 2];

    SegmentTree(Type (*func)(Type a, Type b), Type e) {
        e0 = e;
        f = func;
        fill(ar, ar + (MAXN * 2), e0);
        fill(push, push + (MAXN * 2), 0);
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

    void add(int l, int r, int x)
    {
        add(1, 0, MAXN, l, r, x);
    }

    int index(int l, int r, int k)
    {
        return index(1, l, r, k);
    }
};

SegmentTree<long long> SumTree(sum, 0);
SegmentTree<int> MinTree(Min, 2147483647);

int main()
{
    for(int i = 0; i < MAXN; i++)
    {
        SumTree.ar[i + MAXN] = i;
        MinTree.ar[i + MAXN] = i;
    }
    SumTree.build();
    MinTree.build();

    cout << SumTree.get(19, 37) << ' ' << MinTree.get(37, 42) << '\n';

    return 0;
}
