#include <iostream>
#include <vector>

int main(){
    size_t n; std::cin >> n;
    std::vector<size_t> p(n);

    for(size_t& x : p)
        std::cin >> x, --x;
    
    std::vector<std::pair<size_t, size_t>> ops[2];
    std::vector<bool> visited(n, false);
    for(size_t i{}; i < n; ++i){
        if(visited[i])
            continue;

        std::vector<size_t> cycle{i}; visited[i] = true;
        for(auto j{p[i]}; j != i; j = p[j])
            cycle.emplace_back(j), visited[j] = true;
        
        auto sz = cycle.size();
        for(size_t j{sz - 1}; j * 2 >= sz; --j)
            ops[0].emplace_back(cycle[j], cycle[sz - 1 - j]);

        for(size_t j{1}; j * 2 < sz; ++j)
            ops[1].emplace_back(cycle[j], cycle[sz - j]);
    }

    size_t rounds = !ops[0].empty() + !ops[1].empty();
    std::cout << rounds << "\n";

    for(size_t round{}; round < rounds; ++round){
        std::cout << ops[round].size() << "\n";
        for(auto&& [a, b] : ops[round])
            std::cout << a + 1 << ' ' << b  + 1 << '\n';
    }
}
