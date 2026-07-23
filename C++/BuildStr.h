#pragma once

#include <charconv>
#include <type_traits>

struct Hex {
    unsigned long long value;
    explicit Hex(unsigned long long val) : value(val) {}
};

template <typename T>
struct Fmt {
    T val;
    size_t width = 0;
    char fill = ' ';
    int precision = -1;

    Fmt(T v, size_t w = 0, char f = ' ', int p = -1) 
        : val(v), width(w), fill(f), precision(p) {}
};

template <typename T>
inline Fmt<T> MakeFmt(T val, size_t width = 0, char fill = ' ', int precision = -1) {
    return Fmt<T>(val, width, fill, precision);
}

template <typename T> struct is_fmt : std::false_type {};
template <typename T> struct is_fmt<Fmt<T>> : std::true_type {};
template <typename T> inline constexpr bool is_fmt_v = is_fmt<T>::value;
template <typename...> inline constexpr bool dependent_false_v = false;

template <typename... Args>
std::string BuildStr(const Args&... args)
{
    std::string result;
    result.reserve(256);

    auto append_val = [&result](const auto& val) {
        using T = std::decay_t<decltype(val)>;
        
        if constexpr (std::is_convertible_v<T, std::string_view>)
        {
            result.append(val);
        }
        else if constexpr (std::is_same_v<T, char>)
        {
            result.push_back(val);
        }
        else if constexpr (is_fmt_v<T>)
        {
            using ValT = std::decay_t<decltype(val.val)>;
            
            char buffer[128];
            char* ptr = nullptr;
            std::errc ec{};

            if constexpr (std::is_same_v<ValT, Hex>)
            {
                auto res = std::to_chars(buffer, buffer + sizeof(buffer), val.val.value, 16);
                ptr = res.ptr;
                ec = res.ec;
            }
            else if constexpr (std::is_floating_point_v<ValT>)
            {
                if (val.precision >= 0)
                {
                    auto res = std::to_chars(buffer, buffer + sizeof(buffer), val.val, std::chars_format::fixed, val.precision);
                    ptr = res.ptr; ec = res.ec;
                }
                else
                {
                    auto res = std::to_chars(buffer, buffer + sizeof(buffer), val.val);
                    ptr = res.ptr; ec = res.ec;
                }
            }
            else if constexpr (std::is_arithmetic_v<ValT>)
            {
                auto res = std::to_chars(buffer, buffer + sizeof(buffer), val.val, 10);
                ptr = res.ptr;
                ec = res.ec;
            }

            if (ec == std::errc{} && ptr != nullptr)
            {
                int len = ptr - buffer;
                if (len < val.width)
                    result.append(val.width - len, val.fill);
                
                result.append(buffer, len);
            }
        }
        else if constexpr (std::is_same_v<T, Hex>) 
        {
            char buffer[32];
            auto [ptr, ec] = std::to_chars(buffer, buffer + sizeof(buffer), val.value, 16);
            if (ec == std::errc{})
                result.append(buffer, ptr - buffer);
        }
        else if constexpr (std::is_arithmetic_v<T>) 
        {
            char buffer[128];
            auto [ptr, ec] = std::to_chars(buffer, buffer + sizeof(buffer), val);
            if (ec == std::errc{}) 
                result.append(buffer, ptr - buffer);
        }
        else
            static_assert(dependent_false_v<T>, "unknown type");
    };

    (append_val(args), ...); 
    
    return result;
}
