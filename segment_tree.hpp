#include <bits/stdc++.h>

template <typename T>
struct SegmentTree {
    int n;
    T init;
    std::vector<T> tree;
    std::function<T(T, T)> merge;

    SegmentTree(int n, T init, std::function<T(T, T)> _merge)
        : n(n),
          init(init),
          tree(2 << (int(log2(n)) + 1), init),
          merge(_merge) {}

    SegmentTree(std::vector<T> a, T init, std::function<T(T, T)> merge)
        : SegmentTree(a.size(), init, merge) {
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

    T sum(int node, int tl, int tr, int l, int r) {
        if (l >= r) {
            return init;
        }
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(sum(node * 2, tl, tm, l, std::min(r, tm)),
                     sum(node * 2 + 1, tm, tr, std::max(l, tm), r));
    }

    T sum(int l, int r) { return sum(1, 0, n, l, r); }
};
