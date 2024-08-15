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
