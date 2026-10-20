#include <iostream>
#include <utility>
#include <vector>
#include <bitset>

using namespace std;

const int N = 2e5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    vector<pair<int, int>> v;
    cin >> n >> m;
    v.resize(m);
    for (int i = 0; i < m; i++) cin >> v[i].first;
    for (int i = 0; i < m; i++) cin >> v[i].second;

    bitset<N> ascending, descending;
    for (const auto it : v) {
        if (it.first < it.second)
            ascending[it.first] = ascending[it.second] = true;
        else
            descending[it.first] = descending[it.second] = true;
    }

    cout << ascending.count() + descending.count() 
        - (ascending[n - 1] && descending[n - 1]) << '\n'; // Don't include the last floor twice
    return 0;
}
