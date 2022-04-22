//
// Created by Leon Ericsson on 2022-02-14.
//
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using Matrix = std::vector<std::vector<uint16_t>>;
using Vector = std::vector<uint16_t>;

static const Matrix onebit{
        {1,2,4},
        {0,3,5},
        {0,3,6},
        {1,2,7},
        {0,5,6},
        {1,4,7},
        {2,4,7},
        {3,5,6}
};

static const std::vector<std::string> votes{
    "NNN",
    "NNY",
    "NYN",
    "NYY",
    "YNN",
    "YNY",
    "YYN",
    "YYY"
};

// Find the highest preference move for a specific priest.
uint16_t preference(Vector& priest, const Vector& changes){
    uint16_t optimal{10};
    uint16_t index{0};
    for(const auto& ele : changes){
        if(priest[ele] < optimal){
            optimal = priest[ele];
            index = ele;
        }
    }
    return index;
}

void tabulation(Matrix& DP, Matrix& priests, uint16_t M){
    // Generate the last DP row seperately
    for(uint16_t i{0}; i < 8; ++i){
        DP[M-1][i] = preference(priests[M-1], onebit[i]);
    }

    /*
     * Iterate backwards and propagate the DP matrix depending on
     * the previous rows optimal choice. Each row represents a priest.
     */
    for(int32_t p{M-2}; p >= 0; --p){
        for(uint16_t i{0}; i < 8; ++i){
            Vector c(3);
            std::generate(c.begin(), c.end(), [j=0, &DP, &p, &i] () mutable {
                return DP[p+1][onebit[i][j++]];
            });
            DP[p][i] = preference(priests[p], c);
        }
    }
}

int main(){
    uint16_t N, M;
    std::cin >> N;
    for(uint16_t i{0}; i < N; ++i){
        std::cin >> M;
        Matrix priests(M, Vector(8));
        Matrix DP(M, Vector(8));
        for(uint16_t j{0}; j < M; ++j){
            for(uint16_t k{0}; k < 8; ++k){
                std::cin >> priests[j][k];
            }
        }
        tabulation(DP, priests, M);
        std::cout << votes[DP[0][0]] << std::endl;
    }

}