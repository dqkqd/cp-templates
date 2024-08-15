#include <gtest/gtest.h>

#include <lazy_segment_tree.hpp>

struct TestLazySegmentTreeStruct {
    int x;
    int y;
};

bool operator==(const TestLazySegmentTreeStruct& lhs,
                const TestLazySegmentTreeStruct& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

TEST(LazySegmentTree, Sum) {
    std::vector<int> a = {2, 4, 6};
    LazySegmentTree<int> st(a, 0);

    st.set(0, 3, 5);
    EXPECT_EQ(st.get(0), 7);
    EXPECT_EQ(st.get(1), 9);
    EXPECT_EQ(st.get(2), 11);

    st.set(1, 3, 1);
    EXPECT_EQ(st.get(0), 7);
    EXPECT_EQ(st.get(1), 10);
    EXPECT_EQ(st.get(2), 12);
}

TEST(LazySegmentTree, Max) {
    std::vector<int> a = {2, 4, 6};
    LazySegmentTree<int> st(a, 0, [](int x, int y) { return std::max(x, y); });

    st.set(0, 3, 3);
    EXPECT_EQ(st.get(0), 3);
    EXPECT_EQ(st.get(1), 4);
    EXPECT_EQ(st.get(2), 6);

    st.set(1, 3, 7);
    EXPECT_EQ(st.get(0), 3);
    EXPECT_EQ(st.get(1), 7);
    EXPECT_EQ(st.get(2), 7);
}
