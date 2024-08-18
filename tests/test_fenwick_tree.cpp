#include <gtest/gtest.h>

#include "fenwick_tree.hpp"

TEST(FenwickTree, SumAndAdd) {
    FenwickTree<int> fen(5);

    // {5, 4, 3, 2, 1}
    fen.add(0, 5);
    fen.add(1, 4);
    fen.add(2, 3);
    fen.add(3, 2);
    fen.add(4, 1);

    EXPECT_EQ(fen.sum(1), 5);
    EXPECT_EQ(fen.sum(2), 9);
    EXPECT_EQ(fen.sum(3), 12);
    EXPECT_EQ(fen.sum(4), 14);
    EXPECT_EQ(fen.sum(5), 15);

    EXPECT_EQ(fen.sum(0, 1), 5);
    EXPECT_EQ(fen.sum(0, 2), 9);
    EXPECT_EQ(fen.sum(0, 3), 12);
    EXPECT_EQ(fen.sum(0, 4), 14);
    EXPECT_EQ(fen.sum(0, 5), 15);

    EXPECT_EQ(fen.sum(2, 5), 6);
}

TEST(FenwickTree, Build) {
    std::vector<int> a = {5, 4, 3, 2, 1};
    FenwickTree<int> fen(a);

    EXPECT_EQ(fen.sum(1), 5);
    EXPECT_EQ(fen.sum(2), 9);
    EXPECT_EQ(fen.sum(3), 12);
    EXPECT_EQ(fen.sum(4), 14);
    EXPECT_EQ(fen.sum(5), 15);

    EXPECT_EQ(fen.sum(0, 1), 5);
    EXPECT_EQ(fen.sum(0, 2), 9);
    EXPECT_EQ(fen.sum(0, 3), 12);
    EXPECT_EQ(fen.sum(0, 4), 14);
    EXPECT_EQ(fen.sum(0, 5), 15);

    EXPECT_EQ(fen.sum(2, 5), 6);
}

TEST(FenwickTree, Add) {
    FenwickTree<int> fen(7);
    fen.add(3, 1);
    EXPECT_EQ(fen.sum(0), 0);
    EXPECT_EQ(fen.sum(1), 0);
    EXPECT_EQ(fen.sum(2), 0);
    EXPECT_EQ(fen.sum(3), 0);
    EXPECT_EQ(fen.sum(4), 1);
    EXPECT_EQ(fen.sum(5), 1);
    EXPECT_EQ(fen.sum(6), 1);
    EXPECT_EQ(fen.sum(4, 7), 0);
}

TEST(FenwickTree, Search) {
    std::vector<int> a = {5, 4, 3, 2, 1};
    FenwickTree<int> fen(a);

    EXPECT_EQ(fen.lower_bound(4), 0);
    EXPECT_EQ(fen.lower_bound(5), 1);
    EXPECT_EQ(fen.lower_bound(9), 2);
    EXPECT_EQ(fen.lower_bound(11), 2);
    EXPECT_EQ(fen.lower_bound(12), 3);
    EXPECT_EQ(fen.lower_bound(12), 3);
    EXPECT_EQ(fen.lower_bound(15), 5);
    EXPECT_EQ(fen.lower_bound(16), 5);
}
