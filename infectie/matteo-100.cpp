#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    assert(1 <= n && n <= 1'000'000'000);
    assert(1 <= m && m <= 1'000'000'000);

    cout << (m + n + 1) / 2 << '\n';
    return 0;
}
