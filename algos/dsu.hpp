#include <numeric>
#include <vector>

struct DSU {
    std::vector<int> par;
    std::vector<int> sz;

    DSU(int n) : par(n, -1), sz(n, 1) { std::iota(par.begin(), par.end(), 0); }

    int size(int u) { return sz[get(u)]; }

    int get(int u) {
        while (u != par[u]) {
            u = par[u] = par[par[u]];
        }
        return u;
    }

    void merge(int u, int v) {
        u = get(u);
        v = get(v);
        if (u == v) {
            return;
        }
        if (sz[u] > sz[v]) {
            std::swap(u, v);
        }
        par[v] = u;
        sz[u] += sz[v];
    }
};
