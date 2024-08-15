#include <gtest/gtest.h>

#include <segment_tree.hpp>

struct StSum {
    int v = 0;
    friend StSum operator+(const StSum& lhs, const StSum& rhs) {
        return StSum{lhs.v + rhs.v};
    }
    friend bool operator==(const StSum& lhs, const StSum& rhs) {
        return lhs.v == rhs.v;
    }
};

TEST(SegmentTree, Sum) {
    std::vector<StSum> a = {StSum{2}, StSum{4}, StSum{6}};
    SegmentTree<StSum> st(a);

    EXPECT_EQ(st.tree[1], StSum(12));

    EXPECT_EQ(st.get(0, 0), StSum(0));
    EXPECT_EQ(st.get(0, 1), StSum(2));
    EXPECT_EQ(st.get(0, 2), StSum(6));
    EXPECT_EQ(st.get(0, 3), StSum(12));

    EXPECT_EQ(st.get(1, 1), StSum(0));
    EXPECT_EQ(st.get(1, 2), StSum(4));
    EXPECT_EQ(st.get(1, 3), StSum(10));

    EXPECT_EQ(st.get(2, 2), StSum(0));
    EXPECT_EQ(st.get(2, 3), StSum(6));

    // {2, 4, 6} -> {2, 5, 6}
    st.set(1, StSum{5});

    EXPECT_EQ(st.tree[1], StSum(13));
    EXPECT_EQ(st.get(0, 0), StSum(0));
    EXPECT_EQ(st.get(0, 1), StSum(2));
    EXPECT_EQ(st.get(0, 2), StSum(7));
    EXPECT_EQ(st.get(0, 3), StSum(13));

    EXPECT_EQ(st.get(1, 1), StSum(0));
    EXPECT_EQ(st.get(1, 2), StSum(5));
    EXPECT_EQ(st.get(1, 3), StSum(11));

    EXPECT_EQ(st.get(2, 2), StSum(0));
    EXPECT_EQ(st.get(2, 3), StSum(6));
}

struct StBStMin {
    int v = 10;
    friend StBStMin operator+(const StBStMin& lhs, const StBStMin& rhs) {
        return StBStMin{std::min(lhs.v, rhs.v)};
    }
    friend bool operator==(const StBStMin& lhs, const StBStMin& rhs) {
        return lhs.v == rhs.v;
    }
};

TEST(SegmentTree, Min) {
    std::vector<StBStMin> a = {StBStMin{4}, StBStMin{2}, StBStMin{6}};
    SegmentTree<StBStMin> st(a);

    int init = 10;

    EXPECT_EQ(st.tree[1].v, 2);

    EXPECT_EQ(st.get(0, 0), StBStMin(init));
    EXPECT_EQ(st.get(0, 1), StBStMin(4));
    EXPECT_EQ(st.get(0, 2), StBStMin(2));
    EXPECT_EQ(st.get(0, 3), StBStMin(2));

    EXPECT_EQ(st.get(1, 1), StBStMin(init));
    EXPECT_EQ(st.get(1, 2), StBStMin(2));
    EXPECT_EQ(st.get(1, 3), StBStMin(2));

    EXPECT_EQ(st.get(2, 2), StBStMin(init));
    EXPECT_EQ(st.get(2, 3), StBStMin(6));

    // {4, 2, 6} -> {4, 5, 6}
    st.set(1, StBStMin{5});

    EXPECT_EQ(st.tree[1], StBStMin(4));

    EXPECT_EQ(st.get(0, 0), StBStMin(init));
    EXPECT_EQ(st.get(0, 1), StBStMin(4));
    EXPECT_EQ(st.get(0, 2), StBStMin(4));
    EXPECT_EQ(st.get(0, 3), StBStMin(4));

    EXPECT_EQ(st.get(1, 1), StBStMin(init));
    EXPECT_EQ(st.get(1, 2), StBStMin(5));
    EXPECT_EQ(st.get(1, 3), StBStMin(5));

    EXPECT_EQ(st.get(2, 2), StBStMin(init));
    EXPECT_EQ(st.get(2, 3), StBStMin(6));
}

