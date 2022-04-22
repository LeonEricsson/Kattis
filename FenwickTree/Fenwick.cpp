//
// Created by Leon Ericsson on 2022-01-26.
//


#include <iostream>
#include <algorithm>
#include <vector>

/*
 * A Fenwick Tree is also known as a Binary Index Tree is a data structure on an array which allows for
 * O(logN) updates and prefix sum queries. The implemented Fenwick tree has two operations which can be used.
 * update() and sum(). Both queries run in O(logN) time and the overlaying data structure uses O(N)
 * memory. Fenwick Tree is initialized with a size N.
 * Usage:
 *      void update(uint32_t& i, int64_t& v)
 *
 *      @param i        : Index i to be updated
 *      @param v        : Value to increase index i with.
 *
 *
 *      int64_t sum(uint32_t& i)
 *
 *      @param i        : Index to sum up to, but not including.
 *      return          : Total sum
 *
 */

struct Fenwick{
    explicit Fenwick(uint32_t N) : BITree(N){}


    /*
     * Indicates that a[i] is incremented by val where 0 <= i < N. This function starts at
     * index i+1 in the tree (due to BITree[0] being dummy node) and increments the start node
     * and all its decendents by val. Decendents are found by incrementing the last set bit of
     * current index.
     */
    void update(uint32_t& index, int64_t& val){
        index++;

        while(index <= BITree.size()){
            BITree[index] += val;
            index += (index & (-index));
        }
    }

    /*
     * Query will return a[0] + a[1] + ... a[i-1] where 0 <= i <= N. This is done by starting at index
     * i and for each step incrementing the total sum by BITree[index]. We move 'upwards' in the tree,
     * always moving to the current nodes parent by flipping the right most set bit in the binary of
     * the current index. This means we only need O(logN) steps to reach the root.
     */
    int64_t sum(uint32_t& index){
        int64_t result{0};

        while(index > 0){
            result += BITree[index];
            index -= (index & (-index));
        }
        return result;
    }

    std::vector<int64_t> BITree;
};



/*
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t N, Q;
    std::cin >> N >> Q;

    Fenwick fw(N+1);

    char op;
    uint32_t index;
    int64_t val;
    for(uint32_t i{0}; i < Q; ++i){
        std::cin >> op;
        if(op == '+'){
            std::cin >> index >> val;
            fw.update(index, val);
        } else {
            std::cin >> index;
            std::cout << fw.sum(index) << "\n";
        }
    }
}
*/
