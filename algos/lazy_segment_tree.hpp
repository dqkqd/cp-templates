#include <bits/stdc++.h>

template <typename T>
struct LazySegmentTree {
    using F = std::function<T(const T&, const T&)>;

    int n;
    T init;
    F merge;
    std::vector<T> tree;
    std::vector<bool> mark;

    LazySegmentTree(int n_, T init_, F merge_ = std::plus<>())
        : n(n_),
          init(init_),
          merge(merge_),
          tree(4 << std::__lg(n), init),
          mark(4 << std::__lg(n), false) {}

    LazySegmentTree(std::vector<T> a, T init_, F merge_ = std::plus<>())
        : LazySegmentTree(a.size(), init_, merge_) {
        std::function<void(int, int, int)> build = [&](int node, int l, int r) {
            if (l == r - 1) {
                tree[node] = a[l];
            } else {
                int m = (l + r) / 2;
                build(node * 2, l, m);
                build(node * 2 + 1, m, r);
                tree[node] = init;
            }
        };
        build(1, 0, n);
    }

    void push(int node) {
        if (mark[node]) {
            tree[node * 2] = merge(tree[node * 2], tree[node]);
            tree[node * 2 + 1] = merge(tree[node * 2 + 1], tree[node]);
            mark[node * 2] = mark[node * 2 + 1] = true;
            mark[node] = false;
            tree[node] = init;
        }
    }

    T get(int node, int tl, int tr, int pos) {
        if (tl == tr - 1) {
            return tree[node];
        }
        push(node);
        int tm = (tl + tr) / 2;
        if (pos < tm) {
            return merge(get(node * 2, tl, tm, pos), tree[node]);
        }
        return merge(get(node * 2 + 1, tm, tr, pos), tree[node]);
    }

    T get(int pos) { return get(1, 0, n, pos); }

    void set(int node, int tl, int tr, int l, int r, T val) {
        if (l >= tr || r <= tl) {
            return;
        }
        if (tl >= l && tr <= r) {
            tree[node] = merge(tree[node], val);
            mark[node] = true;
            return;
        }
        push(node);
        int tm = (tl + tr) / 2;
        set(node * 2, tl, tm, l, r, val);
        set(node * 2 + 1, tm, tr, l, r, val);
    }

    void set(int l, int r, T val) { set(1, 0, n, l, r, val); }
};
