#include <gtest/gtest.h>

#include "dsu.hpp"

TEST(DSU, Init) {
    auto dsu = DSU(3);
    EXPECT_EQ(dsu.get(0), 0);
    EXPECT_EQ(dsu.get(1), 1);
    EXPECT_EQ(dsu.get(2), 2);
    EXPECT_EQ(dsu.size(0), 1);
    EXPECT_EQ(dsu.size(1), 1);
    EXPECT_EQ(dsu.size(2), 1);
}

TEST(DSU, Merge) {
    auto dsu = DSU(10);

    dsu.merge(2, 5);
    dsu.merge(4, 8);

    EXPECT_EQ(dsu.get(2), 2);
    EXPECT_EQ(dsu.get(5), 2);
    EXPECT_EQ(dsu.size(5), 2);

    EXPECT_EQ(dsu.get(4), 4);
    EXPECT_EQ(dsu.get(8), 4);
    EXPECT_EQ(dsu.size(8), 2);

    dsu.merge(2, 4);

    EXPECT_EQ(dsu.get(2), 2);
    EXPECT_EQ(dsu.get(4), 2);
    EXPECT_EQ(dsu.get(5), 2);
    EXPECT_EQ(dsu.get(8), 2);
    EXPECT_EQ(dsu.size(8), 4);
}
