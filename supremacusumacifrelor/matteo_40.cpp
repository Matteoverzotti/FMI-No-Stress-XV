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

vector<ModInt> multiply(vector<ModInt> &a, vector<ModInt> &b) {
    int n = a.size();
    vector<ModInt> c(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[(i + j) % n] += a[i] * b[j];

    return c;
}

vector<ModInt> lgput(vector<ModInt> &base, int exp) {
    vector<ModInt> ans(base.size());
    ans[0] = 1;

    while (exp) {
        if (exp & 1) ans = multiply(ans, base);
        base = multiply(base, base);
        exp >>= 1;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, b, k;
    cin >> n >> b >> k;
    vector<ModInt> base(b - 1);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        base[x % (b - 1)].x++;
    }
    auto ans = lgput(base, k);

    int q;
    cin >> q;

    while (q--) {
        int x;
        cin >> x;
        cout << ans[(b - 1 - x % (b - 1)) % (b - 1)].x << '\n';
    }

    return 0;
}
