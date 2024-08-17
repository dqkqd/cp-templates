#include <gtest/gtest.h>

#include <rmq.hpp>

TEST(RMQ, Min) {
    std::vector<int> vec = {5, 2, 4, 3, 1};
    RMQ<int> rmq(vec, [](int a, int b) { return std::min(a, b); });

    EXPECT_EQ(rmq.query(0, 1), 5);
    EXPECT_EQ(rmq.query(0, 2), 2);
    EXPECT_EQ(rmq.query(0, 3), 2);
    EXPECT_EQ(rmq.query(0, 4), 2);
    EXPECT_EQ(rmq.query(0, 5), 1);

    EXPECT_EQ(rmq.query(1, 2), 2);
    EXPECT_EQ(rmq.query(1, 3), 2);
    EXPECT_EQ(rmq.query(1, 4), 2);
    EXPECT_EQ(rmq.query(1, 5), 1);

    EXPECT_EQ(rmq.query(2, 3), 4);
    EXPECT_EQ(rmq.query(2, 4), 3);
    EXPECT_EQ(rmq.query(2, 5), 1);
}
