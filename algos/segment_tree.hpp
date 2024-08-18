#include <concepts>
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T>
concept Add = requires(const T& a, const T& b) {
    { a + b } -> std::same_as<T>;
};

template <typename Node>
    requires Add<Node> && std::default_initializable<Node>
struct SegmentTree {
    using P = std::function<bool(const Node&)>;

    int n;
    std::vector<Node> tree;

    SegmentTree(int n_) : n(n_), tree(4 << std::__lg(n), Node()) {}

    SegmentTree(std::vector<Node> a) : SegmentTree(a.size()) {
        std::function<void(int, int, int)> build = [&](int v, int l, int r) {
            if (l == r - 1) {
                tree[v] = a[l];
            } else {
                int m = (l + r) / 2;
                build(v * 2, l, m);
                build(v * 2 + 1, m, r);
                tree[v] = tree[v * 2] + tree[v * 2 + 1];
            }
        };
        build(1, 0, n);
    }

    Node get(int v, int tl, int tr, int l, int r) {
        if (l >= tr || r <= tl) {
            return Node();
        }
        if (tl >= l && tr <= r) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
    }

    Node get(int l, int r) {
        return get(1, 0, n, l, r);
    }

    void set(int v, int tl, int tr, int pos, Node val) {
        if (tl == tr - 1) {
            tree[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos < tm) {
            set(v * 2, tl, tm, pos, val);
        } else {
            set(v * 2 + 1, tm, tr, pos, val);
        }
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    void set(int pos, Node val) {
        set(1, 0, n, pos, val);
    }

    int find_first(int v, int tl, int tr, int l, int r, P pred) {
        if (l >= tr || r <= tl || !pred(tree[v])) {
            return -1;
        }
        if (tl == tr - 1) {
            return tl;
        }
        int tm = (tl + tr) / 2;
        int pos = find_first(v * 2, tl, tm, l, r, pred);
        if (pos != -1) {
            return pos;
        }
        return find_first(v * 2 + 1, tm, tr, l, r, pred);
    }

    int find_first(int l, int r, P pred) {
        return find_first(1, 0, n, l, r, pred);
    }

    int find_last(int v, int tl, int tr, int l, int r, P pred) {
        if (l >= tr || r <= tl || !pred(tree[v])) {
            return -1;
        }
        if (tl == tr - 1) {
            return tl;
        }
        int tm = (tl + tr) / 2;
        int pos = find_last(v * 2 + 1, tm, tr, l, r, pred);
        if (pos != -1) {
            return pos;
        }
        return find_last(v * 2, tl, tm, l, r, pred);
    }

    int find_last(int l, int r, P pred) {
        return find_last(1, 0, n, l, r, pred);
    }
};

struct Node {
    friend Node operator+([[maybe_unused]] const Node& lhs,
                          [[maybe_unused]] const Node& rhs) {
        throw std::logic_error("Not Implemented");
    }
};
