//
// Created by Leon Ericsson on 2022-04-18.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
/*
 * Solver for the problem of congruences:
 *      x = a mod n
 *      x = b mod m
 * where n,m are relative prime.
 * Usage:
 *      chineseremainder(int a, int n, int b, int m)
 *
 *      @param a      : Modulus
 *      @param n      : Modulus
 *      @param b      : Modulus
 *      @param m      : Modulus
 *
 *      return        :
 *
 *
 */

static int64_t exteuclid(int64_t y, int64_t n){
    int64_t n_old{n};
    int64_t q, t;
    int64_t a{0}, b{1};

    if(n == 1) return 1;
    while(y > 1){
        q = y / n;
        t = n;
        n = y % n;
        y = t;
        t = a;
        a = b - q * a;
        b = t;
    }
    return (b < 0) ? b + n_old : b;
}

std::tuple<int64_t, int64_t> chineseremainder(int64_t a, int64_t n, int64_t b, int64_t m){
    auto K = n * m;
    auto M1 = K / n;
    auto M2 = K / m;
    auto y1 = exteuclid(M1, n);
    auto y2 = exteuclid(M2, m);
    auto x = (a*y1*M1 + b*y2*M2) % K;
    return {x, K};
}

int main(){
    int64_t T, a, n, b, m;
    std::cin >> T;
    while(T--){
        std::cin >> a >> n >> b >> m;
        auto [x, K] = chineseremainder(a,n,b,m);
        std::cout << x << " " << K << "\n";
    }
    return 0;
}

