//
// Created by Leon Ericsson on 2022-04-20.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

/*
 * Implementation of Sieve of Erathostenes for finding all primes from [1:n]. This is implemented
 * in a class Primes where the constructor constructs the prime array in O(n*log(log(n))) time, then
 * prime lookups are constant using the [] operator. During construction, for every prime number we have
 * to check the multiples of this prime and mark them as composite. The count() function gives the total number of primes
 * in the range. The program uses O(n/8) memory due to the memory optimization of using a vector<bool> in
 * c++ where each bool is represented as a single bit.
 *
 */

class Primes{
public:
    explicit Primes(int32_t n){
        prime.resize(n+1, true);
        prime[0] = prime[1] = false;
        for(int32_t i{2}; i*i <= n; ++i){
            if(prime[i])
                for(int32_t j{i*i}; j <= n; j += i)
                    prime[j] = false;
        }
    }

    int64_t count(){
        return std::count(prime.cbegin(), prime.cend(), true);
    }

    int32_t operator[](int32_t i){
        return prime[i];
    }

private:
    std::vector<bool> prime;
};

int main(){
    int32_t n, q, x;
    std::cin >> n >> q;
    Primes p(n);
    std::cout << p.count() << "\n";
    while(q--){
        std::cin >> x;
        std::cout << p[x] << "\n";
    }
}