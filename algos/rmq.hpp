#include <bit>
#include <functional>
#include <vector>

template <typename T>
struct RMQ {
    using F = std::function<T(const T&, const T&)>;

    int n;
    int log;
    std::vector<std::vector<T>> table;
    F cmp;

    RMQ(const std::vector<T>& a, F cmp_)
        : n(a.size()),
          log(std::bit_width(a.size())),
          table(log, std::vector<T>(n + 1)),
          cmp(cmp_) {
        std::copy(a.begin(), a.end(), table[0].begin());
        for (int i = 1; i <= log; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                table[i][j] =
                    cmp(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T query(int l, int r) {
        size_t d = r - l;
        int x = std::bit_width(d) - 1;
        return cmp(table[x][l], table[x][r - (1 << x)]);
    }
};
