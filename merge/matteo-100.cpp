#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, total_n = 0;
    cin >> t;
    assert(1 <= t && t <= 100000);
    while (t--) {
        int n, a, b, max_a, max_b;
        cin >> n; total_n += n;
        assert(1 <= n && n <= 1000000);

        max_a = max_b = -1;
        for (int i = 0; i < n; i++) {
            cin >> a;
            assert(1 <= a && a <= 1000000000);
            max_a = max(max_a, a);
        }
        for (int i = 0; i < n; i++) {
            cin >> b;
            assert(1 <= b && b <= 1000000000);
            max_b = max(max_b, b);
        }

        if (max_a <= max_b)
            cout << "a\n";
        else cout << "b\n";
    }

    assert(1 <= total_n && total_n <= 1000000);
    assert(!(cin >> t));
    return 0;
}
