#include <bits/stdc++.h>

/* debug template start */
template <typename T>
concept Container = requires(T t) {
    { t.begin() } -> std::same_as<typename T::iterator>;
    { t.end() } -> std::same_as<typename T::iterator>;
};

template <typename T>
concept Formattable = requires(T t) {
    { std::format("{}", t) };
};

template <typename T>
    requires Formattable<T> && (!Container<T>)
std::string _format(const T& v) {
    return std::format("{}", v);
}

template <typename T1, typename T2>
std::string _format(std::pair<T1, T2> p) {
    return std::format("({},{})", _format(p.first), _format(p.second));
}

template <typename K, typename V>
std::string _format(const std::map<K, V>& m) {
    std::string s;
    for (auto it = m.begin(); it != m.end(); ++it) {
        auto [k, v] = *it;
        s += std::format("{} : {}", _format(k), _format(v));
        if (it != std::prev(m.end())) {
            s += ", ";
        }
    }
    return std::format("{{{}}}", s);
}

template <typename T>
    requires Container<T>
std::string _format(const T& v) {
    std::string s;
    for (auto it = v.begin(); it != v.end(); ++it) {
        s += _format(*it);
        if (it != std::prev(v.end())) {
            s += ", ";
        }
    }
    return std::format("[{}]", s);
}

void debug_print() { std::cerr << std::endl; }

template <typename H, typename... T>
void debug_print(H h, T... t) {
    std::cerr << _format(h) << " ";
    debug_print(t...);
}

#ifdef DEBUG
#define dbg(...)                                                   \
    std::cerr << "" << __LINE__ << ": [" << #__VA_ARGS__ << "]: "; \
    debug_print(__VA_ARGS__);
#define dbgend() std::cerr << "======================" << std::endl;
#else
#define dbg(...)
#define dbgend()
#endif

/* debug template end */

void solve() {}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}

