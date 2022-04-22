//
// Created by Leon Ericsson on 2022-02-23.
//

#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
#include <numeric>

// Couldn't get the #include to work so these are the unionfind.cpp functions
// ----------------------- UNION FIND -------------------------
uint32_t find_parent(uint32_t a, std::vector<uint32_t>& parents){
    if(a == parents[a]){
        return a;
    }
    return parents[a] = find_parent(parents[a], parents);
}

void union_sets(uint32_t a, uint32_t b, std::vector<uint32_t>& parents, std::vector<uint32_t>& size){
    auto p_a = find_parent(a, parents);
    auto p_b = find_parent(b, parents);

    if(p_a != p_b){
        if(size[p_a] > size[p_b]){
            parents[p_b] = p_a;
            size[p_a] += size[p_b];
        }
        else{
            parents[p_a] = p_b;
            size[p_b] += size[p_a];
        }
    }
}

bool same(uint32_t a, uint32_t b, std::vector<uint32_t>& parents){
    return find_parent(a, parents) == find_parent(b, parents);
}
// -----------------------------------


/*
 * Finds a minimum spanning tree from a list of edges. This program runs with O(M*LogN) time complexity
 * thanks to the usage of the disjoint set union data structure.
 * Usage:
 *      pair<int32_t,int32_t>[] mst(Edge[]& edges, int32_t n, int64_t& cost)
 *
 *      @param edges    : Vector of all edges in the graph.
 *      @param n        : Number of edges
 *      @param cost     : Cost of the minimum spanning tree, should be 0.
 *
 *      return          : Vector of edges that are a part of the minimum spanning tree.
 */

struct Edge{
    uint32_t u, v;
    int32_t w;
    bool operator<(Edge const& other) const{
        return w < other.w;
    }
};

/*
 * This algorithm runs in O(M*LogN) time thanks to the employment of union set finder. For each edge
 * we check if the edge endpoints are  part of the same subtree, if they are not we join these trees.
 * This continues until all edges have been iterated over, in a sorted order.
 */
std::vector<std::pair<int32_t, int32_t>> mst(std::vector<Edge>& edges, int32_t n, int64_t& cost){
    std::sort(edges.begin(), edges.end());
    // Initially, vertices make up a forest of single node trees. For the union finder, initialize all nodes
    // as their own parent.
    std::vector<uint32_t> parents(n);
    std::vector<uint32_t> size(n, 1);
    std::iota(parents.begin(), parents.end(), 0);
    // Result vector
    std::vector<std::pair<int32_t, int32_t>> min_tree;

    // O(M*LogN) time complexity
    for(const auto& e : edges){
        // If the edge connects to different subtrees, join the trees.
        if(!same(e.u, e.v, parents)){
            union_sets(e.u, e.v, parents, size);
            if(e.u < e.v)
                min_tree.emplace_back(std::make_pair(e.u, e.v));
            else
                min_tree.emplace_back(std::make_pair(e.v, e.u));
            cost += e.w;
        }
    }

    // Make sure the graph doesn't consist of multiple trees
    // O(N) time complexity
    for (int32_t i{1}; i < parents.size(); ++i) {
        if (!same(parents[i], parents[i-1], parents)){
            return std::vector<std::pair<int32_t, int32_t>>{};
        }
    }

    return min_tree;
}

int main(){
    // ----------- INPUT -----------
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t n, m;
    while(std::cin >> n >> m && (n != 0 || m != 0)){
        std::vector<Edge> e(m);
        for(int32_t i{0}; i < m; ++i){
            Edge temp{};
            std::cin >> temp.u >> temp.v >> temp.w;
            e[i] = temp;
        }
        // -------- SOLVER ---------
        int64_t cost{0};
        auto solution = mst(e, n, cost);

        // -------- OUTPUT ---------
        if(solution.empty()){
            std::cout << "Impossible\n";
            continue;
        }
        std::sort(solution.begin(), solution.end());
        std::cout << cost << "\n";
        for(const auto& ele: solution){
            std::cout << ele.first << " " << ele.second << "\n";
        }
    }
    return 0;
}