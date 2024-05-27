#include <iostream>
#include <string>
#include <queue>

using namespace std;

const int K = 26;
const char FirstChar = 'a';

class Trie
{
private:
    Trie* next[K];
    Trie* link = nullptr;
    Trie* parent = nullptr;
    char c;
    bool end = false;
    int count = 0;

    void insert(const string& s, int pos)
    {
        count++;
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
        next[c]->insert(s, pos + 1);
    }

    bool find(const string& s, int pos)
    {
        if (pos == (int)s.size())
        {
            return this->end;
        }

        char c = s[pos] - FirstChar;

        if (this->next[c] == nullptr)
        {
            return false;
        }

        return next[c]->find(s, pos + 1);
    }

    void erase(const string& s, int pos)
    {
        count--;

        if (parent != nullptr && count == 0)
        {
            parent->next[s[pos - 1] - FirstChar] = nullptr;
        }

        if (pos == (int)s.size()) return;

        char c = s[pos] - FirstChar;

        next[c]->erase(s, pos + 1);
    }

public:

    Trie() {
        fill(next, next + K, nullptr);
    }

    void insert(const string& s)
    {
        insert(s, 0);
    }

    bool find(string& s)
    {
        return find(s, 0);
    }

    void erase(const string& s)
    {
        erase(s, 0);
    }

    void axo_korasik()
    {
        queue<Trie*> q;
        q.push(this);
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
};

signed main()
{
    Trie* root = new Trie();

    return 0;
}
