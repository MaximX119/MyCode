#include <iostream>
#include <random>
#include <tuple>

using namespace std;

mt19937 rng(37);

class Treap
{
private:
    int x, y;
    Treap* left = nullptr;
    Treap* right = nullptr;

    void Recalc()
    {
        size = 1 + (left == nullptr ? 0 : left->size) + (right == nullptr ? 0 : right->size);
    }

    int GetSize(Treap* a)
    {
        return (a != nullptr ? a->size : 0);
    }

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

    tuple<Treap*, Treap*, Treap*> Split3(Treap* a, int x)
    {
        Treap *a1, *a2, *a3;
        tie(a1, a2) = Split(a, x);
        tie(a2, a3) = Split(a2, x + 1);
        return make_tuple(a1, a2, a3);
    }

    pair<Treap*, Treap*> SplitSize(Treap* a, int size)
    {
        if (a == nullptr)
            return { nullptr , nullptr };
        if (GetSize(a->left) < size)
        {
            auto p = SplitSize(a->right, size - GetSize(a->left) - 1);
            a->right = p.first;
            a->Recalc();
            return { a, p.second };
        }
        else
        {
            auto p = SplitSize(a->left, size);
            a->left = p.second;
            a->Recalc();
            return { p.first, a };
        }
    }

public:
    int size = 1;
    Treap() {}
    Treap(int x, int y) : x(x), y(y) {}

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
        if (a2 != nullptr)
            a2 = Merge(a2->left, a2->right);
        return Merge(a1, Merge(a2, a3));
    }

    bool Has_in(Treap* a, int x)
    {
        if (a->x == x)
            return 1;
        if (a->x < x && a->right != nullptr)
            return Has_in(a->right, x);
        if (a->x > x && a->left != nullptr)
            return Has_in(a->left, x);
        return 0;
    }

    int Next_Element(Treap* root, int x)
    {
        Treap *a1, *a2, *a3, *a;
        tie(a1, a2, a3) = Split3(root, x);
        a = a3;
        if (a == nullptr)
        {
            root = Merge(a1, Merge(a2, a3));
            return -1000000019;
        }
        while (a->left != nullptr)
            a = a->left;
        root = Merge(a1, Merge(a2, a3));
        return a->x;
    }

    int Previous_Element(Treap* root, int x)
    {
        Treap *a1, *a2, *a3, *a;
        tie(a1, a2, a3) = Split3(root, x);
        a = a1;
        if (a == nullptr)
        {
            root = Merge(a1, Merge(a2, a3));
            return -1000000019;
        }
        while (a->right != nullptr)
            a = a->right;
        root = Merge(a1, Merge(a2, a3));
        return a->x;
    }

    int Count(Treap* a, int x)
    {
        Treap *a1, *a2, *a3;
        tie(a1, a2, a3) = Split3(a, x);
        int res = GetSize(a2);
        a = Merge(a1, Merge(a2, a3));
        return res;
    }

    int Count_Less(Treap* a, int x)
    {
        Treap *a1, *a2, *a3;
        tie(a1, a2, a3) = Split3(a, x);
        int res = GetSize(a1);
        a = Merge(a1, Merge(a2, a3));
        return res;
    }

    int Kth_Element(Treap* a, int k)
    {
        auto p = SplitSize(a, k);
        auto q = SplitSize(p.first, k - 1);
        int res = q.second->x;
        a = Merge(Merge(q.first, q.second), p.second);
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Treap* root = nullptr;

    return 0;
}
