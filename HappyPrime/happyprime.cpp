//
// Created by Leon Ericsson on 2022-04-17.
//

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

bool isHappyPrime(int32_t m){
    std::vector<int32_t> prev;
    std::string m_str;
    int32_t c_int;
    while(true){
        prev.push_back(m);
        m_str = std::to_string(m);
        m = 0;
        for(const auto& c : m_str){
            c_int = c - '0';
            m += (c_int * c_int);
        }
        if(m == 1){
            return true;
        }
        if(std::count(prev.begin(), prev.end(), m) != 0){
            return false;
        }
    }

}

bool isPrime(int32_t& m){
    if(m == 1 || m == 2)
        return false;
    for(int32_t i{2}; i < m; ++i){
        if(m % i == 0)
            return false;
    }
    return true;
}

int main(){
    int32_t P, K, m;
    std::cin >> P;
    while(P--){
        std::cin >> K >> m;
        std::string result{"NO"};
        if(isPrime(m)){
            result = isHappyPrime(m) ? "YES" : "NO";
        }

        std::cout << K << " " << m << " " << result << "\n";
    }
    return 0;
}