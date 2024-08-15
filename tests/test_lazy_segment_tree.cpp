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

TEST(LazySegmentTree, Assign) {
    std::vector<int> a = {2, 4, 6};
    std::vector<std::optional<int>> b(a.begin(), a.end());
    LazySegmentTree<std::optional<int>> st(b, {}, [](auto x, auto y) {
        if (y.has_value())
            return y;
        else
            return x;
    });

    st.set(0, 2, 3);
    EXPECT_EQ(st.get(0), std::optional<int>(3));
    EXPECT_EQ(st.get(1), std::optional<int>(3));
    EXPECT_EQ(st.get(2), std::optional<int>(6));

    st.set(1, 3, 7);
    EXPECT_EQ(st.get(0), std::optional<int>(3));
    EXPECT_EQ(st.get(1), std::optional<int>(7));
    EXPECT_EQ(st.get(2), std::optional<int>(7));
}
