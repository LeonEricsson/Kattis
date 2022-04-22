//
// Created by Leon Ericsson on 2022-02-18.
//
#include <vector>
#include <iostream>
#include <functional>

/*
 * Solves the single-source shortest distance problem using Dijkstra's algorithm given a directed
 * or undirected weighted graph. All weights must be non-negative.
 * Usage:
 *      int32_t[] shortest_path(AdjList& adj, vector<int32_t> d, int32_t n, int32_t start)
 *
 *      @param adj      : The graph is represented as an adjacent list, for each vertex v adj[v] contains
 *                        a list of edges going from v and the weight of this edge.
 *      @param d        : Vector representing the cost to reach a vertex v as d[v]. All elements should be initialized to inf.
 *      @param n        : Number of nodes in the graph
 *      @param start    : Source node.
 *
 *      return          : Vector of predecessors where for each vertex v, p[v] is the penultimate vertext in the
 *                        shortest path from s to v.
 */


const int32_t INF = std::numeric_limits<int32_t>::max();
using AdjList = std::vector<std::vector<std::pair<int32_t, int32_t>>>;

/*
 * Uses Dijkstras algorithm to solve the problem with O(N^2) time complexity. It runs for n iterations,
 * at each iteration an unvisited vertex v with the lowest value d[v] is chosen. Then we iterate over
 * each adjacent vertex u from v and update d[u] according to the following relaxation
 *          d[u] = min(d[u], d[v] + edge cost)
 * After all adjacent vertexes have been considered we mark vertex v as visited and repeat the process
 * of finding the next vertex v.
 */
std::vector<int32_t> shortest_path(AdjList& adj, std::vector<int32_t>& d, int32_t n, int32_t start){
    std::vector<int32_t> p(n);
    std::vector<bool> visited(n, false);
    d[start] = 0;

    for(int32_t i{0}; i < n; ++i){
        int32_t v{-1};
        for(int32_t j{0}; j < n; ++j){
            if(!visited[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if(d[v] == INF)
            break;

        for(const auto& edge : adj[v]){
            if(auto cost = d[v] + edge.second; cost < d[edge.first]){
                d[edge.first] = cost;
                p[edge.first] = v;
            }
        }

        visited[v] = true;
    }

    return p;
}

// Adjacency list decides if directed or undirected!
// Initialize d(n, INF)

/*int main(){
    int32_t n,m,q,s;
    while(std::cin >> n >> m >> q >> s){
        // ------- INPUT ------
        if(n == 0 && m == 0 && q == 0 && s == 0)
            break;
        AdjList adj(n);
        int32_t u, v, w;
        for(int32_t i{0}; i < m; ++i){
            std::cin >> u  >> v >> w;
            adj[u].emplace_back(std::make_pair(v, w));
        }

        // ------- SOLVER -------
        std::vector<int32_t> d(n, INF);
        auto parents = shortest_path(adj,d, n, s);

        // ------- OUTPUT -------
        int32_t goal;
        for(int32_t i{0}; i < q; ++i){
            std::cin >> goal;
            if(d[goal] != INF)
                std::cout << d[goal] << "\n";
            else
                std::cout << "Impossible\n";
        }

    }
}*/