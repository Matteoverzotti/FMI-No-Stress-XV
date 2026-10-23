// BFS over permutations, where one move is any non-empty set of disjoint swaps.
//   brute            reads one instance (n <= 8) and prints an optimal answer
//   brute --check N  checks the 0/1/2 rule against BFS on every permutation with n <= N
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using Perm = std::vector<int>;
using Matching = std::vector<std::pair<int, int>>;

// Every non-empty set of disjoint pairs over positions 0..n-1.
std::vector<Matching> matchings(int n) {
    std::vector<Matching> all;
    Matching current;
    std::vector<bool> used(n, false);
    auto extend = [&](auto& self, int from) -> void {
        if (!current.empty()) all.push_back(current);
        for (int i = from; i < n; ++i) {
            if (used[i]) continue;
            for (int j = i + 1; j < n; ++j) {
                if (used[j]) continue;
                used[i] = used[j] = true;
                current.emplace_back(i, j);
                self(self, i + 1);
                current.pop_back();
                used[i] = used[j] = false;
            }
        }
    };
    extend(extend, 0);
    return all;
}

Perm apply(Perm p, const Matching& m) {
    for (auto [i, j] : m) std::swap(p[i], p[j]);
    return p;
}

// Distance from every permutation to the identity, with the move that leads one step closer.
std::map<Perm, std::pair<int, int>> bfs(int n, const std::vector<Matching>& moves) {
    Perm identity(n);
    std::iota(identity.begin(), identity.end(), 0);
    std::map<Perm, std::pair<int, int>> dist{{identity, {0, -1}}};
    std::queue<Perm> queue;
    queue.push(identity);
    while (!queue.empty()) {
        Perm p = queue.front();
        queue.pop();
        int d = dist[p].first;
        for (int k = 0; k < static_cast<int>(moves.size()); ++k) {
            // Each move is its own inverse, so the same move leads back toward the identity.
            Perm q = apply(p, moves[k]);
            if (dist.emplace(q, std::pair{d + 1, k}).second) queue.push(q);
        }
    }
    return dist;
}

int rule(const Perm& p) {
    int longest = 1;
    std::vector<bool> visited(p.size(), false);
    for (int i = 0; i < static_cast<int>(p.size()); ++i) {
        int length = 0;
        for (int j = i; !visited[j]; j = p[j]) {
            visited[j] = true;
            ++length;
        }
        longest = std::max(longest, length);
    }
    return longest == 1 ? 0 : longest == 2 ? 1 : 2;
}

int main(int argc, char** argv) {
    if (argc >= 3 && std::string(argv[1]) == "--check") {
        int limit = std::stoi(argv[2]);
        bool allMatch = true;
        for (int n = 1; n <= limit; ++n) {
            auto dist = bfs(n, matchings(n));
            int worst = 0, mismatches = 0;
            for (const auto& [p, entry] : dist) {
                worst = std::max(worst, entry.first);
                if (entry.first != rule(p)) ++mismatches;
            }
            std::cout << "n=" << n << ": " << dist.size() << " permutations, max " << worst << " seconds, "
                      << mismatches << " disagree with the rule\n";
            allMatch &= mismatches == 0;
        }
        return allMatch ? 0 : 1;
    }

    int n;
    std::cin >> n;
    Perm p(n);
    for (int& x : p) {
        std::cin >> x;
        --x;
    }
    auto moves = matchings(n);
    auto dist = bfs(n, moves);
    std::vector<Matching> plan;
    while (dist[p].first > 0) {
        const Matching& m = moves[dist[p].second];
        plan.push_back(m);
        p = apply(p, m);
    }
    std::cout << plan.size() << '\n';
    for (const auto& m : plan) {
        std::cout << m.size() << '\n';
        for (auto [i, j] : m) std::cout << i + 1 << ' ' << j + 1 << '\n';
    }
}
