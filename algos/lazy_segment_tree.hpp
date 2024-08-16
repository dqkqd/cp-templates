#include <bits/stdc++.h>

template <typename T>
concept IsOp = requires(T t, const T& o) {
    { t.apply(o) } -> std::same_as<void>;
    { T() };
};

template <typename T, typename U>
concept IsNode = requires(T t, const T& a, const T& b, const U& o) {
    { t.apply(o) } -> std::same_as<void>;
    { a + b } -> std::same_as<T>;
    { T() };
};

template <typename Node, typename Op>
    requires IsOp<Op> && IsNode<Node, Op>
struct LazySegmentTree {
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

    Node get(int l, int r) { return get(1, 0, n, l, r); }

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

    void set(int l, int r, const Op& op) { set(1, 0, n, l, r, op); }
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
