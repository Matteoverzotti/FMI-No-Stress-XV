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

void DFT(vector<ModInt> &a, bool rev) {
    int n = a.size();
    auto b = a;
    ModInt g = 1;
    while (g.pow((MOD - 1) / 2) == 1)
        g = g + 1;

    if (rev)
        g = g.inv();

    for (int step = n / 2; step; step >>= 1) {
        ModInt w = g.pow((MOD - 1) / (n / step)), wn = 1;
        for (int i = 0; i < n / 2; i += step) {
            for (int j = 0; j < step; j++) {
                auto u = a[2 * i + j];
                auto v = wn * a[2 * i + j + step];
                b[i + j] = u + v;
                b[i + n / 2 + j] = u - v;
            }
            wn = wn * w;
        }
        swap(a, b);
    }

    if (rev) {
        auto n1 = ModInt(n).inv();
        for (auto &x : a)
            x = x * n1;
    }
}

vector<ModInt> polyMul(vector<ModInt> a, vector<ModInt> b) {
    if (a.empty() || b.empty()) return {};
    int B = a.size(); 
    int m = a.size() + b.size() - 1;
    int n = m;

    while (n & (n - 1))
        n++;

    a.resize(n, 0);
    b.resize(n, 0);

    DFT(a, 0); DFT(b, 0);
    for (int i = 0; i < n; i++)
        a[i] = a[i] * b[i];

    DFT(a, 1);
    a.resize(m);

    vector<ModInt> r(B);
    for (int i = 0; i < a.size(); i++)
        r[i % B] += a[i];

    a.resize(B);
    a = r;
    return a;
}

vector<ModInt> lgput(vector<ModInt> &base, int exp) {
    vector<ModInt> ans(base.size());
    ans[0] = 1;

    while (exp) {
        if (exp & 1) ans = polyMul(ans, base);
        base = polyMul(base, base);
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
