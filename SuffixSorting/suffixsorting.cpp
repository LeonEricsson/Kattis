//
// Created by Leon Ericsson on 2022-03-24.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>

/*
 * Given a string str of length N, constructs a suf object containing a suffix array that represents the starting indexes
 * of all the sorted suffixes in the given string. Time complexity O(NLogN).
 * Usage:
 *      Suffix(string str)
 *
 *      @param str          : String to create suf object from
 *
 *
 *      void buildArray(string str)
 *
 *      @param str          : String to create suf object from
 *
 *      int getSuffix(int i)
 *
 *      @param i            : suf index
 *
 *      return              : returns the suf of specific index
 *
 */

class Suffix{
public:
    explicit Suffix(std::string str){
        auto sorted = suffixArray(str);
        suf = sorted;
    }

    int32_t getSuffix(int32_t i){
        return suf[i];
    }

private:

    // Counting sort for cyclic substring of length 1
    void cSort(std::vector<int32_t> & c, std::vector<int32_t>& o, std::string& s) const{
        for(const auto & ch : s)
            c[ch]++;
        for (int32_t i{1}; i < ALPB; ++i)
            c[i] += c[i - 1];
        for (int32_t i{1}; i < s.size(); ++i)
            o[--c[s[i]]] = i;
    }

    /*
     * The idea here is to sort cyclic shifts by considering cyclic substrings of increasing sizes without
     * storing the suffixes in temporary variables, maps etc. We begin by appending a character to the
     * string which has a lower ASCII value than all other possible chars that may appear. This sorting
     * algorithm will be called Log N times where each iteration sorts the n cyclic substrings of length
     * 2^k (k'th iteration). In each iteration we use a variation of Radix Sort to sort the substrings
     * in O(N) time resulting in a total complexity of O(NLogN).
     */
    std::vector<int32_t> suffixArray(std::string& str){
        str += 0x1f;
        std::vector<int32_t> order(str.size()), clas(str.size(), 0), count(std::max(ALPB, static_cast<int32_t>(str.size())), 0);
        cSort(count, order, str);

        // Equivalence classes for cyclic substring of length 1
        int32_t cl{1};
        for (int32_t i{1}; i < str.size(); ++i) {
            if (str[order[i]] != str[order[i - 1]])
                ++cl;
            clas[order[i]] = cl - 1;
        }

        std::vector<int32_t> ordern(str.size()), clasn(str.size());
        for (int32_t h{0}; (1 << h) < str.size(); ++h) {
            for (int32_t i{0}; i < str.size(); ++i) {
                ordern[i] = order[i] - (1 << h);
                if (ordern[i] < 0)
                    ordern[i] += str.size();
            }
            fill(count.begin(), count.begin() + cl, 0);
            // Counting Sort
            for (int32_t i{0}; i < str.size(); ++i)
                count[clas[ordern[i]]]++;
            for (int32_t i{1}; i < cl; ++i)
                count[i] += count[i - 1];
            for (int32_t i = str.size()-1; i >= 0; --i)
                order[--count[clas[ordern[i]]]] = ordern[i];
            // Equivalence classes
            clasn[order[0]] = 0;
            cl = 1;
            for (int32_t i = 1; i < str.size(); i++) {
                auto cur = std::make_pair(clas[order[i]], clas[(order[i] + (1 << h)) % str.size()]);
                auto prev = std::make_pair(clas[order[i - 1]], clas[(order[i - 1] + (1 << h)) % str.size()]);
                if (cur != prev)
                    ++cl;
                clasn[order[i]] = cl - 1;
            }
            clas.swap(clasn);
        }
        order.erase(order.begin());
        return order;
    }

    std::vector<int32_t> suf;
    const int32_t ALPB{256};
};


int main(){
    std::string str;
    int32_t n, q;
    while(std::getline(std::cin, str)){
        Suffix sa(str);

        std::cin >> n;
        for(int32_t i{0}; i < n; ++i){
            std::cin >> q;
            std::cout << sa.getSuffix(q) << " ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n";
    }
    return 0;
}