//
// Created by Leon Ericsson on 2022-02-22.
//

#include <vector>
#include <iostream>
#include <functional>

/*
 * Solves the single-source shortest distance problem using Bellman-Ford's algorithm given a directed
 * or undirected weighted graph with negative weights and cycles.
 * Usage:
 *      int32_t[] shortest_path(vector<Edge>& edges, vector<int32_t> d, int32_t n)
 *
 *      @param edges    : Graph represented as a vector of all edges.
 *      @param d        : Vector representing the cost to reach a vertex v as d[v]. All elements initialized to inf except
 *                        start vertex which has value 0.
 *      @param n        : Number of nodes in the graph
 *
 *      return          : Vector of predecessors where for each vertex v, p[v] is the penultimate vertext in the
 *                        shortest path from s to v.
 */

const int32_t INF = std::numeric_limits<int32_t>::max();

struct Edge{
    int32_t u, v, w;
};

/*
 * Uses Bellman-Ford to solve the problem with O(N*E) time complexity, the main SSSP algorithm runs for n-1
 * iterations where we for each iterate over all edges updating the cost in the d vector. If nothing changes
 * for an entire iteration the algorithm can exit. To solve the case for negative cycles, we run the algorithm
 * again for n-1 iterations over all edges for each iteration. If we are able to update a vertex with a better
 * cost then it is a part of or reachable from the negative cycle.
 */
std::vector<int32_t> shortest_path(std::vector<Edge>& edges, std::vector<int32_t>& d, int32_t n) {
    std::vector<int32_t> p(n);
    bool changed;
    for(int32_t i{0}; i < n-1; ++i){
        changed = false;
        for(int32_t j{0}; j < edges.size(); ++j){
            if(d[edges[j].u] < INF && d[edges[j].u] + edges[j].w < d[edges[j].v]){
                d[edges[j].v] = std::max(-INF, d[edges[j].u] + edges[j].w);
                p[edges[j].v] = edges[j].u;
                changed = true;
            }
        }
        if(!changed)
            return p;
    }

    for(int32_t i{0}; i < n-1; ++i){
        changed = false;
        for(int32_t j{0}; j < edges.size(); ++j){
            if(d[edges[j].u] < INF && (d[edges[j].u] == -INF || d[edges[j].u] + edges[j].w < d[edges[j].v])){
                d[edges[j].v] = -INF;
                p[edges[j].v] = edges[j].u;
                changed = true;
            }
        }
        if(!changed)
            return p;
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
        std::vector<Edge> edges(m);
        for(int32_t i{0}; i < m; ++i){
            Edge temp{};
            std::cin >> temp.u >> temp.v >> temp.w;
            edges[i] = temp;
        }

        // ------- SOLVER -------
        std::vector<int32_t> d(n, INF);
        d[s] = 0;
        auto parents = shortest_path(edges, d, n);

        // ------- OUTPUT -------
        int32_t goal;
        for(int32_t i{0}; i < q; ++i){
            std::cin >> goal;
            if(d[goal] == INF)
                std::cout << "Impossible\n";
            else if(d[goal] == -INF)
                std::cout << "-Infinity\n";
            else
                std::cout << d[goal] << "\n";
        }
    }
    return 0;
}*/