#include <iostream>
#include <random>
#include <tuple>

using namespace std;

mt19937 rng(37);

struct Treap
{
    int x, y, size = 1;
    Treap* left = nullptr;
    Treap* right = nullptr;
    Treap() {}
    Treap(int x, int y, int n) : x(x), y(y) {}
    void Recalc()
    {
        size = 1 + (left == nullptr ? 0 : left->size) + (right == nullptr ? 0 : right->size);
    }
};

Treap* Merge(Treap* a, Treap* b)
{
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;
    if (a->y < b->y)
    {
        a->right = Merge(a->right, b);
        a->Recalc();
        return a;
    }
    else
    {
        b->left = Merge(a, b->left);
        b->Recalc();
        return b;
    }
}

pair<Treap*, Treap*> Split(Treap* a, int key)
{
    if (a == nullptr)
        return { nullptr , nullptr };
    if (a->x < key)
    {
        auto p = Split(a->right, key);
        a->right = p.first;
        a->Recalc();
        return { a, p.second };
    }
    else
    {
        auto p = Split(a->left, key);
        a->left = p.second;
        a->Recalc();
        return { p.first, a };
    }
}

Treap* Insert(Treap* a, int x)
{
    Treap* to_add = new Treap(x, rng());
    pair<Treap*, Treap*> p = Split(a, x);
    p.second = Merge(to_add, p.second);
    return Merge(p.first, p.second);
}

Treap* Insert(Treap* a, int x, int y)
{
    Treap* to_add = new Treap(x, y);
    pair<Treap*, Treap*> p = Split(a, x);
    p.second = Merge(to_add, p.second);
    return Merge(p.first, p.second);
}

Treap* Erase(Treap* a, int x)
{
    Treap *a1, *a2, *a3;
    tie(a1, a2) = Split(a, x);
    tie(a2, a3) = Split(a2, x + 1);
    a2 = Merge(a2->left, a2->right);
    return Merge(a1, Merge(a2, a3));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Treap* root = new Treap(0, rng());
    
    return 0;
}