struct StMaxAndCount {
    int max = -1;
    int count = -1;
    friend StMaxAndCount operator+(const StMaxAndCount& lhs,
                                   const StMaxAndCount& rhs) {
        if (lhs.max > rhs.max) {
            return lhs;
        }
        if (rhs.max > lhs.max) {
            return rhs;
        }
        return StMaxAndCount{lhs.max, lhs.count + rhs.count};
    }
    friend bool operator==(const StMaxAndCount& lhs, const StMaxAndCount& rhs) {
        return lhs.max == rhs.max && lhs.count == rhs.count;
    }
};

TEST(SegmentTree, FindingMaximumAndTheNumberOfTimeItAppears) {
    std::vector<StMaxAndCount> a = {StMaxAndCount{5, 1}, StMaxAndCount{2, 1},
                                    StMaxAndCount{3, 1}, StMaxAndCount{5, 1},
                                    StMaxAndCount{2, 1}, StMaxAndCount{2, 1}};

    StMaxAndCount init = {-1, -1};
    SegmentTree<StMaxAndCount> st(a);

    EXPECT_EQ(st.tree[1], StMaxAndCount(5, 2));

    EXPECT_EQ(st.get(0, 0), init);
    EXPECT_EQ(st.get(0, 1), StMaxAndCount(5, 1));
    EXPECT_EQ(st.get(0, 2), StMaxAndCount(5, 1));
    EXPECT_EQ(st.get(0, 3), StMaxAndCount(5, 1));
    EXPECT_EQ(st.get(0, 4), StMaxAndCount(5, 2));
    EXPECT_EQ(st.get(0, 5), StMaxAndCount(5, 2));
    EXPECT_EQ(st.get(0, 6), StMaxAndCount(5, 2));
    EXPECT_EQ(st.get(1, 2), StMaxAndCount(2, 1));
    EXPECT_EQ(st.get(1, 3), StMaxAndCount(3, 1));
    EXPECT_EQ(st.get(1, 4), StMaxAndCount(5, 1));

    // a = {2, 2, 3, 5, 2, 2};
    st.set(0, StMaxAndCount(2, 1));

    EXPECT_EQ(st.get(0, 0), init);
    EXPECT_EQ(st.get(0, 1), StMaxAndCount(2, 1));
    EXPECT_EQ(st.get(0, 2), StMaxAndCount(2, 2));
    EXPECT_EQ(st.get(0, 3), StMaxAndCount(3, 1));
    EXPECT_EQ(st.get(0, 4), StMaxAndCount(5, 1));
    EXPECT_EQ(st.get(0, 5), StMaxAndCount(5, 1));
    EXPECT_EQ(st.get(0, 6), StMaxAndCount(5, 1));
}

TEST(SegmentTree, FindFirst) {
    std::vector<StSum> a = {StSum{1}, StSum{2}, StSum{4}, StSum{3}, StSum{5}};
    SegmentTree<StSum> st(a);
    EXPECT_EQ(st.find_first(0, 1, [](auto x) { return x.v >= 3; }), -1);
    EXPECT_EQ(st.find_first(0, 2, [](auto x) { return x.v >= 3; }), -1);
    EXPECT_EQ(st.find_first(0, 3, [](auto x) { return x.v >= 3; }), 2);
    EXPECT_EQ(st.find_first(0, 3, [](auto x) { return x.v >= 2; }), 1);
    EXPECT_EQ(st.find_first(0, 5, [](auto x) { return x.v >= 5; }), 4);
}

TEST(SegmentTree, FindLast) {
    std::vector<StSum> a = {StSum{1}, StSum{2}, StSum{4}, StSum{3}, StSum{5}};
    SegmentTree<StSum> st(a);
    EXPECT_EQ(st.find_last(0, 1, [](auto x) { return x.v >= 3; }), -1);
    EXPECT_EQ(st.find_last(0, 2, [](auto x) { return x.v >= 1; }), 1);
    EXPECT_EQ(st.find_last(0, 3, [](auto x) { return x.v >= 1; }), 2);
    EXPECT_EQ(st.find_last(0, 3, [](auto x) { return x.v >= 3; }), 2);
    EXPECT_EQ(st.find_last(0, 4, [](auto x) { return x.v >= 3; }), 3);
}
