//
// Created by Leon Ericsson on 2022-03-24.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

/*
 * Given a string str of length N and a suffix array, this program constructs a Longest Common Prefix array
 * using Kasai's Algorithm.  Time complexity O(N).
 * Usage:
 *      Suffix(string str)
 *
 *      @param str          : String to create suf and lcp arrays from.
 *
 *      void LCPArray(string str)
 *
 *      @param str          : String to create LCP array from
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
        suffixArray(str);
        LCPArray(str);
    }

    int32_t getSuffix(int32_t i){
        return suff[i];
    }

    int32_t getLRS(){
        return *std::max_element(lcp.begin(), lcp.end());
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
    void suffixArray(std::string& str){
        str += 0x1f;
        std::vector<int32_t> clas(str.size(), 0), count(std::max(ALPB, static_cast<int32_t>(str.size())), 0);
        suff.resize(str.size());
        cSort(count, suff, str);

        // Equivalence classes for cyclic substring of length 1
        int32_t cl{1};
        for (int32_t i{1}; i < str.size(); ++i) {
            if (str[suff[i]] != str[suff[i - 1]])
                ++cl;
            clas[suff[i]] = cl - 1;
        }

        std::vector<int32_t> ordern(str.size()), clasn(str.size());
        for (int32_t h{0}; (1 << h) < str.size(); ++h) {
            for (int32_t i{0}; i < str.size(); ++i) {
                ordern[i] = suff[i] - (1 << h);
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
                suff[--count[clas[ordern[i]]]] = ordern[i];
            // Equivalence classes
            clasn[suff[0]] = 0;
            cl = 1;
            for (int32_t i = 1; i < str.size(); i++) {
                auto cur = std::make_pair(clas[suff[i]], clas[(suff[i] + (1 << h)) % str.size()]);
                auto prev = std::make_pair(clas[suff[i - 1]], clas[(suff[i - 1] + (1 << h)) % str.size()]);
                if (cur != prev)
                    ++cl;
                clasn[suff[i]] = cl - 1;
            }
            clas.swap(clasn);
        }
        suff.erase(suff.begin());
    }

    /*
     * Create an LCP array given that a suffix array already exists, uses Kasai's algorithm.
     * It is clear that everything except the while loop runs in O(N) time. Since k is
     * decremeneted at most n times and can not grow larger than N the loop is executed
     * a total of O(N) times.
     */
    void LCPArray(std::string str){
        std::vector<int32_t> inverseSuf(str.size());
        lcp.resize(str.size());
        // Store position of suffix in the 'suf' array
        for(int32_t i{0}; i < str.size(); ++i){
            inverseSuf[suff[i]] = i;
        }

        int32_t k{0};

        for(int32_t i{0}; i < str.size(); ++i){
            if (inverseSuf[i] == str.size() - 1){
                k = 0;
                continue;
            }

            auto j = suff[inverseSuf[i] + 1];
            while(i + k < str.size() && j + k < str.size() && str[i+k] == str[j+k])
                ++k;

            lcp[inverseSuf[i]] = k;
            if(k)
                --k;
        }
    }

    std::vector<int32_t> suff;
    std::vector<int32_t> lcp;
    const int32_t ALPB{256};
};

int main(){
    std::string str;
    int32_t L;

    std::cin >> L;
    std::cin >> str;

    Suffix sa(str);

    std::cout << sa.getLRS() << "\n";

    return 0;
}