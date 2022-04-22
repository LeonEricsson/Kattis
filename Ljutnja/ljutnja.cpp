//
// Created by Leon Ericsson on 2022-01-19.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

uint64_t give_candy(std::vector<uint64_t>& c, uint64_t& M, uint64_t& N){
    // Stop one before last child is evaluated.
    uint64_t anger;
    uint64_t i{0};
    for(; i < c.size() - 1; ++i){
        auto i_n{i+1};
        if(c[i] == c[i_n]){
            continue;
        }

        uint64_t step{};
        uint64_t diff{};
        while(c[i] != c[i_n]){

            // If we can't give every child one candy each at current level
            if(i_n >= M){
                anger = M*static_cast<uint64_t>(pow(c[i]-1,2)) + (i_n - M)*static_cast<uint64_t>(pow(c[i],2));
                for(uint64_t j{i+1}; j < c.size(); ++j){
                    anger += static_cast<uint64_t>(pow(c[j],2));
                }
                return anger;
            }


            step = M / (i+1);
            diff = c[i] - c[i_n];
            if(step >= diff){
                c[i] = c[i_n];
                M -= diff*(i+1);
            } else{
                c[i] -= step;
                M -= (i+1)*step;
            }
        }

    }

    while(M != 0 && c[i] != 0){
        if(N >= M){
            anger = M*static_cast<uint64_t>(pow(c[i]-1,2)) + (N-M)*static_cast<uint64_t>(pow(c[i],2));
            return anger;
        }
        c[i]--;
        M -= N;
    }

    return 0;
}


int main(){
    uint64_t N;
    uint64_t M;
    std::cin >> M >> N;

    std::vector<uint64_t> c;
    c.reserve(N);

    uint64_t read;
    for(int i{0}; i < N; ++i){
        std::cin >> read;
        c.emplace_back(read);
    }

    std::sort(c.begin(), c.end(), std::greater());

    auto result{give_candy(c, M, N)};

    std::cout << result << "\n";
}