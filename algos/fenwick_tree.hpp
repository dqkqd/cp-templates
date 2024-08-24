#include <vector>

template <typename T>
concept Add = requires(const T& a, const T& b) {
    { a + b } -> std::same_as<T>;
};
template <typename T>
concept Sub = requires(const T& a, const T& b) {
    { a - b } -> std::same_as<T>;
};

template <typename T>
    requires Add<T> && Sub<T> && std::default_initializable<T>
struct FenwickTree {
    int n;
    std::vector<T> bit;

    FenwickTree(int n_) : n(n_ + 1), bit(n_ + 1, T{}) {}

    FenwickTree(std::vector<T> a) : FenwickTree(a.size()) {
        for (int i = 1; i < n; ++i) {
            bit[i] = bit[i] + a[i - 1];
            int r = i + (i & -i);
            if (r < n) {
                bit[r] = bit[r] + bit[i];
            }
        }
    }

    T sum(int idx) {
        auto res = T{};
        for (; idx > 0; idx -= idx & -idx) {
            res = res + bit[idx];
        }
        return res;
    }

    T sum(int l, int r) { return sum(r) - sum(l); }

    void add(int idx, T delta) {
        for (++idx; idx < n; idx += idx & -idx) {
            bit[idx] = bit[idx] + delta;
        }
    }

    int lower_bound(T s)
        requires std::totally_ordered<T>
    {
        // find min pos that [0, pos) <= s
        int pos = 0;
        for (int pw = 1 << std::__lg(n); pw; pw >>= 1) {
            if (pos + pw <= n && bit[pos + pw] <= s) {
                pos += pw;
                s -= bit[pos];
            }
        }
        return pos;
    }
};
