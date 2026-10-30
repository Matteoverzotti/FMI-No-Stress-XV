#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

const int MOD = 998244353;
struct ModInt {
    int x;
    ModInt(int x = 0) : x (x + (x < 0) * MOD - (x >= MOD) * MOD) {}
    ModInt operator + (ModInt o) { return x + o.x; }
    ModInt& operator += (ModInt o) { *this = *this + o; return *this; }
    ModInt operator - (ModInt o) { return x - o.x; }
    ModInt operator * (ModInt o) { return 1LL * x * o.x % MOD; }
    ModInt operator / (ModInt o) { return *this * o.inv(); }
    ModInt inv() { return pow(MOD - 2); }
    ModInt pow(int exp) {
        if (!exp) return 1;
        ModInt r = pow(exp / 2);
        r = r * r;
        return exp % 2 ? *this * r : r;
    }

    bool operator == (ModInt o) { return x == o.x; }
};

using namespace std;

int main() {
    int n, T, P;
    cin >> n >> T >> P;
    assert(2 <= n && n <= 100);
    assert(1 <= T && T <= 20'000);
    assert(1 <= P && P <= 100);
    assert(!(cin >> n));

    ModInt q = ModInt(P) / (ModInt(100 * (n - 1)));

    vector<vector<ModInt>> dp[2];
    dp[0].resize(n, vector<ModInt>(n));
    dp[1].resize(n, vector<ModInt>(n));

    dp[0][0][0] = 1;
    for (int t = 0; t < T; t++) {
        auto &current = dp[t & 1];
        auto &next = dp[(t + 1) & 1];
        for (auto &row : next)
            ranges::fill(row, ModInt(0));

        for (int a = 0; a < n - 1; a++) {
            for (int b = 0; b < n - 1; b++) {
                if (a + b == n - 2) {
                    next[a + 1][b + 1] += q * current[a][b];
                    next[a][b] += (ModInt(1) - q) * current[a][b];
                } else {
                    next[a + 1][b] += q * current[a][b];
                    next[a][b + 1] += q * current[a][b];
                    next[a][b] += (ModInt(1) - q * 2) * current[a][b];
                }
            }
            // b == n - 1
            next[a + 1][n - 1] += q * current[a][n - 1];
            next[a][n - 1] += (ModInt(1) - q) * current[a][n - 1];
        }

        // a == n - 1
        for (int b = 0; b < n - 1; b++) {
            next[n - 1][b + 1] += q * current[n - 1][b];
            next[n - 1][b] += (ModInt(1) - q) * current[n - 1][b];
        }

        // a == n - 1 && b == n - 1
        next[n - 1][n - 1] += current[n - 1][n - 1];
    }

    cout << dp[T & 1][n - 1][n - 1].x << '\n';
    return 0;
}
