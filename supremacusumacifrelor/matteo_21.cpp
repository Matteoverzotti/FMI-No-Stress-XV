#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, b, k;
    cin >> n >> b >> k;
    vector<int> c(b);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        c[x % (b - 1)]++;
    }

    int q;
    cin >> q;

    vector<ModInt> dp[2];
    dp[0].resize(b); dp[1].resize(b);
    dp[0][0] = 1;
    for (int t = 0; t < k; t++) {
        auto &curr = dp[t & 1];
        auto &nxt = dp[(t + 1) & 1];
        ranges::fill(nxt, 0);

        for (int r = 0; r < b - 1; r++)
            for (int x = 0; x < b - 1; x++)
                nxt[(x + r) % (b - 1)] += curr[r] * c[x];
    }

    auto &ans = dp[k & 1];

    while (q--) {
        int x;
        cin >> x;
        cout << ans[(b - 1 - x % (b - 1)) % (b - 1)].x << '\n';
    }

    return 0;
}
