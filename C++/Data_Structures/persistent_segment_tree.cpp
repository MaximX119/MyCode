#include <iostream>
#include <vector>

using namespace std;

int my_max(int a, int b)
{
    return max(a, b);
}

template <typename Type>
struct node
{
    node* left = nullptr;
    node* right = nullptr;
    int l, r;
    Type val, unity, neutral;
    Type (*func)(Type a, Type b);

    node(int l, int r, Type neutral, Type (*f)(Type a, Type b)) : l(l), r(r), neutral(neutral) {
        func = f;
        val = neutral;
        unity = neutral;
    }

    node* copy()
    {
        node* new_node = new node(l, r, neutral, func);
        new_node->left = left;
        new_node->right = right;
        new_node->unity = unity;
        new_node->val = val;
        new_node->func = func;
        new_node->neutral = neutral;
        return new_node;
    }

    void recalc()
    {
        unity = val;
        if (left != nullptr)
            unity = func(unity, left->unity);
        if (right != nullptr)
            unity = func(unity, right->unity);
    }

    int get(int seg_l, int seg_r)
    {
        recalc();
        if (r <= seg_l || seg_r <= l)
            return neutral;
        if (seg_l <= l && r <= seg_r)
            return unity;

        return func(val * (seg_l <= l && l < seg_r),
               func(left == nullptr ? neutral : left->get(seg_l, seg_r),
               right == nullptr ? neutral : right->get(seg_l, seg_r)));
    }

    node* update(int i, int value)
    {
        node* new_node = copy();
        if (l == i)
        {
            new_node->val = value;
            new_node->recalc();
            return new_node;
        }
        if (left != nullptr && i < left->r)
            new_node->left = left->update(i, value);
        if (right != nullptr && i >= right->l)
            new_node->right = right->update(i, value);

        new_node->recalc();
        return new_node;
    }
};

template <typename Type>
class segment_tree
{
private:
    vector<node<Type>*> roots;
    Type neutral;
    Type (*func)(Type a, Type b);

    void build(node<Type>* v, vector<int> &arr)
    {
        v->val = arr[v->l];
        v->recalc();
        if (v->r - v->l == 1)
            return;

        int mid = (v->l + 1 + v->r) / 2;
        if (mid > v->l + 1)
        {
            v->left = new node<Type>(v->l + 1, mid, neutral, func);
            build(v->left, arr);
        }
        if (mid < v->r)
        {
            v->right = new node<Type>(mid, v->r, neutral, func);
            build(v->right, arr);
        }
        v->recalc();
    }
public:
    segment_tree(vector<int> &arr, Type neutral, Type (*f)(Type a, Type b)) : neutral(neutral) {
        func = f;
        node<Type>* first_root = new node<Type>(0, arr.size(), neutral, func);
        build(first_root, arr);
        roots.push_back(first_root);
    };

    void update(int ver, int i, int value)
    {
        if (ver >= roots.size())
            return;
        node<Type>* new_root = (roots[ver]->update(i, value));
        roots.push_back(new_root);
    }

    void update_last(int i, int value)
    {
        update(roots.size() - 1, i, value);
    }

    int get(int ver, int seg_l, int seg_r)
    {
        if (ver >= roots.size())
            return 0;
        return roots[ver]->get(seg_l, seg_r);
    }
};

signed main()
{
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    segment_tree<int> segtree(arr, -1, my_max);

    cout << segtree.get(0, 0, 4) << '\n'; // 4
    segtree.update(0, 2, 100);
    segtree.update_last(3, 200);
    cout << segtree.get(0, 0, 4) << '\n'; // 4
    cout << segtree.get(1, 0, 5) << '\n'; // 100
    cout << segtree.get(2, 0, 5) << '\n'; // 200

    return 0;
}
