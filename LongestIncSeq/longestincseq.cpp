//
// Created by Leon Ericsson on 2022-01-24.
//

#include <iostream>
#include <algorithm>
#include <vector>

/*
 * Given an array of random numbers this program finds the longest increasing subsequence in the array.
 * The program runs with O(N*log N) time complexity.
 * Usage:
 *      int32_t[] lis(Ele*[] seq)
 *
 *      @param seq      : Sequence of random numbers represented by Ele object.
 *      @return         : vector of item indices which represent the largest increasing
 *                        sequence.
 *
 */


struct Ele{
    int v{};
    int i{};
    Ele* prev{nullptr};
};

// Binary search algorithm, O(logN). Requires sorted input vector v.
uint32_t binary(std::vector<Ele*>& v, int32_t l, uint32_t r, int32_t key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m]->v >= key)
            r = m;
        else
            l = m;
    }

    return r;
}

/*
 * Calculated the longest increasing subsequence (LIS) by considering a vector of active
 * potential lists of increasing sequences. Iterating over the sequence, for each element we
 * have one of three options. The element is smallest among all end candidates of active lists,
 * the element is largest among all end candidates of active lists or the element is in between
 * the end element of two lists. Since we only consider the end elements of each active list we
 * don't need to store the contents of the entire active lists. Instead we hold an auxillary array
 * to keep just the end elements. Complexity for outer loop is O(N) and we run binary search inside
 * the loop meaning total O(N*Log N) time complexity.
 */
std::vector<int32_t> lis(std::vector<Ele>& seq){

    std::vector<Ele*> rear(seq.size());

    rear[0] = &seq[0];
    uint32_t size{1};

    // Iterate over sequence with size N: O(N)
    for(uint32_t i{1}; i < seq.size(); ++i){
        if(seq[i].v < rear[0]->v){
            rear[0] = &seq[i];
        }
        else if(seq[i].v > rear[size - 1]->v){
            seq[i].prev = rear[size-1];
            rear[size++] = &seq[i];
        }
        else if (seq[i].v > rear[0]->v && seq[i].v < rear[size-1]->v){
            auto index = binary(rear, -1, size - 1, seq[i].v);
            rear[index] = &seq[i];
            seq[i].prev = rear[index-1];
        }
    }

    std::vector<int32_t> result;
    auto cur{*rear[size-1]};
    while(true){
        result.push_back(cur.i);

        if(!cur.prev)
            break;
        else
            cur = *cur.prev;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

int main(){
    int32_t N, val;
    std::vector<Ele> seq;
    while(std::cin >> N){
        seq.clear();
        // Test case input gathering
        for(int32_t i{0}; i < N; ++i){
            std::cin >> val;
            seq.emplace_back(Ele{val,i});
        }

        // Solve test case
        auto result{lis(seq)};

        // Output result
        std::cout << result.size() << '\n';
        for(const auto ele : result){
            std::cout << ele << " ";
        }
        std::cout << '\n';
    }
};
