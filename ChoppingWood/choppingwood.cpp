//
// Created by Leon Ericsson on 2022-01-28.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <queue>
#include <functional>

int main(){
    uint32_t N, v;
    std::cin >> N;

    std::vector<int32_t> degree(N+2, 1);
    std::vector<uint32_t> prufer(N);
    for(uint32_t i{0}; i < N; ++i){
        std::cin >> v;
        prufer[i] = v;
        if(i != N-1)
            degree[v]++;
    }


    std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<>> leafs;
    for(uint32_t i{1}; i < degree.size(); ++i){
        if(degree[i] == 1){
            leafs.push(i);
        }
    }

    std::vector<uint32_t> result(N);
    for(uint32_t i{0}; i < prufer.size(); ++i){
        auto u{leafs.top()};
        result[i] = u;
        leafs.pop();
        if(--degree[u] == 1){
            leafs.push(u);
        }
        if(--degree[prufer[i]] == 1){
            leafs.push(prufer[i]);
        }
    }

    for(uint32_t i{1}; i < degree.size(); ++i){
        if(degree[i] != 0){
            std::cout << "Error" << "\n";
            return 0;
        }
    }

    for(const auto& ele : result){
        std::cout << ele << "\n";
    }

    return 0;
}
