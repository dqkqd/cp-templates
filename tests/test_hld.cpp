#include <gtest/gtest.h>

#include "hld.hpp"

auto graph() {
    // https://cp-algorithms.com/graph/hld.png
    std::vector<std::vector<int>> g(16);

    auto add_edge = [&](int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    };

    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(0, 3);

    add_edge(1, 4);
    add_edge(1, 5);

    add_edge(2, 6);
    add_edge(2, 7);

    add_edge(5, 8);
    add_edge(5, 9);

    add_edge(6, 10);
    add_edge(7, 11);

    add_edge(10, 12);
    add_edge(10, 13);
    add_edge(10, 14);

    add_edge(13, 15);

    return g;
}

TEST(HLD, Size) {
    auto hld = HLD(graph(), 0);
    EXPECT_EQ(hld.size[0], 16);
    EXPECT_EQ(hld.size[1], 5);
    EXPECT_EQ(hld.size[2], 9);
    EXPECT_EQ(hld.size[3], 1);
    EXPECT_EQ(hld.size[4], 1);
    EXPECT_EQ(hld.size[5], 3);
    EXPECT_EQ(hld.size[6], 6);
    EXPECT_EQ(hld.size[7], 2);
    EXPECT_EQ(hld.size[8], 1);
    EXPECT_EQ(hld.size[9], 1);
    EXPECT_EQ(hld.size[10], 5);
    EXPECT_EQ(hld.size[11], 1);
    EXPECT_EQ(hld.size[12], 1);
    EXPECT_EQ(hld.size[13], 2);
    EXPECT_EQ(hld.size[14], 1);
    EXPECT_EQ(hld.size[15], 1);
}

TEST(HLD, Head) {
    auto hld = HLD(graph(), 0);
    EXPECT_EQ(hld.head[0], 0);
    EXPECT_EQ(hld.head[1], 1);
    EXPECT_EQ(hld.head[2], 0);
    EXPECT_EQ(hld.head[3], 3);
    EXPECT_EQ(hld.head[4], 4);
    EXPECT_EQ(hld.head[5], 1);
    EXPECT_EQ(hld.head[6], 0);
    EXPECT_EQ(hld.head[7], 7);
    EXPECT_EQ(hld.head[8], 1);
    EXPECT_EQ(hld.head[9], 9);
    EXPECT_EQ(hld.head[10], 0);
    EXPECT_EQ(hld.head[11], 7);
    EXPECT_EQ(hld.head[12], 12);
    EXPECT_EQ(hld.head[13], 0);
    EXPECT_EQ(hld.head[14], 14);
    EXPECT_EQ(hld.head[15], 0);
}

TEST(HLD, IsAncestor) {
    auto hld = HLD(graph(), 0);
    EXPECT_TRUE(hld.is_ancestor(2, 6));
    EXPECT_TRUE(hld.is_ancestor(2, 7));
    EXPECT_TRUE(hld.is_ancestor(2, 2));
    EXPECT_FALSE(hld.is_ancestor(1, 2));
}

TEST(HLD, LCA) {
    auto hld = HLD(graph(), 0);
    EXPECT_EQ(hld.lca(0, 5), 0);
    EXPECT_EQ(hld.lca(10, 11), 2);
}

TEST(HLD, Distance) {
    auto hld = HLD(graph(), 0);
    EXPECT_EQ(hld.distance(0, 5), 2);
    EXPECT_EQ(hld.distance(10, 11), 4);
}

// https://judge.yosupo.jp/problem/lca
void test() {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        g[i].push_back(p);
        g[p].push_back(i);
    }
    auto hld = HLD(std::move(g), 0);
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << hld.lca(u, v) << std::endl;
    }
}
