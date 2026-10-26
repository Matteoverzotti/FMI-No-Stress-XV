#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <vector>

template<typename T, T mod>
struct Matrix{
    std::vector<std::vector<T>> m_;
    Matrix(size_t n, size_t m){
        m_.resize(n);
        for(auto& row : m_)
            row.resize(m);
    }

    size_t rows() const{
        return m_.size();
    }

    size_t columns() const{
        return m_[0].size();
    }

    T& operator()(size_t i, size_t j){
        return m_[i][j];
    }

    const T& operator()(size_t i, size_t j) const{
        return m_[i][j];
    }

    friend Matrix operator*(const Matrix& a, const Matrix& b){
        if(a.columns() != b.rows()) [[unlikely]]
            throw std::runtime_error{"multiplication couldn't happen"};
        Matrix result(a.rows(), b.columns());
        for(size_t i{}; i < a.rows(); ++i)
            for(size_t k{}; k < a.columns(); ++k)
                for(size_t j{}; j < b.columns(); ++j)
                    result(i, j) += 1ll * a(i, k) * b(k, j) % mod, result(i, j) %= mod;
        return result;
    }

    Matrix fastpow(size_t k){
        if(columns() != rows()) [[unlikely]]
            throw std::runtime_error{"the matrix should be square in order to perform exponentiation"};
        Matrix result{rows(), columns()};
        for(size_t i{}; i < rows(); ++i)
            result(i, i) = 1;

        auto self = *this;
        while(k){
            if(k & 1)
                result = result * self;
            self = self * self;
            k >>= 1;
        }

        return result;
    }
};

using Mat = Matrix<long long, 1'000'000'007>;

int main(){
    size_t n, m; std::cin >> n >> m;
    std::vector<std::tuple<long long, long long, size_t, size_t>> events;
    long long end{2};
    for(size_t i{}; i < m; ++i){
        size_t u, v; long long st, dr;
        std::cin >> u >> v >> st >> dr, --u, --v;
        events.emplace_back(st, 1, u, v);
        events.emplace_back(dr + 1, -1, u, v);
        end = std::max(end, dr + 2);
    }
    std::sort(events.begin(), events.end());

    Mat step(n + 1, n + 1), ways(1, n + 1);
    step(n - 1, n) = step(n, n) = 1;
    ways(0, 0) = 1;

    long long now{};
    for(auto&& [time, delta, u, v] : events){
        if(time > now)
            ways = ways * step.fastpow(time - now), now = time;
        step(u, v) += delta;
        if(u != v)
            step(v, u) += delta;
    }
    ways = ways * step.fastpow(end - now);

    std::cout << ways(0, n) << '\n';
}
