// O(max(dr) * m) DP over time, enough for the dr <= 100 subtask.
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

constexpr long long MOD = 1'000'000'007;

int main(){
    size_t n, m; std::cin >> n >> m;
    std::vector<std::tuple<size_t, size_t, long long, long long>> edges(m);
    long long end{};
    for(auto& [u, v, st, dr] : edges)
        std::cin >> u >> v >> st >> dr, --u, --v, end = std::max(end, dr + 1);

    std::vector<long long> ways(n, 0);
    ways[0] = 1;
    long long answer{};
    for(long long t{}; t <= end; ++t){
        answer = (answer + ways[n - 1]) % MOD;
        std::vector<long long> next(n, 0);
        for(auto&& [u, v, st, dr] : edges){
            if(t < st || dr < t)
                continue;
            next[v] = (next[v] + ways[u]) % MOD;
            if(u != v)
                next[u] = (next[u] + ways[v]) % MOD;
        }
        ways = next;
    }

    std::cout << answer << '\n';
}
