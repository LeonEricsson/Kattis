//
// Created by Leon Ericsson on 2022-01-20.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <ostream>

/*
 * Solves the classic knapsack problem by determining a subset of total N items which have the greatest
 * total value while still fitting into the knapsack that has capacity C. Program runs with
 * 0(N*C) time and memory complexity.
 * Usage:
 *      uint16_t[] knapsack(uint16_t C, Items[] items)
 *
 *      @param C        : Knapsack capacity
 *      @param items    : Items to choose from, a Item is defined by value, weight, index and prev*.
 *      @return         : vector of item indices which maximize total value.
 *
 */

struct Item{
    uint32_t value;
    uint32_t weight;
    uint16_t index;

    Item* prev = nullptr;

    bool operator<(const Item& other) const {
        return value < other.value;
    }
};

/*
 * This function uses Dynamic Programming to build a temporary array DP[][] in bottom-up
 * manner to avoid recomputation of the same subproblems. The DP table considers all possible
 * weights from 0 -> Capacity as its columns and items[i] as its rows where i: 0->N.
 */
std::vector<uint16_t> knapsack(uint16_t C, std::vector<Item>& items){
    std::vector<std::vector<Item>> DP(items.size()+1, std::vector<Item>(C + 1));
    for(uint32_t i{1}; i <= items.size(); ++i){
        for(uint32_t j{1}; j <= C; ++j){
            if(j < items[i-1].weight){
                DP[i][j] = DP[i-1][j];
            }

            else{
                if(DP[i-1][j-items[i-1].weight].value + items[i-1].value > DP[i-1][j].value){
                    DP[i][j].value = DP[i-1][j-items[i-1].weight].value + items[i-1].value;
                    DP[i][j].index = items[i-1].index;
                    DP[i][j].prev = &DP[i-1][j-items[i-1].weight];
                }
                else{
                    DP[i][j] = DP[i-1][j];
                }
            }
        }
    }
    std::vector<uint16_t> result;
    auto item{&DP[items.size()][C]};
    while(true){
        if(item->value)
            result.push_back(item->index);

        if(item->prev == nullptr)
            break;
        else{
            item = item->prev;
        }
    }
    return result;
}

/*

int main(){
    uint16_t C, n;
    while(std::cin >> C >> n){
        // Test case start
        std::vector<Item> items;
        items.reserve(n);
        for(uint16_t i{0}; i < n; ++i){
            uint16_t v,w;
            std::cin >> v >> w;
            items.emplace_back(Item{v,w,i});
        }
        auto result{knapsack(C,items)};

        std::cout << result.size() << "\n";
        for(const auto& ele : result){
            std::cout << ele << " ";
        }
        std::cout << "\n";
        items.clear();
    }
}*/
