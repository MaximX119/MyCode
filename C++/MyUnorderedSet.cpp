#include <iostream>

using namespace std;

const int MAXN = 1e6;

int IntHash(int& a)
{
    return a % MAXN;
}

int StringHash(string& s)
{
    int v = 0;
    for (char c : s)
    {
        v = (v * 37 + (int)(c - 'a') + 1) % MAXN;
    }
    return v;
}

template <typename Type>
class U_set
{
    private:
        int set[MAXN];
        int (*hash)(Type& a);
    public:

        int size = 0;

        U_set(int (*h)(Type& a)) {
            hash = h;
            fill(set, set + MAXN, 0);
        }

        void insert(Type a)
        {
            set[hash(a)]++;
            size++;
        }

        void erase(Type a)
        {
            if (set[hash(a)] > 0)
            {
                set[hash(a)]--;
                size--;
            }
        }

        int count(Type a)
        {
            return set[hash(a)];
        }

        bool empty()
        {
            return (size > 0);
        }

        void clear()
        {
            for (int i = 0; i < MAXN; i++)
            {
                set[i] = 0;
            }
            size = 0;
        }

        void merge(U_set& b)
        {
            for (int i = 0; i < MAXN; i++)
            {
                if (set[i] + b.set[i] > 0 && set[i] * b.set[i] == 0)
                {
                    size++;
                }
                set[i] += b.set[i];
            }
        }

        U_set operator + (const U_set& other) const
        {
            U_set c = U_set();
            for (int i = 0; i < MAXN; i++)
            {
                c.set[i] = set[i] + other.set[i];
                if (c.set[i] > 0)
                {
                    c.size++;
                }
            }
            return c;
        }

        U_set operator - (const U_set& other) const
        {
            U_set c = U_set();
            for (int i = 0; i < MAXN; i++)
            {
                c.set[i] = max(set[i] - other.set[i], 0);
                if (c.set[i] > 0)
                {
                    c.size++;
                }
            }
            return c;
        }

        U_set operator & (const U_set& other) const
        {
            U_set c = U_set();
            for (int i = 0; i < MAXN; i++)
            {
                c.set[i] = min(set[i], other.set[i]);
                if (c.set[i] > 0)
                {
                    c.size++;
                }
            }
            return c;
        }

        U_set operator | (const U_set& other) const
        {
            U_set c = U_set();
            for (int i = 0; i < MAXN; i++)
            {
                c.set[i] = max(set[i], other.set[i]);
                if (c.set[i] > 0)
                {
                    c.size++;
                }
            }
            return c;
        }

        friend ostream& operator << (const ostream& out, U_set& a)
        {
            for (int i = 0; i < MAXN; i++)
            {
                cout << a.set[i] << ' ';
            }
            cout << '\n';
        }
};

int main()
{
    U_set<int> int_us(IntHash);
    U_set<string> str_us(StringHash);
    
    int_us.insert(1901);
    str_us.insert("abacaba");
    
    return 0;
}
