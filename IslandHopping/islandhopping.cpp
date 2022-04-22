//
// Created by Leon Ericsson on 2022-02-28.
//

//
// Created by Leon Ericsson on 2022-02-23.
//


#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <iomanip>

struct Edge{
    int32_t u,v;
    double w;
    bool operator<(Edge const& other) const{
        return w < other.w;
    }
};

struct Node{
    double x,y;
    int32_t id;
};

double mst(std::vector<Edge>& edges, int32_t n){
    std::sort(edges.begin(), edges.end());
    // Initially, vertices make up a forest of single node trees.
    std::vector<int32_t> tree_id(n);
    std::iota(tree_id.begin(), tree_id.end(), 0);
    double cost{0};
    for(const auto& e : edges){
        // If the edge 'ends' aren't a part of the same subtree, join the trees.
        if(tree_id[e.u] != tree_id[e.v]){
            auto old_id{tree_id[e.v]};
            std::replace(tree_id.begin(), tree_id.end(), old_id, tree_id[e.u]);
            cost += e.w;
        }
    }
    return cost;
}

int main(){
    // ----------- INPUT -----------
    int32_t n, m;
    std::cin >> n;
    while(n--){
        std::cin >> m;
        double x, y;
        std::vector<Edge> e;
        std::vector<Node> nodes;
        int32_t counter{0};
        for(int32_t i{0}; i < m; ++i){
            Node temp{};
            std::cin >> temp.x >> temp.y;
            temp.id = counter++;
            for(const auto& node : nodes){
                Edge temp2{};
                temp2.u = temp.id;
                temp2.v = node.id;
                temp2.w = std::sqrt((node.x - temp.x)*(node.x-temp.x) + (node.y-temp.y)*(node.y-temp.y));
                e.push_back(temp2);
            }
            nodes.push_back(temp);
        }
        // -------- SOLVER ---------
        double solution = mst(e, counter);
        // -------- OUTPUT ---------
        std::cout << std::setprecision(15) << solution << "\n";
    }
    return 0;
}