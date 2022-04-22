//
// Created by Leon Ericsson on 2022-02-28.
//

#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
#include <numeric>

/*
 * Solves the 'All Pairs Shortest Path' problem in O(N^3) time. The graph is represented
 * as an adjacency matrix where cell [i][j] represents the edge weight going from node i
 * to node j.
 * Usage:
 *      int64_t[][] APSP(Matrix& adj, int32_t n)
 *
 *      @param edges    : Adjacency Matrix
 *      @param n        : Number of edges
 *
 *      return          : Distance matrix where cell [i][j] represents the optimal cost of going from node i to node j.
 */

const int32_t INF = std::numeric_limits<int32_t>::max();
using Matrix = std::vector<std::vector<int64_t>>;

/*
 * Uses the Floyd-Warshall algorithm to solve the 'All Pairs Shortest Path' problem with O(N^3)
 * time complexity. Adjacency matrix diagonal should be defined as the lowest of adj[u][v] & 0 while
 * the rest of the graph is init INF.
 */
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

/*
int main(){
    // ----------- INPUT -----------
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t n,m,q;
    while(std::cin >> n >> m >> q && (n + m + q != 0)){

        Matrix adj(n, std::vector<int64_t>(n, INF));
        // Initialize distance from node to itself as 0
        for(int32_t i{0}; i < n; ++i){
            adj[i][i] = 0;
        }

        int64_t u, v, w;
        for(int32_t i{0}; i < m; ++i){
            std::cin >> u >> v >> w;
            adj[u][v] = std::min(adj[u][v], w);
        }

        // --------------- SOLVER --------------
        auto solution = APSP(adj, n);

        // --------------- OUTPUT ---------------
        for(int32_t i{0}; i < q; ++i){
            std::cin >> u >> v;
            if(solution[u][v] == INF){
                std::cout << "Impossible\n";
            } else if(solution[u][v] == -INF){
                std::cout <<"-Infinity\n";
            } else{
                std::cout << solution[u][v] << "\n";
            }
        }
        std::cout << "\n";
    }
}*/