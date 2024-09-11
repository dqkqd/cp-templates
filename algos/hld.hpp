#include <algorithm>
#include <vector>

struct HLD {
    std::vector<std::vector<int>> g;
    std::vector<int> parent, depth, size, in, out, head;
    int cur = 0;

    HLD(std::vector<std::vector<int>>&& _g, int root = 0)
        : g(_g),
          parent(g.size(), -1),
          depth(g.size()),
          size(g.size()),
          in(g.size()),
          out(g.size()),
          head(g.size(), root) {
        dfs_size(root);
        dfs_hld(root);
    }

    void dfs_size(int u) {
        if (parent[u] != -1) {
            const auto ret = std::ranges::remove(g[u], parent[u]);
            g[u].erase(ret.begin(), ret.end());
        }

        size[u] = 1;
        for (auto& v : g[u]) {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            dfs_size(v);
            size[u] += size[v];
            if (size[v] > size[g[u][0]]) {
                std::swap(v, g[u][0]);
            }
        }
    }

    void dfs_hld(int u) {
        in[u] = cur++;
        for (auto v : g[u]) {
            head[v] = v == g[u][0] ? head[u] : v;
            dfs_hld(v);
        }
        out[u] = cur;
    }

    bool is_ancestor(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                u = parent[head[u]];
            } else {
                v = parent[head[v]];
            }
        }
        return depth[u] < depth[v] ? u : v;
    }

    int distance(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};
