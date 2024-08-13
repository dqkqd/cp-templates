#include <bits/stdc++.h>

auto _format(auto v) { return std::format("{}", v); }
template <typename T1, typename T2>
auto _format(std::pair<T1, T2> p) {
    return std::format("({},{})", _format(p.first), _format(p.second));
}
auto _format(bool v) { return v ? "t" : "f"; }
auto _format(std::vector<bool> v) {
    std::string s;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s += ", ";
        s += v[i] ? "t" : "f";
    }
    return std::format("[{}]", s);
}
template <typename T>
auto _format(std::vector<T>& v) {
    std::string s;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s += ", ";
        s += _format(v[i]);
    }
    return std::format("[{}]", s);
}
void debug_print() { std::cerr << std::endl; }
template <typename H, typename... T>
void debug_print(H h, T... t) {
    std::cerr << _format(h) << " ";
    debug_print(t...);
}
// clang-format off
#ifdef DEBUG
#define dbg(...) std::cerr << "" << __LINE__ << ": [" << #__VA_ARGS__ << "]: "; debug_print(__VA_ARGS__);
#define dbgend() std::cerr << "======================" << std::endl;
#else
#define dbg(...)
#define dbgend()
#endif
// clang-format on

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
