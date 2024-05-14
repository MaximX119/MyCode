#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int K = 26;

struct Trie
{
    Trie* next[K];
    Trie* link = nullptr;
    Trie* parent = nullptr;
    char c;
    int size = 1;
    bool end = false;
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
