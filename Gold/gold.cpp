//
// Created by Leon Ericsson on 2022-02-18.
//

#include <vector>
#include <iostream>
#include <queue>
#include <functional>

struct Node;
using Matrix = std::vector<std::vector<Node>>;

const std::vector<int32_t> u{-1, 0, 1, 0};
const std::vector<int32_t> w{0, 1, 0, -1};

struct Node{
    Node() = default;
    Node(int32_t i, int32_t j) : i(i), j(j){}
    char value = '#';
    bool visited = false;
    int32_t i = 0;
    int32_t j = 0;
};

void addChildren(Matrix& map, std::queue<Node*>& queue, Node* cur){
    for(int32_t k{0}; k < 4; ++k){
        auto temp = map[cur->i + u[k]][cur->j + w[k]];
        if(temp.value == 'T')
            return;
    }

    for(int32_t k{0}; k < 4; ++k){
        auto temp = &map[cur->i + u[k]][cur->j + w[k]];
        queue.push(temp);
    }
}

int32_t bfs(Matrix& map, Node* start){
    std::queue<Node*> queue;
    queue.push(start);

    int32_t gold{0};
    while(!queue.empty()){
        auto cur = queue.front();
        queue.pop();
        if(cur->visited || cur->value == '#')
            continue;
        else if (cur->value == 'G')
            ++gold;

        addChildren(map, queue, cur);
        cur->visited = true;
    }
    return gold;
}


int main(){
    int32_t W, H;
    std::cin >> W >> H;
    Matrix map(H, std::vector<Node>(W));
    Node* start;
    for(int32_t i{0}; i < H; ++i){
        for(int32_t j{0}; j < W; ++j){
            Node temp{i,j};
            std::cin >> temp.value;
            map[i][j] = temp;
            if(temp.value == 'P'){
                start = &map[i][j];
            }
        }
    }

    std::cout << bfs(map, start);

}