//
// Created by Leon Ericsson on 2022-04-11.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
using Vector = std::vector<std::pair<int32_t, int32_t>>;

int32_t nrSubstrings(std::vector<std::string>& dict, std::string& message){
    Vector wordIntervals;
    for(const auto& word : dict){
        auto i = message.find(word);
        while(i != std::string::npos){
            wordIntervals.emplace_back(std::make_pair(i, i + word.length() - 1));
            i = message.find(word, ++i);
        }
    }

    if(wordIntervals.empty())
        return 0;


    std::sort(wordIntervals.begin(), wordIntervals.end(), [](const auto& w1, const auto& w2){
        return w1.second < w2.second;
    });

    int32_t counter{1};
    auto e = wordIntervals[0].second;
    for(int32_t i{1}; i < wordIntervals.size(); ++i){
        if(wordIntervals[i].first > e){
            e = wordIntervals[i].second;
            ++counter;
        }
    }

    return counter;
}


int main(){
    std::vector<std::string> dict;
    std::string word;
    while(std::getline(std::cin, word) && word != "#"){
        dict.push_back(word);
    }

    std::string message;
    while(std::getline(std::cin, word) && word != "#"){
        message.append(word);
        if(message[message.size() - 1] == '|'){
            message.pop_back();
            std::cout << nrSubstrings(dict, message) << "\n";
            message.clear();
        }
    }
}

