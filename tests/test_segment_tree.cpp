#include <gtest/gtest.h>

#include <segment_tree.hpp>

struct TestSegmentTreeStruct {
    int x;
    int y;
};

bool operator==(const TestSegmentTreeStruct& lhs,
                const TestSegmentTreeStruct& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

TEST(SegmentTree, Sum) {
    std::vector<int> a = {2, 4, 6};
    SegmentTree<int> st(a, 0);

    EXPECT_EQ(st.tree[1], 12);

    EXPECT_EQ(st.get(0, 0), 0);
    EXPECT_EQ(st.get(0, 1), 2);
    EXPECT_EQ(st.get(0, 2), 6);
    EXPECT_EQ(st.get(0, 3), 12);

    EXPECT_EQ(st.get(1, 1), 0);
    EXPECT_EQ(st.get(1, 2), 4);
    EXPECT_EQ(st.get(1, 3), 10);

    EXPECT_EQ(st.get(2, 2), 0);
    EXPECT_EQ(st.get(2, 3), 6);

    // {2, 4, 6} -> {2, 5, 6}
    st.set(1, 5);

    EXPECT_EQ(st.tree[1], 13);
    EXPECT_EQ(st.get(0, 0), 0);
    EXPECT_EQ(st.get(0, 1), 2);
    EXPECT_EQ(st.get(0, 2), 7);
    EXPECT_EQ(st.get(0, 3), 13);

    EXPECT_EQ(st.get(1, 1), 0);
    EXPECT_EQ(st.get(1, 2), 5);
    EXPECT_EQ(st.get(1, 3), 11);

    EXPECT_EQ(st.get(2, 2), 0);
    EXPECT_EQ(st.get(2, 3), 6);
}

TEST(SegmentTree, Min) {
    std::vector<int> a = {4, 2, 6};

    int init = 10;
    SegmentTree<int> st(a, init, [](int x, int y) { return std::min(x, y); });

    EXPECT_EQ(st.tree[1], 2);

    EXPECT_EQ(st.get(0, 0), init);
    EXPECT_EQ(st.get(0, 1), 4);
    EXPECT_EQ(st.get(0, 2), 2);
    EXPECT_EQ(st.get(0, 3), 2);

    EXPECT_EQ(st.get(1, 1), init);
    EXPECT_EQ(st.get(1, 2), 2);
    EXPECT_EQ(st.get(1, 3), 2);

    EXPECT_EQ(st.get(2, 2), init);
    EXPECT_EQ(st.get(2, 3), 6);

    // {4, 2, 6} -> {4, 5, 6}
    st.set(1, 5);

    EXPECT_EQ(st.tree[1], 4);

    EXPECT_EQ(st.get(0, 0), init);
    EXPECT_EQ(st.get(0, 1), 4);
    EXPECT_EQ(st.get(0, 2), 4);
    EXPECT_EQ(st.get(0, 3), 4);

    EXPECT_EQ(st.get(1, 1), init);
    EXPECT_EQ(st.get(1, 2), 5);
    EXPECT_EQ(st.get(1, 3), 5);

    EXPECT_EQ(st.get(2, 2), init);
    EXPECT_EQ(st.get(2, 3), 6);
}

TEST(SegmentTree, Struct) {
    std::vector<TestSegmentTreeStruct> a = {
        TestSegmentTreeStruct{.x = 1, .y = 2},
        TestSegmentTreeStruct{.x = 3, .y = 4},
        TestSegmentTreeStruct{.x = 5, .y = 6}};

    auto init = TestSegmentTreeStruct{.x = 0, .y = 0};
    SegmentTree<TestSegmentTreeStruct> st(a, init, [](auto lhs, auto rhs) {
        return TestSegmentTreeStruct{.x = lhs.x + rhs.x, .y = lhs.y + rhs.y};
    });

    EXPECT_EQ(st.tree[1], TestSegmentTreeStruct(9, 12));

    EXPECT_EQ(st.get(0, 0), init);
    EXPECT_EQ(st.get(0, 1), TestSegmentTreeStruct(1, 2));
    EXPECT_EQ(st.get(0, 2), TestSegmentTreeStruct(4, 6));
    EXPECT_EQ(st.get(0, 3), TestSegmentTreeStruct(9, 12));

    st.set(1, TestSegmentTreeStruct(0, 1));

    EXPECT_EQ(st.tree[1], TestSegmentTreeStruct(6, 9));

    EXPECT_EQ(st.get(0, 0), init);
    EXPECT_EQ(st.get(0, 1), TestSegmentTreeStruct(1, 2));
    EXPECT_EQ(st.get(0, 2), TestSegmentTreeStruct(1, 3));
    EXPECT_EQ(st.get(0, 3), TestSegmentTreeStruct(6, 9));
}

TEST(SegmentTree, FindingMaximumAndTheNumberOfTimeItAppears) {
    std::vector<int> a = {5, 2, 3, 5, 2, 2};

    using P = std::pair<int, int>;

    std::vector<P> b;
    for (size_t i = 0; i < a.size(); ++i) {
        b.emplace_back(a[i], 1);
    }

    P init = {-1, -1};
    SegmentTree<P> st(b, init, [](auto p1, auto p2) -> P {
        if (p1.first > p2.first) {
            return p1;
        }
        if (p2.first > p1.first) {
            return p2;
        }
        return {p1.first, p1.second + p2.second};
    });

    EXPECT_EQ(st.tree[1], std::make_pair(5, 2));

    EXPECT_EQ(st.get(0, 0), init);
    EXPECT_EQ(st.get(0, 1), std::make_pair(5, 1));
    EXPECT_EQ(st.get(0, 2), std::make_pair(5, 1));
    EXPECT_EQ(st.get(0, 3), std::make_pair(5, 1));
    EXPECT_EQ(st.get(0, 4), std::make_pair(5, 2));
    EXPECT_EQ(st.get(0, 5), std::make_pair(5, 2));
    EXPECT_EQ(st.get(0, 6), std::make_pair(5, 2));
    EXPECT_EQ(st.get(1, 2), std::make_pair(2, 1));
    EXPECT_EQ(st.get(1, 3), std::make_pair(3, 1));
    EXPECT_EQ(st.get(1, 4), std::make_pair(5, 1));

    // a = {2, 2, 3, 5, 2, 2};
    st.set(0, std::make_pair(2, 1));

    EXPECT_EQ(st.get(0, 0), init);
    EXPECT_EQ(st.get(0, 1), std::make_pair(2, 1));
    EXPECT_EQ(st.get(0, 2), std::make_pair(2, 2));
    EXPECT_EQ(st.get(0, 3), std::make_pair(3, 1));
    EXPECT_EQ(st.get(0, 4), std::make_pair(5, 1));
    EXPECT_EQ(st.get(0, 5), std::make_pair(5, 1));
    EXPECT_EQ(st.get(0, 6), std::make_pair(5, 1));
}

TEST(SegmentTree, FindFirst) {
    std::vector<int> a = {1, 2, 4, 3, 5};
    int init = 0;
    SegmentTree<int> st(a, init);
    EXPECT_EQ(st.find_first(0, 1, [](int x) { return x >= 3; }), -1);
    EXPECT_EQ(st.find_first(0, 2, [](int x) { return x >= 3; }), -1);
    EXPECT_EQ(st.find_first(0, 3, [](int x) { return x >= 3; }), 2);
    EXPECT_EQ(st.find_first(0, 3, [](int x) { return x >= 2; }), 1);
    EXPECT_EQ(st.find_first(0, 5, [](int x) { return x >= 5; }), 4);
}

TEST(SegmentTree, FindLast) {
    std::vector<int> a = {1, 2, 4, 3, 5};
    int init = 0;
    SegmentTree<int> st(a, init);
    EXPECT_EQ(st.find_last(0, 1, [](int x) { return x >= 3; }), -1);
    EXPECT_EQ(st.find_last(0, 2, [](int x) { return x >= 1; }), 1);
    EXPECT_EQ(st.find_last(0, 3, [](int x) { return x >= 1; }), 2);
    EXPECT_EQ(st.find_last(0, 3, [](int x) { return x >= 3; }), 2);
    EXPECT_EQ(st.find_last(0, 4, [](int x) { return x >= 3; }), 3);
}
