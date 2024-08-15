#include <bits/stdc++.h>

template <typename T>
struct SegmentTree {
    using F = std::function<T(const T&, const T&)>;
    using P = std::function<bool(const T&)>;

    int n;
    T init;
    F merge;
    std::vector<T> tree;

    SegmentTree(int n_, T init_, F merge_ = std::plus<>())
        : n(n_), init(init_), merge(merge_), tree(4 << std::__lg(n), init) {}

    SegmentTree(std::vector<T> a, T init_, F merge_ = std::plus<>())
        : SegmentTree(a.size(), init_, merge_) {
        std::function<void(int, int, int)> build = [&](int node, int l, int r) {
            if (l == r - 1) {
                tree[node] = a[l];
            } else {
                int m = (l + r) / 2;
                build(node * 2, l, m);
                build(node * 2 + 1, m, r);
                tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
            }
        };
        build(1, 0, n);
    }

    T get(int node, int tl, int tr, int l, int r) {
        if (l >= tr || r <= tl) {
            return init;
        }
        if (tl >= l && tr <= r) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(get(node * 2, tl, tm, l, r),
                     get(node * 2 + 1, tm, tr, l, r));
    }

    T get(int l, int r) { return get(1, 0, n, l, r); }

    void set(int node, int tl, int tr, int pos, T val) {
        if (tl == tr - 1) {
            tree[node] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos < tm) {
            set(node * 2, tl, tm, pos, val);
        } else {
            set(node * 2 + 1, tm, tr, pos, val);
        }
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void set(int pos, T val) { set(1, 0, n, pos, val); }

    int find_first(int node, int tl, int tr, int l, int r, P pred) {
        if (l >= tr || r <= tl || !pred(tree[node])) {
            return -1;
        }
        if (tl == tr - 1) {
            return tl;
        }
        int tm = (tl + tr) / 2;
        int pos = find_first(node * 2, tl, tm, l, r, pred);
        if (pos != -1) {
            return pos;
        }
        return find_first(node * 2 + 1, tm, tr, l, r, pred);
    }

    int find_first(int l, int r, P pred) {
        return find_first(1, 0, n, l, r, pred);
    }

    int find_last(int node, int tl, int tr, int l, int r, P pred) {
        if (l >= tr || r <= tl || !pred(tree[node])) {
            return -1;
        }
        if (tl == tr - 1) {
            return tl;
        }
        int tm = (tl + tr) / 2;
        int pos = find_last(node * 2 + 1, tm, tr, l, r, pred);
        if (pos != -1) {
            return pos;
        }
        return find_last(node * 2, tl, tm, l, r, pred);
    }

    int find_last(int l, int r, P pred) {
        return find_last(1, 0, n, l, r, pred);
    }
};
