#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    assert(n == 1);
    assert(1 <= m && m <= 100'000);

    cout << (m + n + 1) / 2 << '\n';
    return 0;
}
