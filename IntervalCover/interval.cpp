//
// Created by Leon Ericsson on 2022-01-20.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <ostream>

/*
 * Program which handles the problem of covering a provided interval using a minimal set of another range of
 * provided intervals. Program runs with O(N*logN) time and O(n) memory complexity. API is supplied in form of the
 * cover() function.
 * Usage:
 *      int[] cover(Interval i, Interval[] v)
 *
 *      @param i    : Primary interval which you want covered
 *      @param v    : Available intervals to use for finding minimal coverage
 *      @return     : vector of minimal coverage interval indices, -1 if
 *                    coverage is not possible.
 *
 */


struct Interval{
    double A;
    double B;
    int index;

    bool operator < (const Interval& other) const {
        return A < other.A;
    }
};

/*
 * Calculates the minimal set of intervals which cover the primary interval. Greedy approach
 * which assumes that the optimal interval choice to cover a range (A,B) is one with start point
 * P <= A and end point is maximum possible.
 */
std::vector<int> cover(Interval primary, std::vector<Interval> intervals){
    std::vector<int> result;
    // O(N*logN) time complexity
    sort(intervals.begin(), intervals.end());

    double start{primary.A};
    double end{start-1};
    int count{0};
    // O(N) time complexity
    for(int i{0}; i < intervals.size();){
        if(intervals[i].A <= start){
            auto max{std::max(end, intervals[i].B)};
            if(max != end){
                if(result.empty() || result.size() <= count){
                    result.push_back(intervals[i].index);
                } else{
                    result[count] = intervals[i].index;
                }
            }
            i++;
            end = max;

        } else{
            start = end;
            count++;

            if(intervals[i].A > end || end >= primary.B ){
                break;
            }
        }

    }

    if(end < primary.B){
        return std::vector<int>{-1};
    }

    return result;
}



/*
int main(){
    double A, B;
    int N;
    while(std::cin >> A >> B >> N){
        std::vector<Interval> intervals;
        intervals.reserve(N);
        Interval primary{A, B};

        // O(N) time and memory complexity
        for(int j{0}; j < N; ++j){
            Interval temp{};
            std::cin >> temp.A >> temp.B;
            temp.index = j;
            intervals.emplace_back(temp);
        }
        auto result{cover(primary,  intervals)};

        if(result[0] == -1){
            std::cout << "impossible" << "\n";
            continue;
        }

        std::cout << result.size() << "\n";
        for(int j{0}; j < result.size(); ++j){
            std::cout << result[j];

            if(j != result.size() - 1){
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    return 0;
};
*/
