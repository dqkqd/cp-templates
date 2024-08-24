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

struct OpA {
    int value = 0;

    void apply(const OpA& op) { value += op.value; }
};

struct NodeA {
    int value = 0;

    void apply(const OpA& op) { value += op.value; }

    friend NodeA operator+(const NodeA& lhs, const NodeA& rhs) {
        return NodeA{std::max(lhs.value, rhs.value)};
    }
};

TEST(LazySegmentTree, SumAndMax) {
    std::vector<NodeA> a = {NodeA{2}, NodeA{4}, NodeA{6}};
    LazySegmentTree<NodeA, OpA> st(a);

    st.set(0, 3, OpA{5});
    EXPECT_EQ(st.get(0, 1).value, 7);
    EXPECT_EQ(st.get(0, 2).value, 9);
    EXPECT_EQ(st.get(0, 3).value, 11);

    st.set(1, 3, OpA{1});
    EXPECT_EQ(st.get(0, 1).value, 7);
    EXPECT_EQ(st.get(1, 2).value, 10);
    EXPECT_EQ(st.get(1, 3).value, 12);
}

struct OpB {
    std::optional<int> value = {};

    void apply(const OpB& op) {
        if (op.value.has_value()) {
            value = op.value;
        }
    }
};

struct NodeB {
    int value = 0;

    void apply(const OpB& op) {
        if (op.value.has_value()) {
            value = op.value.value();
        }
    }

    friend NodeB operator+(const NodeB& lhs, const NodeB& rhs) {
        return NodeB{std::max(lhs.value, rhs.value)};
    }
};

TEST(LazySegmentTree, AssignAndMax) {
    std::vector<NodeB> a = {NodeB{2}, NodeB{4}, NodeB{6}};
    LazySegmentTree<NodeB, OpB> st(a);

    st.set(0, 2, OpB{3});
    EXPECT_EQ(st.get(0, 1).value, 3);
    EXPECT_EQ(st.get(0, 2).value, 3);
    EXPECT_EQ(st.get(0, 3).value, 6);

    st.set(1, 3, OpB{1});
    EXPECT_EQ(st.get(0, 1).value, 3);
    EXPECT_EQ(st.get(1, 2).value, 1);
    EXPECT_EQ(st.get(1, 3).value, 1);
}

struct OpC {
    std::optional<int> value = {};

    void apply(const OpC& op) {
        if (op.value.has_value()) {
            value = op.value;
        }
    }
};

struct NodeC {
    int value = 0;

    void apply(const OpC& op) {
        if (op.value.has_value()) {
            value = op.value.value();
        }
    }

    friend NodeC operator+(const NodeC& lhs, const NodeC& rhs) {
        return NodeC{std::max(lhs.value, rhs.value)};
    }
};

TEST(LazySegmentTree, FindFirstAssignAndMax) {
    // {1 3 2 4 5}
    std::vector<NodeC> a = {NodeC{1}, NodeC{3}, NodeC{2}, NodeC{4}, NodeC{5}};
    LazySegmentTree<NodeC, OpC> st(a);

    EXPECT_EQ(st.find_first(0, 5, [](auto x) { return x.value >= 3; }), 1);
    EXPECT_EQ(st.find_first(2, 5, [](auto x) { return x.value >= 3; }), 3);

    // {1 3 2 4 5} -> {1 4 4 4 5}
    st.set(1, 3, OpC{4});
    EXPECT_EQ(st.find_first(0, 5, [](auto x) { return x.value >= 3; }), 1);

    // {1 2 2 4 5} -> {0 0 0 0 5}
    st.set(0, 4, OpC{0});
    EXPECT_EQ(st.find_first(0, 5, [](auto x) { return x.value >= 1; }), 4);
}

TEST(LazySegmentTree, FindLastAssignAndMax) {
    // {5 4 2 3 1}
    std::vector<NodeC> a = {NodeC{5}, NodeC{4}, NodeC{2}, NodeC{3}, NodeC{1}};
    LazySegmentTree<NodeC, OpC> st(a);

    EXPECT_EQ(st.find_last(0, 5, [](auto x) { return x.value >= 3; }), 3);
    EXPECT_EQ(st.find_last(0, 3, [](auto x) { return x.value >= 3; }), 1);

    // {5 4 2 3 1} -> {5 4 4 4 1}
    st.set(1, 4, OpC{4});
    EXPECT_EQ(st.find_last(0, 5, [](auto x) { return x.value >= 3; }), 3);

    // {5 4 4 4 1} -> {5 0 0 0 0}
    st.set(1, 5, OpC{0});
    EXPECT_EQ(st.find_last(0, 5, [](auto x) { return x.value >= 1; }), 0);
}
