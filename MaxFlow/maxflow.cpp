//
// Created by Leon Ericsson on 2022-03-01.
//

#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
#include <numeric>
#include <queue>
#include <deque>
#include <tuple>

/*
 * Solves the maximum flow problem given a flow network on a directed graph with N nodes and E edges, where
 * each edge has a capacity C. Algorithm runs with O(VE^2) time complexity.
 * Usage:
 *      void max_flow(AdjList& adj, Matrix& cap, int32_t s, int32_t t, int32_t n)
 *
 *      @param Adj      : Adjacency list
 *      @param cap      : Residual capacity matrix
 *      @param s        : Source node
 *      @param t        : Sink node
 *      @param n        : Number of vertices

 */
const int32_t INF = std::numeric_limits<int32_t>::max();
using AdjList = std::vector<std::vector<int32_t>>;
using Matrix = std::vector<std::vector<int32_t>>;
using Result = std::tuple<std::deque<int32_t>, int32_t>;
using Triple = std::tuple<int32_t, int32_t, int32_t>;

/*
 * BFS used to find the next augmententing path from source -> sink thus giving the
 * complexity O(VE^2). This BFS returns the shortest path from s to t along with the
 * maximum flow / minimum residual capacity for this path.
 */
Result bfs(AdjList& adj, Matrix& cap, int32_t n, int32_t start, int32_t goal){
    std::vector<bool> visited(n, false);
    std::vector<int32_t> parent(n, -1);
    std::queue<int32_t> q;
    q.push(start);
    visited[start] = true;

    while(!q.empty()){
        auto cur = q.front();
        q.pop();

        // Add adjacent nodes to queue if they have residual capacity and not yet explored.
        for(const auto& dest: adj[cur]){
            if(!visited[dest] && cap[cur][dest]){
                visited[dest] = true;
                q.push(dest);
                parent[dest] = cur;
                if(dest == goal)
                    goto endloop;
            }
        }
    }

endloop:
    std::deque<int32_t> path;
    int32_t min_cap{INF};
    int32_t c;

    // Retrieve path from s to t along with minimum residual capacity.
    for (int32_t i{goal} ; parent[i] != -1; i = parent[i]) {
        path.push_front(i);
        c = cap[parent[i]][i];
        if(c < min_cap)
            min_cap = c;
    }

    return {path, min_cap};
}

/*
 * Maximum flow algorithm using BFS to find next augmenting path. Capacity matrix is stored as residual
 * capacity and the flow in the network is not stored but rather calculated in the output by
 * (capacity - residual capacity).
 *
 */
void max_flow(AdjList& adj, Matrix& cap, int32_t s, int32_t t, int32_t n){
    while(true){
        auto [path, new_flow] = bfs(adj, cap, n, s, t);
        if(path.empty())
            break;

        int32_t cur = s;
        // Update residual capacity for both directions of each edge in the augmented path.
        for(const auto& v : path){
            cap[cur][v] -= new_flow;
            cap[v][cur] += new_flow;
            cur = v;
        }
    }

}

/*int main(){
    // ----------- INPUT -----------
    int32_t n, m, s, t;
    std::cin >> n >> m >> s >> t;

    int32_t u, v, c;
    AdjList adj(n);
    Matrix residual_cap(n, std::vector<int32_t>(n, 0));
    for(int32_t i{0}; i < m; ++i){
        std::cin >> u >> v >> c;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        residual_cap[u][v] += c;
    }
    auto cap{residual_cap};

    // --------------- SOLVER --------------
    max_flow(adj, residual_cap, s, t, n);

    // --------------- OUTPUT ---------------
    int32_t max_flow{0};
    std::vector<Triple> edges;
    for(int32_t i{0}; i < n; ++i){
        for(int32_t j{0}; j < n; ++j){
            if(auto flow = cap[i][j] - residual_cap[i][j]; flow > 0){
                edges.emplace_back(std::make_tuple(i, j, flow));
                if(j == t)
                    max_flow += flow;
            }
        }
    }

    std::cout << n << " " << max_flow << " " << edges.size() << "\n";
    for(const auto& e : edges){
        std::cout << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e) << "\n";
    }
}*/