//
// Created by Leon Ericsson on 2022-03-24.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
/*
 * Given a text and a pattern find the occurences sub-strings in the text that match the pattern. Uses
 * Knuth-Morris-Pratt to achieve complexity O(text + pattern).
 * Usage:
 *      int32_t[] find(string pattern, string text)
 *
 *      @param pattern      : Pattern to find
 *      @param text         : Text to search in
 *
 *      return              : Vector containing the positions of all the occurences of pattern in the text.
 */

/* Preprocess the pattern and return an auxiliary array lps where
 * lps[i] is the length of the longest proper prefix of the substring
 * pattern[0->i] which is also a suffix of the pattern.
*/
std::vector<int32_t> LPS(std::string& pattern){
    std::vector<int32_t> lps(pattern.size(), 0);
    int32_t i{1}, j{0};
    while(i < pattern.size()){
        if(pattern[i] == pattern[j]){
            lps[i++] = ++j;
        } else{
            if(j != 0)
                j = lps[j-1];
            else
                lps[i++] = 0;
        }
    }
    return lps;
}

/*
 * Knutt-Morris-Pratt algorithm, we begin by pre-processing the pattern to retrieve LSP array by
 * iterating over the pattern once requiring O(pattern). Following the pre-processing we iterate
 * over the text once while identifying any pattern matches, with the help of the LSP we achieve
 * this with O(text) complexity resulting in total O(pattern + text).
 *
 */
auto find(std::string pattern, std::string text){
    auto lps = LPS(pattern);

    int32_t i{0}; // Index for text
    int32_t j{0}; // Index for pattern
    std::vector<int32_t> pos;
    while(i < text.size()){
        if(pattern[j] == text[i]){
            ++j, ++i;
            if(j == pattern.size()){
                pos.push_back(i - pattern.size());
                j = lps[j-1];
            }
        } else{
            if(j){
                j = lps[j-1];
            } else {
                ++i;
            }
        }
    }
    return pos;
}

int main(){
    std::string p, t;
    while(std::getline(std::cin, p) && std::getline(std::cin, t)){
        auto pos = find(p, t);
        for(const auto& x : pos){
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}