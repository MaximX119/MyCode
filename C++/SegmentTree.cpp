#include <iostream>
#include <vector>

using namespace std;

typedef long long my_type;

const my_type e0 = -2e9;
const my_type MAXN = (1 << 17);

my_type f(my_type a, my_type b)
{
    return max(a, b);
}

struct SegmentTree
{
    my_type ar[MAXN * 2];
    long long push[MAXN * 2];
    SegmentTree() {
        fill(ar, ar + (MAXN * 2), e0);
        fill(push, push + (MAXN * 2), 0);
    }
    void update(int i, my_type val)
    {
        i += MAXN;
        ar[i] = val;
        for (i /= 2; i > 0; i /= 2)
        {
            ar[i] = f(ar[2 * i], ar[2 * i + 1]);
        }
    }

    my_type get(int v, int l, int r, int seg_l, int seg_r)
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

    void build()
    {
        for (int i = MAXN - 1; i > 0; --i)
        {
            ar[i] = f(ar[2 * i], ar[2 * i + 1]);
        }
    }

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
        if (ar[2 * v] >= l)
            return index(v * 2, l, (l + r) / 2, k);
        return index(2 * v + 1, (l + r) / 2, r, k - ar[v * 2]);
    }

};
SegmentTree t;
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);


  
    return 0;
}
