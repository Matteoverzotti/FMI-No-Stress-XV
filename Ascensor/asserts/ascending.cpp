#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    assert(2 <= n && n <= 200000);
    assert(1 <= m && m <= 200000);
    
    vector<int> s(m), t(m);
    for (int i = 0; i < m; i++) {
        cin >> s[i];
        assert(0 <= s[i] && s[i] < n);
    }
    for (int i = 0; i < m; i++) {
        cin >> t[i];
        assert(0 <= t[i] && t[i] < n);
        assert(s[i] != t[i]);
        assert(s[i] < t[i]);
    }

    assert(!(cin >> n));
    return 0;
}
