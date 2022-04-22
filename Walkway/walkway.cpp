//
// Created by Leon Ericsson on 2022-03-10.
//


#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <queue>

struct Node{
    int32_t a,b,h,i;
    double cost;
};

const double INF = std::numeric_limits<double>::max();
using AdjList = std::vector<std::vector<Node>>;

int32_t matchingSide(Node a, Node b){
    int32_t side{0};
    if(a.a == b.a || a.a == b.b)
        side = a.a;
    else if(a.b == b.a || a.b == b.b)
        side = a.b;
    return side;
}

std::vector<int32_t> shortest_path(AdjList& adj, std::vector<double>& d, std::vector<Node>& stones, int32_t n, int32_t start){
    std::vector<int32_t> p(n);
    std::vector<bool> visited(n, false);
    d[start] = 0;
    int32_t prev;
    for(int32_t i{0}; i < n; ++i){
        int32_t v{-1};
        for(int32_t j{0}; j < n; ++j){
            if(!visited[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if(d[v] == INF)
            break;

        for(const auto& node : adj[v]){
            if(auto cost = d[v] + node.cost; cost < d[node.i]){
                prev = matchingSide(stones[v], node);
                d[node.i] = cost;
                p[node.i] = v;
            }
        }

        visited[v] = true;
    }

    return p;
}


int main(){
    int32_t n;
    while(std::cin >> n && n){
        int32_t a,b,h;
        std::vector<Node> stones(n);
        AdjList adj(n+2);
        for(int32_t i{0}; i < n; ++i){
            Node temp{};
            std::cin >> temp.a >> temp.b >> temp.h;
            temp.cost = ((temp.a + temp.b)/2.0 * temp.h)*0.02;
            temp.i = i;
            for(int32_t j{0}; j < stones.size(); ++j){
                if(stones[j].a == temp.a || stones[j].a == temp.b || stones[j].b == temp.b || stones[j].b == temp.a){
                    adj[i].push_back(stones[i]);
                    adj[j].push_back(temp);
                }
            }
            stones[i] = temp;
        }
        int32_t porch_w, gaz_w;
        std::cin >> porch_w >> gaz_w;
        Node porch{porch_w, 0, 0, n};
        Node gaz{gaz_w, 0, 0, n+1};
        for(int32_t i{0}; i < stones.size(); ++i){
            if(stones[i].a == porch.a || stones[i].b == porch.b){
                adj[n].push_back(stones[i]);
            }
            if(stones[i].a == gaz.a || stones[i].b == gaz.a){
                adj[i].push_back(gaz);
            }
        }

        std::vector<double> d(n+2, INF);
        auto parents = shortest_path(adj, d, stones, n+2, n);

        std::cout << d[n+1] << "\n";
    }



    return 0;
}