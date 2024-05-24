#include <iostream>
#include <vector>
#include <string>

using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#define int long long

using namespace std;

const int K = 26;
const char FirstChar = 'a';

class Trie
{
private:
    void add(const string& s, int pos)
    {
        if (pos == (int)s.size())
        {
            end = true;
            return;
        }
        char c = s[pos] - FirstChar;
        if (next[c] == nullptr)
        {
            next[c] = new Trie();
            next[c]->parent = this;
            next[c]->c = c;
        }
        next[c]->add(s, pos + 1);
    }

    bool Has_in(const string& s, int pos)
    {
        if (pos == (int)s.size())
            return this->end;
        char c = s[pos] - FirstChar;
        if (this->next[c] == nullptr)
            return false;
        return next[c]->Has_in(s, pos + 1);
    }

public:
    Trie* next[K];
    Trie* link = nullptr;
    Trie* parent = nullptr;
    char c;
    bool end = false;

    Trie() {
        fill(next, next + K, nullptr);
    }

    void add(const string& s)
    {
        add(s, 0);
    }

    bool Has_in(const string& s)
    {
        return Has_in(s, 0);
    }
};

void axo_korasik(Trie* root)
{
    queue<Trie*> q;
    q.push(root);
    while (!q.empty())
    {
        Trie* cur = q.front();
        q.pop();
        for (int i = 0; i < K; ++i)
        {
            if (cur->next[i] != nullptr)
            {
                q.push(cur->next[i]);
            }
        }
        if (cur->parent == nullptr)
        {
            for (int i = 0; i < K; ++i)
            {
                if (cur->next[i] == nullptr)
                {
                    cur->next[i] = cur;
                }
            }
            continue;
        }

        if (cur->parent->parent == nullptr) //if (cur->parent == root)
        {
            cur->link = cur->parent;
        }
        else
        {
            cur->link = cur->parent->link->next[cur->c];
        }
        for (int i = 0; i < K; i++)
        {
            if (cur->next[i] == nullptr)
            {
                cur->next[i] = cur->link->next[i];
            }
        }
        if (cur->link->end)
            cur->end = true;
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    Trie* root = new Trie();

    return 0;
}

const int K = 26;

class Trie
{
private:
    Trie* next[K];
    Trie* link = nullptr;
    Trie* parent = nullptr;
    char c;
    int size = 1;
    bool end = false;

public:
    Trie() {
        fill(next, next + K, nullptr);
        size = 1;
    }

    void add(const string& s, int pos)
    {
        if (pos == (int)s.size())
        {
            end = true;
            return;
        }
        char c = s[pos] - 'a';
        if (next[c] == nullptr)
        {
            next[c] = new Trie();
            next[c]->parent = this;
            next[c]->c = c;
            size++;
        }
        next[c]->add(s, pos + 1);
    }

    bool Has_in(const string& s, int pos)
    {
        if (pos == (int)s.size())
        {
            return this->end;
        }
        char c = s[pos] - 'a';
        if (this->next[c] == nullptr)
        {
            return false;
        }
        return next[c]->Has_in(s, pos + 1);
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    Trie* root = new Trie();

    return 0;
}
