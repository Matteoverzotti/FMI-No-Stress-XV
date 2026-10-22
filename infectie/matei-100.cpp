#include <iostream>
#include <cassert>

int n,m;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m;
    assert(1<=n && n<=1e9); 
    assert(1<=m && m<=1e9);

    std::cout << (n+m)/2+((n+m)&1) << "\n";

    return 0;
}