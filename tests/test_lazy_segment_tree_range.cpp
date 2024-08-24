#include <gtest/gtest.h>

#include <lazy_segment_tree_range.hpp>

struct OpRA {
    int value = 0;

    void apply(const OpRA& op) { value += op.value; }
};

struct NodeRA {
    int value = 0;

    void apply(const OpRA& op, int l, int r) { value += op.value * (r - l); }

    friend NodeRA operator+(const NodeRA& lhs, const NodeRA& rhs) {
        return NodeRA{lhs.value + rhs.value};
    }
};

TEST(LazySegmentTreeRange, AddAndSum) {
    std::vector<NodeRA> a = {NodeRA{2}, NodeRA{4}, NodeRA{6}};
    LazySegmentTree<NodeRA, OpRA> st(a);

    st.set(0, 3, OpRA{5});
    EXPECT_EQ(st.get(0, 1).value, 7);
    EXPECT_EQ(st.get(0, 2).value, 16);
    EXPECT_EQ(st.get(0, 3).value, 27);

    st.set(1, 3, OpRA{1});
    EXPECT_EQ(st.get(0, 1).value, 7);
    EXPECT_EQ(st.get(1, 2).value, 10);
    EXPECT_EQ(st.get(1, 3).value, 22);
}

struct OpRB {
    std::optional<int> value = {};

    void apply(const OpRB& op) {
        if (op.value.has_value()) {
            value = op.value;
        }
    }
};

struct NodeRB {
    int value = 0;

    void apply(const OpRB& op, int l, int r) {
        if (op.value.has_value()) {
            value = op.value.value() * (r - l);
        }
    }

    friend NodeRB operator+(const NodeRB& lhs, const NodeRB& rhs) {
        return NodeRB{lhs.value + rhs.value};
    }
};

TEST(LazySegmentTreeRange, AssignAndSum) {
    std::vector<NodeRB> a = {NodeRB{2}, NodeRB{4}, NodeRB{6}};
    LazySegmentTree<NodeRB, OpRB> st(a);

    st.set(0, 2, OpRB{3});

    EXPECT_EQ(st.get(0, 1).value, 3);
    EXPECT_EQ(st.get(0, 2).value, 6);
    EXPECT_EQ(st.get(0, 3).value, 12);

    st.set(1, 3, OpRB{1});
    EXPECT_EQ(st.get(0, 1).value, 3);
    EXPECT_EQ(st.get(1, 2).value, 1);
    EXPECT_EQ(st.get(1, 3).value, 2);
}
