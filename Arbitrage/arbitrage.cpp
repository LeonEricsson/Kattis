//
// Created by Leon Ericsson on 2022-03-10.
//

#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
#include <numeric>
#include <string>
#include <map>

const int32_t INF = std::numeric_limits<int32_t>::max();
using Matrix = std::vector<std::vector<int64_t>>;

Matrix APSP(Matrix& adj, int32_t n){
    auto DP = adj;

    // O(N^3) time complexity
    for(int32_t k{0}; k < n; ++k){
        for(int32_t i{0}; i < n; ++i){
            for(int32_t j{0}; j < n; ++j){
                // Ignore paths that don't exist
                if(DP[i][k] < INF && DP[k][j] < INF){
                    // Update the k'th phase of DP taking the shorter path of i->j and i->k->j
                    DP[i][j] = std::min(DP[i][j], DP[i][k] + DP[k][j]);
                }
            }
        }
    }
    // Rerun the FW algorithm to find any nodes in or affected by a negative cycle, setting these
    // optimal distances to -INF.
    for(int32_t k{0}; k < n; ++k){
        for(int32_t i{0}; i < n; ++i){
            for(int32_t j{0}; j < n; ++j){
                // Ignore paths that don't exist and set cycle effected nodes
                if(DP[i][k] < INF && DP[k][j] < INF && DP[k][k] < 0){
                    DP[i][j] = -INF;
                }
            }
        }
    }

    return DP;
}

int main(){
    int32_t C;
    while(std::cin >> C && C != 0){

        Matrix adj(C, std::vector<int64_t>(C, INF));

        // Initialize distance from node to itself as 0
        for(int32_t i{0}; i < C; ++i){
            adj[i][i] = 1;
        }

        // -- READ INPUT ---
        std::string CUR;
        std::map<std::string, int32_t> m;
        for(int32_t i{0}; i < C; ++i){
            std::cin >> CUR;
            m[CUR] = i;
        }

        int32_t R;
        std::cin >> R;
        std::string CUR1, CUR2;
        int32_t EX1, EX2;
        for(int32_t i{0}; i < R; ++i){
            std::cin >> CUR1 >> CUR2 >> EX1;
            std::cin.ignore(1) >> EX2;
            EX2 /= EX1;
            adj[m[CUR1]][m[CUR2]] = EX2;
        }

        APSP(adj, C);

        for(int32_t i{0}; i < R; ++i){
            if(adj[i][i] < 0){
                std::cout << "Arbitrage\n";
                return 0;
            }
        }

        std::cout << "Ok\n";

    }
    return 0;
}
