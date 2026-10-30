
#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>
#include <cmath>

using namespace std;

const int N = 500'000;

optional<int> perfectSquare(int x) {
    int r = sqrt(x);
    if (r * r == x)
        return r;
    return nullopt;
}

void updateFrequency(int val, int upd, vector<int> &freq, vector<int> &squarefq, int &counts) {
    int previousFreq = freq[val];
    freq[val] += upd;
    int currFreq = freq[val];

    auto pvsq = perfectSquare(previousFreq);
    if (pvsq.has_value()) {
        squarefq[pvsq.value()]--;
        if (squarefq[pvsq.value()] == 1)
            counts++;
        else if (squarefq[pvsq.value()] == 0)
            counts--;
    }

    auto currsq = perfectSquare(currFreq);
    if (currsq.has_value()) {
        squarefq[currsq.value()]++;
        if (squarefq[currsq.value()] == 1)
            counts++;
        else if (squarefq[currsq.value()] == 2)
            counts--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    vector<int> squares = {1};
    int sq = 2;
    while (squares.back() <= n) {
        squares.push_back(squares.back() + sq * sq);
        sq++;
    }
    squares.pop_back();

    vector<int> v(n);
    for (auto &x : v)
        cin >> x;

    sq = 1;
    int ans = 0;
    vector<int> freq(N + 1), squarefq(N + 1);
    for (auto seq_len : squares) {
        int counts = 0;
        ranges::fill(freq, 0);
        ranges::fill(squarefq, 0);
        for (int i = 0; i < seq_len - 1; i++) {
            updateFrequency(v[i], 1, freq, squarefq, counts);
        }

        for (int i = seq_len - 1; i < n; i++) {
            updateFrequency(v[i], 1, freq, squarefq, counts);
            if (counts == sq)
                ans++;
            updateFrequency(v[i - seq_len + 1], -1, freq, squarefq, counts);
        }

        sq++;
    }

    cout << ans << '\n';
    return 0;
}
