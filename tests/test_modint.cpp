#include <gtest/gtest.h>

#include <modint.hpp>

TEST(ModInt, Init) {
    EXPECT_EQ(ModInt<3>(1), 1);
    EXPECT_EQ(ModInt<3>(2), 2);
    EXPECT_EQ(ModInt<3>(3), 0);
    EXPECT_EQ(ModInt<3>(4), 1);

    EXPECT_EQ(ModInt<3>(-2), 1);
}

TEST(ModInt, Plus) { EXPECT_EQ(+ModInt<3>(2), 2); }

TEST(ModInt, Minus) { EXPECT_EQ((-ModInt<3>(2)), 1); }

TEST(ModInt, AddAssign) {
    auto a = ModInt<5>(2);
    a += 1;
    EXPECT_EQ(a, 3);
    a += 1;
    EXPECT_EQ(a, 4);
    a += ModInt<5>(1);
    EXPECT_EQ(a, 0);
    a += ModInt<5>(1);
    EXPECT_EQ(a, 1);
}

TEST(ModInt, SubAssign) {
    auto a = ModInt<5>(2);
    a -= 1;
    EXPECT_EQ(a, 1);
    a -= 1;
    EXPECT_EQ(a, 0);
    a -= ModInt<5>(1);
    EXPECT_EQ(a, 4);
    a -= ModInt<5>(1);
    EXPECT_EQ(a, 3);
}

TEST(ModInt, MulAssign) {
    auto a = ModInt<5>(2);
    a *= 3;
    EXPECT_EQ(a, 1);
    a *= ModInt<5>(5);
    EXPECT_EQ(a, 0);
}

TEST(ModInt, DivAssign) {
    auto a = ModInt<11>(8);
    a /= 2;
    EXPECT_EQ(a, 4);
    a /= ModInt<11>(2);
    EXPECT_EQ(a, 2);
}

TEST(ModInt, Add) {
    auto a = ModInt<5>(2);

    auto b = a + 1;
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 3);

    auto c = a + ModInt<5>(1);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(c, 3);

    auto d = 1 + a;
    EXPECT_EQ(a, 2);
    EXPECT_EQ(d, 3);
}

TEST(ModInt, Sub) {
    auto a = ModInt<5>(1);

    auto b = a - 1;
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 0);

    auto c = a - ModInt<5>(1);
    EXPECT_EQ(a, 1);
    EXPECT_EQ(c, 0);

    auto d = 1 - a;
    EXPECT_EQ(a, 1);
    EXPECT_EQ(d, 0);
}

TEST(ModInt, Mul) {
    auto a = ModInt<5>(2);

    auto b = a * 3;
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 1);

    auto c = a * ModInt<5>(3);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(c, 1);

    auto d = 3 * a;
    EXPECT_EQ(a, 2);
    EXPECT_EQ(d, 1);
}

TEST(ModInt, Div) {
    auto a = ModInt<11>(8);

    auto b = a / 2;
    EXPECT_EQ(a, 8);
    EXPECT_EQ(b, 4);

    auto c = a / ModInt<11>(2);
    EXPECT_EQ(a, 8);
    EXPECT_EQ(c, 4);

    auto d = 16 / a;
    EXPECT_EQ(a, 8);
    EXPECT_EQ(d, 2);
}

TEST(ModInt, Binomial) {
    auto b = Binomial<104729>();

    EXPECT_EQ(b.size, 1);
    EXPECT_EQ(b.binomial_coefficient(6, 4), 15);
    EXPECT_EQ(b.size, 8);

    // already init for the same mod
    auto c = Binomial<104729>();
    EXPECT_EQ(c.size, 8);

    // no init for other mod
    auto d = Binomial<1047210>();
    EXPECT_EQ(d.size, 1);
}
