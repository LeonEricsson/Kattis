//
// Created by Leon Ericsson on 2022-03-04.
//

#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
#include <numeric>
#include <queue>
#include <deque>
#include <tuple>
#include <stack>

/*
 * Find an eulerian path in the given graph if such exists, graph is directed and could be multigraph. Solves
 * the problem with O(N+E) time complexity.
 * Usage:
 *      int32_t[] eulerian_path(AdjList& adj, int32_t n, int32_t m)
 *
 *      @param adj      : Adjacency List containing internal Node representation.
 *      @param n        : Number of vertices
 *      @param m        : Number of edges
 *
 *      return          : Eulerian path
 */

struct Node; // forward decleration
using AdjList = std::vector<Node>;

// Internal node representation
struct Node{
    int32_t to,from;
    std::deque<int32_t> nb;
};

/* Conditions for an eulerian path in directed graph:
 * - At most one vertex, an, with (out-degree) - (in-degree) = 1
 * - At most one vertex, bn, with (in-degree) - (out-degree) = 1
 * - Remaining vertices have (in-degree) = (out-degree)
 * Time complexity O(N)
 */
bool path_exists(AdjList& adj, int32_t& an, int32_t& bn, int32_t n){
    int32_t c1{0}, c2{0};
    for(int32_t i{0}; i < n; ++i){
        if(adj[i].from - adj[i].to == 1){
            an = i;
            ++c1;
        } else if(adj[i].to - adj[i].from == 1){
            bn = i;
            ++c2;
        } else if(adj[i].to == adj[i].from){
            continue;
        } else{
            return false;
        }
    }

    if(c1 > 1 || c2 > 1)
        return false;

    // Add vertex bn -> an so that all vertices have (in-degree) = (out-degree)
    if(c1 && c2) {
        adj[bn].nb.push_back(an);
        ++adj[bn].from;
    }

    return true;
}

/*
 * Find an eulerian path in the graph that is modified by path_exists() using Hierholzer's
 * algorithm, time complexity O(N + E). First we determine if the path exists and if one
 * does, we make sure all vertices have (in-degree) = (out-degree). This means the graph now
 * contains an eulerian cycle. We run through Hierholzers algorithm and finally we retrieve
 * the eulerian path from the modified graph by removing the edge we added.
 */
std::vector<int32_t> eulerian_path(AdjList& adj, int32_t n, int32_t m){
    std::vector<int32_t> path;
    int32_t an{-1}, bn{-1};
    if(!path_exists(adj, an, bn, n))
        return path;


    std::stack<int32_t> st;
    st.push((an == -1) ? 0 : an);

    int32_t v;
    while(!st.empty()){
        v = st.top();
        if(!adj[v].from){
            path.push_back(v);
            st.pop();
        } else {
            auto neighbor{adj[v].nb.front()};
            st.push(neighbor);
            adj[v].nb.pop_front();
            --adj[v].from;
        }
    }
    std::reverse(path.begin(), path.end());

    // Graph naturally contains eulerian cycle
    if(an == -1 && bn == -1)
        return path;

    // Check if the graph is disconnected in which case no eulerian path exists
    if(path.size() - 1 != m + 1)
        return std::vector<int32_t>{};

    // 'Remove' the edge we added to retrieve the euler path
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        if ((path[i] == bn && path[i + 1] == an)) {
            std::vector<int32_t> path2;
            for (size_t j = i + 1; j < path.size(); ++j)
                path2.push_back(path[j]);
            for (size_t j = 1; j <= i; ++j)
                path2.push_back(path[j]);
            path = path2;
            break;
        }
    }

    return path;
}

/* Initializing adjacency list:
 * A new edge from U to V -> Push V into vector adj[u].nb,
 * increment adj[u].from and adj[v].to.
*/

int main(){
    // --------- INPUT --------
    int32_t n,m;
    while(std::cin >> n >> m && (n + m != 0)){
        int32_t u,v;
        AdjList adj(n);
        for(int32_t i{0}; i < m; ++i){
            std::cin >> u >> v;
            ++adj[u].from;
            ++adj[v].to;
            adj[u].nb.push_back(v);
        }

        // --------- SOLVER ---------
        auto path = eulerian_path(adj, n, m);

        // --------- OUTPUT ---------
        if(path.empty()){
            std::cout << "Impossible\n";
        } else{
          for(const auto& node: path){
              std::cout << node << " ";
          }
          std::cout << "\n";
        }
    }
}