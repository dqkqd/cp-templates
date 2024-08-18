#include <concepts>
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T>
concept Default = requires { T{}; };
template <typename T, typename U>
concept Apply = requires(T t, const U& o) {
    { t.apply(o) } -> std::same_as<void>;
};
template <typename T>
concept Add = requires(const T& a, const T& b) {
    { a + b } -> std::same_as<T>;
};

template <typename Node, typename Op>
    requires Default<Node> && Default<Op> &&
             Apply<Op, Op> && Apply<Node, Op> && Add<Node>
struct LazySegmentTree {
    using P = std::function<bool(const Node&)>;

    int n;
    std::vector<Node> tree;
    std::vector<Op> lazy;

    LazySegmentTree(int n_)
        : n(n_),
          tree(4 << std::__lg(n), Node()),
          lazy(4 << std::__lg(n), Op()) {}

    LazySegmentTree(std::vector<Node> a) : LazySegmentTree(a.size()) {
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

    void apply(int v, const Op& op) {
        tree[v].apply(op);
        lazy[v].apply(op);
    }

    void push(int v) {
        apply(v * 2, lazy[v]);
        apply(v * 2 + 1, lazy[v]);
        lazy[v] = Op();
    }

    Node get(int v, int tl, int tr, int l, int r) {
        if (l >= tr || r <= tl) {
            return Node();
        }
        if (tl >= l && tr <= r) {
            return tree[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        return get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
    }

    Node get(int l, int r) {
        return get(1, 0, n, l, r);
    }

    void set(int v, int tl, int tr, int l, int r, const Op& op) {
        if (l >= tr || r <= tl) {
            return;
        }
        if (tl >= l && tr <= r) {
            apply(v, op);
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        set(v * 2, tl, tm, l, r, op);
        set(v * 2 + 1, tm, tr, l, r, op);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    void set(int l, int r, const Op& op) {
        set(1, 0, n, l, r, op);
    }

    int find_first(int v, int tl, int tr, int l, int r, P pred) {
        if (l >= tr || r <= tl || !pred(tree[v])) {
            return -1;
        }
        if (tl == tr - 1) {
            return tl;
        }
        push(v);
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
        push(v);
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

struct Op {
    void apply([[maybe_unused]] const Op& op) {
        throw std::logic_error("Not Implemented");
    }
};

struct Node {
    void apply([[maybe_unused]] const Op& op) {
        throw std::logic_error("Not Implemented");
    }

    friend Node operator+([[maybe_unused]] const Node& lhs,
                          [[maybe_unused]] const Node& rhs) {
        throw std::logic_error("Not Implemented");
    }
};
