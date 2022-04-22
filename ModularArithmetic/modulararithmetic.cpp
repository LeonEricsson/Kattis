//
// Created by Leon Ericsson on 2022-04-18.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
/*
 * Implementation of a Modular operation class that handles modular arithmetic for +, -, / and *.
 * Usage:
 *      ModularOP(int n)
 *
 *      @param x      : Modulus
 *
 */

class ModularOP{
public:
    ModularOP() = default;
    explicit ModularOP(int64_t n) : n{n}{}

    // Compute the remainder of the operands independently to guarantee values smaller than 2n.
    int64_t add(int64_t& x, int64_t& y) const{
        return (x%n + y%n)%n;
    }

    int64_t sub(int64_t& x, int64_t& y) const{
        auto a = x - y;
        if(a < 0)
            a += n;
        return a;
    }

    // Uses the extended euclidean algorithm to find the modular inverse to solve x*y^-1 instead of x/y.
    int64_t div(int64_t& x, int64_t& y) const{
        if(std::gcd(y, n) != 1){ // Need to be relative prime
            return -1;
        }

        auto inv = exteuclid(y,n);
        return (x%n * inv%n)%n;
    }

    // Compute the remainder of the operands to reduce risk of overflow but not yet as good as sub/add (2n).
    int64_t mul(int64_t& x, int64_t& y) const{
        return (x%n * y%n)%n;
    }

    int64_t n;

private:
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
};

int main(){
    int32_t t;
    int64_t n,x,y;
    char op;
    while(std::cin >> n >> t){
        if(n == 0 && t == 0)
            break;
        ModularOP mod{n};
        for(int32_t i{0}; i < t; ++i){
            std::cin >> x >> op >> y;
            int64_t res{0};
            switch(op){
                case '+':
                    res = mod.add(x,y);
                    break;
                case '-':
                    res = mod.sub(x,y);
                    break;
                case '/':
                    res = mod.div(x,y);
                    break;
                case '*':
                    res = mod.mul(x,y);
                    break;
                default:
                    break;
            }
            std::cout << res << "\n";
        }
    }
    return 0;
}

