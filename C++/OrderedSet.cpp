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

class Utility {
public:
    static std::string TrimString(const std::string& str) {
        size_t first = str.find_first_not_of("\r\n\t ");
        if (first == std::string::npos) {
            return "";
        }
        size_t last = str.find_last_not_of("\r\n\t ");
        
        return str.substr(first, last - first + 1);
    }


    static std::string_view TrimString(std::string_view str) {
        size_t first = str.find_first_not_of("\r\n\t ");
        if (first == std::string_view::npos) {
            return "";
        }
        size_t last = str.find_last_not_of("\r\n\t ");

        return str.substr(first, last - first + 1);
    }

    inline static void StrCpy(char* dest, const size_t cnt, std::string_view src) noexcept
    {
        if (cnt > 0)
        {
            const size_t copy_len = std::min(src.size(), cnt - 1);
            if (copy_len > 0)
                std::memcpy(dest, src.data(), copy_len);
            
            dest[copy_len] = '\0';
        }
    }

    template <std::size_t N>
    inline static void StrCpy(char (&dest)[N], std::string_view src) noexcept
    {
        StrCpy(dest, N, src);
    }

    template <typename... Args>
    static std::string BuildStr(const Args&... args)
    {
        std::ostringstream oss;
        (oss << ... << args);
        return oss.str();
    }

    template <typename... Args>
    static std::string_view BuildStrView(std::ostringstream& oss, const Args&... args)
    {
        oss.str(""); oss.clear();
        oss << std::dec;
        (oss << ... << args);
        return std::string_view(oss.rdbuf()->str().data(), oss.rdbuf()->str().size());
    }
};
