#include <iostream>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n,k;
    std::cin >> n >> k;

    assert(1<=n && n<=100'000);
    assert(1<=k && k<=26);

    if(k==1) {
        for(int i=0; i<n; i++) {
            std::cout << 'a';
        }
        std::cout << "\n";
    }
    else if(k==2) {
        // holy pattern aabbab
        for(int i=0; i<n; i++) {
            if(i%6==0 || i%6==1 || i%6==4) {
                std::cout << 'a';
            }
            else {
                std::cout << 'b';
            }
        }
        std::cout << "\n";
    }
    else {      
        // e de ajuns doar sa ciclez 
        for(int i=0; i<n; i++) {
            std::cout << (char)('a'+(i%k));
        }
        std::cout << "\n";
    }

    return 0;
}