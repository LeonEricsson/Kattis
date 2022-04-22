//
// Created by Leon Ericsson on 2022-03-10.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <queue>

using AdjList = std::vector<std::vector<int32_t>>;

std::vector<int32_t> bfs2(AdjList& adj, int32_t n, int32_t start){
    std::vector<bool> visited(n+1, false);
    std::queue<int32_t> q;
    q.push(start);
    visited[start] = true;

    while(!q.empty()){
        auto cur = q.front();
        q.pop();

        for(const auto& dest: adj[cur]){
            if(!visited[dest]){
                visited[dest] = true;
                q.push(dest);
            }
        }
    }
    std::vector<int32_t> result;
    for(int32_t i{1}; i<n+1; ++i){
        if(!visited[i])
            result.push_back(i);
    }
    return result;
}

int main(){
    int32_t N,M,a,b;
    std::cin >> N >> M;
    AdjList adj(N+1);
    for(int32_t i{0}; i < M; ++i){
        std::cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto sol = bfs2(adj, N, 1);

    if(sol.empty()){
        std::cout << "Connected\n";
    } else{
        for(const auto& x : sol){
            std::cout << x << "\n";
        }
    }

    return 0;
}