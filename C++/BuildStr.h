#pragma once

#include <string>
#include <charconv>
#include <type_traits>

/// Обертка для вывода чисел в шестнадцатеричном (HEX) формате.
struct Hex {
    unsigned long long value;
    explicit Hex(unsigned long long val) : value(val) {}
};

/// Класс-модификатор для гибкого управления форматированием вывода.
template <typename T>
class Fmt {
public:
    Fmt(T v) : val(v) {}

    /// Устанавливает минимальную ширину поля вывода.
    Fmt& SetWidth(size_t w) { width = w; return *this; }

    /// Устанавливает символ заполнения для пустых мест в поле ширины.
    Fmt& SetFill(char c) { fill = c; return *this; }

    /// Устанавливает количество знаков после запятой (для чисел с плавающей точкой).
    Fmt& SetPrecision(int p) { precision = p; return *this; }

    const T& GetVal() const { return val; }
    size_t GetWidth() const { return width; }
    char GetFill() const { return fill; }
    int GetPrecision() const { return precision; }

private:
    T val;
    size_t width = 0;
    char fill = ' ';
    int precision = -1;
};

/// Создает объект Fmt
template <typename T>
inline Fmt<T> MakeFmt(T val) { return Fmt<T>(val); }

namespace detail {

template <typename T> struct is_fmt : std::false_type {};
template <typename T> struct is_fmt<Fmt<T>> : std::true_type {};
template <typename T> inline constexpr bool is_fmt_v = is_fmt<T>::value;

template <typename ValT>
inline char* WriteFmtValue(char* buffer, char* last, const ValT& val, int precision) {
    if constexpr (std::is_same_v<ValT, Hex>) {
        return std::to_chars(buffer, last, val.value, 16).ptr;
    } else if constexpr (std::is_floating_point_v<ValT>) {
        if (precision >= 0) {
            return std::to_chars(buffer, last, val, std::chars_format::fixed, precision).ptr;
        } else {
            return std::to_chars(buffer, last, val).ptr;
        }
    } else if constexpr (std::is_arithmetic_v<ValT>) {
        return std::to_chars(buffer, last, val, 10).ptr;
    }
    return nullptr;
}

template <typename T>
std::enable_if_t<std::is_convertible_v<T, std::string_view>, void>
AppendVal(std::string& result, const T& val) { 
    result.append(val); 
}

template <typename T>
std::enable_if_t<std::is_same_v<std::decay_t<T>, char>, void>
AppendVal(std::string& result, T val) { 
    result.push_back(val); 
}

template <typename T>
std::enable_if_t<std::is_same_v<std::decay_t<T>, Hex>, void>
AppendVal(std::string& result, const T& val) {
    char buffer[32];
    auto [ptr, ec] = std::to_chars(buffer, buffer + sizeof(buffer), val.value, 16);
    if (ec == std::errc{}) result.append(buffer, ptr - buffer);
}

template <typename T>
std::enable_if_t<std::is_arithmetic_v<std::decay_t<T>> && !std::is_same_v<std::decay_t<T>, char>, void>
AppendVal(std::string& result, T val) {
    char buffer[128];
    auto [ptr, ec] = std::to_chars(buffer, buffer + sizeof(buffer), val);
    if (ec == std::errc{}) result.append(buffer, ptr - buffer);
}

template <typename T>
std::enable_if_t<is_fmt_v<std::decay_t<T>>, void>
AppendVal(std::string& result, const T& fmt_obj) {
    using ValT = std::decay_t<decltype(fmt_obj.GetVal())>;
    char buffer[128];
    char* ptr = WriteFmtValue(buffer, buffer + sizeof(buffer), fmt_obj.GetVal(), fmt_obj.GetPrecision());
    if (ptr != nullptr) {
        size_t len = ptr - buffer;
        size_t width = fmt_obj.GetWidth();
        if (len < width) result.append(width - len, fmt_obj.GetFill());
        result.append(buffer, len);
    }
}

} // namespace detail

/// Собирает единую std::string строку из произвольного количества аргументов разных типов.
template <typename... Args>
inline std::string BuildStr(const Args&... args) {
    std::string result;
    result.reserve(256);
    (detail::AppendVal(result, args), ...); 
    return result;
}
