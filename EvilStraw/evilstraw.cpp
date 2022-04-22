//
// Created by Leon Ericsson on 2022-03-25.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <queue>
#include <unordered_map>
#include <string>

using Map = std::unordered_map<char, int32_t>;

bool palindromeExists(Map& chars){
    bool odd{false};
    for(const auto& [c, count] : chars){
        if(count % 2 != 0){
            if(odd)
                return false;
            else
                odd = true;
        }
    }
    return true;
}

int32_t findMatch(char c, std::string& str, bool fromRight, int32_t start){
    if(fromRight){
        for(int32_t i{static_cast<int32_t>(str.length()-1-start)}; i > start; --i){
            if(str[i] == c)
                return i;
        }
    } else {
        for(int32_t i{start}; i < str.length()-start; ++i){
            if(str[i] == c)
                return i;
        }
    }
    return -1;
}

int32_t swap(std::string& str, int32_t index, int32_t goal, int32_t step){
    int32_t counter{0};
    while(index != goal){
        char tmp = str[index];
        str[index] = str[index + step];
        str[index += step] = tmp;
        counter++;
    }
    return counter;
}
int32_t palindromeSwapsReverse(std::string& str, int32_t start){
    int32_t swaps{0};
    for(int32_t i{start}; i > str.length()/2; --i){
        auto ind = findMatch(str[i], str, false, static_cast<int32_t>(str.length()) - 1 - i);
        auto goal = static_cast<int32_t>(str.length()) - 1 - i;
        swaps += swap(str, ind, goal, -1);
    }
    return swaps;
}

int32_t palindromeSwaps(std::string& str){
    int32_t swaps{0};
    for(int32_t i{0}; i < str.length()/2; ++i){
        auto ind = findMatch(str[i], str, true, i);
        if(ind == -1){
            return swaps + palindromeSwapsReverse(str, static_cast<int32_t>(str.length()) - 1 - i);
        }
        auto goal = static_cast<int32_t>(str.length()) - 1 - i;
        swaps += swap(str, ind, goal, 1);
    }
    return swaps;
}

int main(){
    int32_t n;
    std::string s;
    std::cin >> n;
    while(n--){
        std::cin >> s;

        Map characters;
        for(const auto& c : s){
            characters[c]++;
        }

        if(palindromeExists(characters)){
            std::cout << palindromeSwaps(s) << "\n";
        } else {
            std::cout << "Impossible\n";
        }
    }
    return 0;
}