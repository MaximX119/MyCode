#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<pair<int, int>, null_type,less<pair<int, int> >, rb_tree_tag,tree_order_statistics_node_update>

int main()
{
    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);

    int StarCount, x, y, Degree;
    cin >> StarCount;

    ordered_set Stars;
    vector<int> StarsWithThisDegreeCount(StarCount, 0);
    for (int i = 0; i < StarCount; i++)
    {
        cin >> x >> y;
        Stars.insert(make_pair(x, y));
        Degree = Stars.order_of_key({x, y});
        StarsWithThisDegreeCount[Degree]++;
    }

    for (int i = 0; i < StarCount; i++)
    {
        cout << StarsWithThisDegreeCount[i] << '\n';
    }

    return 0;
}
