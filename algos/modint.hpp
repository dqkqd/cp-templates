#include <cstdint>
#include <ostream>
#include <vector>

template <std::integral auto MOD>
struct ModInt {
    unsigned int v;

    ModInt() : v{0} {}

    ModInt(int n) {
        n %= MOD;
        if (n < 0) n += MOD;
        v = n;
    }

    static unsigned int norm(unsigned int n) { return n >= MOD ? n - MOD : n; }

    ModInt operator+() const { return *this; }

    ModInt operator-() const { return ModInt(MOD - v); }

    ModInt& operator+=(const ModInt& rhs) {
        v = norm(v + rhs.v);
        return *this;
    }

    ModInt& operator-=(const ModInt& rhs) {
        v = norm(v + MOD - rhs.v);
        return *this;
    }

    ModInt& operator*=(const ModInt& rhs) {
        auto x = static_cast<uint64_t>(v);
        x = (x * rhs.v) % MOD;
        v = static_cast<unsigned int>(x);
        return *this;
    }

    ModInt pow(unsigned int p) const {
        ModInt res = 1;
        auto x = *this;
        while (p) {
            if (p & 1) res *= x;
            x *= x;
            p >>= 1;
        }
        return res;
    }

    ModInt inv() const { return pow(MOD - 2); }

    ModInt& operator/=(const ModInt& rhs) {
        *this *= rhs.inv();
        return *this;
    };

    friend ModInt operator+(ModInt lhs, const ModInt& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend ModInt operator-(ModInt lhs, const ModInt& rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend ModInt operator*(ModInt lhs, const ModInt& rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend ModInt operator/(ModInt lhs, const ModInt& rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend bool operator==(const ModInt& lhs, const ModInt& rhs) {
        return lhs.v == rhs.v;
    }

    friend bool operator!=(const ModInt& lhs, const ModInt& rhs) {
        return lhs.v != rhs.v;
    }

    friend std::ostream& operator<<(std::ostream& os, const ModInt& self) {
        return os << self.v;
    }
};

template <std::integral auto MOD>
struct Binomial {
    using mint = ModInt<MOD>;

    inline static int size = 1;
    inline static std::vector<mint> fact{1, 1};
    inline static std::vector<mint> invfact{1, 1};

    void allocate_by_size(int m) {
        if (m <= size) return;
        fact.resize(m);
        invfact.resize(m);
        for (int i = size; i < m; ++i) {
            fact[i] = fact[i - 1] * i;
        }
        invfact[m - 1] = 1 / fact[m - 1];
        for (int i = m - 1; i >= size; --i) {
            invfact[i - 1] = invfact[i] * i;
        }
        size = m;
    };

    void allocate(int n) {
        if (n >= size)
            allocate_by_size(std::bit_ceil(static_cast<unsigned int>(n + 1)));
    }

    mint binomial_coefficient(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        allocate(n);
        return fact[n] * invfact[k] * invfact[n - k];
    };
};
