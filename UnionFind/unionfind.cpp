//
// Created by Leon Ericsson on 2022-01-25.
//

#include <algorithm>
#include <vector>
/*
 * Union finder which supplies three functions: find_parent(), same() and union_set(). Allowing
 * a user to combine any two sets, find what set a specific element is in and find if two elements
 * are apart off the same set. Program runs with amortized O(logN) time complexity and O(N) memory
 * complexity.
 * Usage:
 *      uint32_t find_parent(uint32_t a, uint32_t[] p)
 *
 *      @param a    : element to find parent for
 *      @param p    : vector of direct ancestors, ancestor of element i is p[i].
 *      @return     : parent integer.
 *
 *      void union_sets(uint32_t a, uint32_t b, uint32_t[] p, uint32_t[] s)
 *
 *      @param a    : first set element to union
 *      @param b    : second set element to union
 *      @param p    : vector of direct ancestors
 *      @param s    : vector of tree sizes for each element
 *
 *      bool same(uint32_t a, uint32_t b, uint32_t p)
 *
 *      @param a    : first set element to check with
 *      @param b    : second set element to check with
 *      @param p    : vector of direct ancestors
 *      @return     : true if elements are apart off the same set, false otherwise.
 */


/*
 * Recursively searches parents vector for the parent to initial element 'a'. While
 * searching recursively also refactors the set tree such that each tree element passed
 * through is moved to be a direct descendent of the root. This solution avoids trees
 * degenerating into long chains where each call would take O(N) time. Instead we guarantee
 * amortized O(logN).
 */
uint32_t find_parent(uint32_t a, std::vector<uint32_t>& parents){
    if(a == parents[a]){
        return a;
    }
    return parents[a] = find_parent(parents[a], parents);
}

/*
 * Creates a union from the sets that a and b belong too. To guarantee
 * O(logN) we always attatch the tree with the smaller size to the one
 * with larger size thus avoiding trees containing long chains of length
 * O(N).
 */
void union_sets(uint32_t a, uint32_t b, std::vector<uint32_t>& parents, std::vector<uint32_t>& size){
    auto p_a = find_parent(a, parents);
    auto p_b = find_parent(b, parents);

    if(p_a != p_b){
        if(size[p_a] > size[p_b]){
            parents[p_b] = p_a;
            size[p_a] += size[p_b];
        }
        else{
            parents[p_a] = p_b;
            size[p_b] += size[p_a];
        }
    }
}

bool same(uint32_t a, uint32_t b, std::vector<uint32_t>& parents){
    return find_parent(a, parents) == find_parent(b, parents);
}


/*
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t N, Q;
    std::cin >> N >> Q;

    std::vector<uint32_t> parents(N);
    std::vector<uint32_t> size(N, 1);
    std::iota(parents.begin(), parents.end(), 0);

    char op;
    uint32_t a,b;
    for(uint32_t i{0}; i < Q; ++i){
        std::cin >> op >> a >> b;
        if(op == '='){
            union_sets(a,b, parents, size);
        } else {
            auto output = same(a,b,parents) ? "yes" : "no";
            std::cout << output << "\n";
        }

    }
}*/
