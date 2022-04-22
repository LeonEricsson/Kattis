//
// Created by Leon Ericsson on 2022-02-22.
//

//
// Created by Leon Ericsson on 2022-02-18.
//
#include <vector>
#include <iostream>
#include <functional>

/*
 * Solves the single-source shortest distance problem using Dijkstra's algorithm given a directed
 * or undirected time-table graph, i.e a graph where an edge may only be used during certain
 * time intervals. All weights must be non-negative.
 * Usage:
 *      int32_t[] shortest_path(AdjList& adj, vector<int32_t> d, int32_t n)
 *
 *      @param adj      : The graph is represented as an adjacent list, for each vertex v adj[v] contains
 *                        a list of edges going from v with their start time, interval and travel duration.
 *      @param d        : Vector representing the cost to reach a vertex v as d[v]. All elements should be initialized to inf.
 *      @param n        : Number of nodes in the graph
 *
 *      return          : Vector of predecessors where for each vertex v, p[v] is the penultimate vertext in the
 *                        shortest path from s to v.
 */

struct Edge{
    int32_t dest;
    int32_t t0;
    int32_t P;
    int32_t d;
};

const int32_t INF = std::numeric_limits<int32_t>::max();
using AdjList = std::vector<std::vector<Edge>>;

/*
 * Uses Dijkstras algorithm to solve the problem with O(N^2 + E) time complexity. It runs for n iterations,
 * at each iteration an unvisited vertex v with the lowest value d[v] is chosen. Then we iterate over
 * each adjacent vertex u from v and update d[u] according to the following relaxation
 *          d[u] = min(d[u], d[v] + edge cost)
 * After all adjacent vertexes have been considered we mark vertex v as visited and repeat the process
 * of finding the next vertex v.
 */
std::vector<int32_t> shortest_path(AdjList& adj, std::vector<int32_t>& d, int32_t n){
    std::vector<int32_t> p(n);
    std::vector<bool> visited(n, false);

    for(int32_t i{0}; i < n; ++i){
        int32_t v{-1};
        for(int32_t j{0}; j < n; ++j){
            if(!visited[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if(d[v] == INF)
            break;

        for(const auto& edge : adj[v]){
            int32_t wait{0};
            if(edge.P == 0 || d[v] < edge.t0){
                wait = edge.t0 - d[v];
            } else {
                auto diff = (d[v] - edge.t0) % edge.P;
                wait = diff ? edge.P - diff : 0;
            }
            if(auto cost = d[v] + wait + edge.d; cost < d[edge.dest] && wait >= 0){
                d[edge.dest] = cost;
                p[edge.dest] = v;
            }
        }
        visited[v] = true;
    }
    return p;
}

/*
int main(){
    int32_t n,m,q,s;
    while(std::cin >> n >> m >> q >> s){
        // ------- INPUT ------
        if(n == 0 && m == 0 && q == 0 && s == 0)
            break;
        AdjList adj(n);
        int32_t u;
        for(int32_t i{0}; i < m; ++i){
            Edge temp{};
            std::cin >> u >> temp.dest >> temp.t0 >> temp.P >> temp.d;
            adj[u].emplace_back(temp);
        }

        // ------- SOLVER -------
        std::vector<int32_t> d(n, INF);
        d[s] = 0;
        auto parents = shortest_path(adj,d, n);

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