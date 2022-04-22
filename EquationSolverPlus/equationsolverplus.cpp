//
// Created by Leon Ericsson on 2022-02-08.
//

#include <vector>
#include <iostream>
#include <cmath>

/*
 * Given a system of n linear equations with m unkowns this program determines if
 * the system is either unsolvable, has multiple solution or has a unique solution.
 * If a unique solution exists then this solution is found and returned as a vector.
 * Gauss-Jordan elimination is the algorithm behind this solution and runs with
 * O(N^3) time complexity. The problem can be represented as a matrix, Ax = b.
 * Usage:
 *      double[] gaussElimination(Matrix& A,Vector& b, int16_t N)
 *
 *      @param A        : A two-dimensional vector of floating point numbers to represent the lhs matrix A.
 *      @param b        : Vector of floating point numbers representing the rhs vector b.
 *      @param N        : Size of the square matrix A
 *
 *      return          : Solution vector, empty if no solution exists or if there are multiple.
 */



using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

bool threshold(double x){
    return std::abs(x) < 0.00000001;
}

bool forwardElimination(Matrix& A, Vector& b){
    uint32_t step{0};
    for(uint64_t n{0}; n < A.size(); ++n){
        uint64_t pivot = n-step;
        double max = std::abs(A[n-step][n]);

        // Find the greatest value in current column
        for(uint64_t i{n+1-step}; i < A.size(); ++i){
            if(std::abs(A[i][n]) > max){
                max = std::abs(A[i][n]);
                pivot = i;
            }
        }

        // Pivot element is 0 means matrix is singular
        if(threshold(max)){
            step++;
            continue;
        }

        // Swap rows to get greatest pivot element
        if(pivot != n-step){
            std::iter_swap(A.begin() + n-step, A.begin() + pivot);
            std::iter_swap(b.begin() + n-step, b.begin() + pivot);
        }

        // Row operations to achieve upper triangular matrix, turns current
        // column below n into 0s.
        for(uint64_t i{n-step}; i < A.size()-1; ++i){
            double div{-A[i+1][n]/A[n-step][n]};
            for(uint64_t j{n}; j < A.size(); ++j){
                A[i+1][j] += A[n-step][j]*div;
            }
            b[i+1] += b[n-step]*div;
        }
    }
    return step;
}

std::vector<double> backwardSubstitution(Matrix& A, Vector& b, int16_t N){
    std::vector<double> solution(A.size());

    for(int32_t i{N-1}; i >= 0; --i){
        solution[i] = b[i];
        for(int32_t j{i+1}; j < A.size(); ++j){
            solution[i] -= A[i][j]*solution[j];
        }
        solution[i] /= A[i][i];
    }
    return solution;
}

/*
 * Determine if the function has multiple solutions or no solutions, runs with O(N^2)
 * time complexity.
 */
using namespace std;
vector<pair<double, bool>> multiple(vector<vector<double>>& matrix, vector<double>& b){
    vector<pair<double, bool>> res(matrix.size(), make_pair(0, false));

    //Time complexity: O(n^2)
    for (int i = int(matrix.size()-1); i >= 0; --i) {

        // Use non zeros to keep track if there are more than one value on a row that has a value, if then
        // those are undetermined
        int nonZeros{0};

        // Using firstindex to keep track of which variable potentially was determined
        int firstIndex{};
        for (int j = int(matrix.size()-1); j >= i; --j) {
            //Due to rounding errors, values will not be exactly zero
            if (abs(matrix[i][j]) > 0.00000001) {
                // If a value found save it in case it is the only one
                if (nonZeros == 0) {
                    double val = b[i] / matrix[i][j];
                    nonZeros++;
                    firstIndex = j;
                    res[j] = make_pair(val, true);
                    // If one more is found, make the first one invalid
                } else{
                    res[firstIndex].second = false;
                    nonZeros++;
                }
            }
            if (nonZeros>1)
                break;
        }
    }
    return res;
}

Vector multiple2(Matrix& A, Vector& b, int16_t N){
    Vector result(N);
    for(int32_t i{N-1}; i >= 0; --i){
        uint16_t cnt{0};
        for(int32_t j{N-1}; j >= i; --j){
            if(!threshold(A[i][j])){
                if(!cnt){

                    b[i] -= result[j]*A[i][j];
                    result[j] = b[i]/A[i][j];
                }
                cnt++;
            }
        }
        if(!threshold(b[i]) && !cnt)
            return Vector{};
        if(cnt>1)
            break;
    }
    return result;
}

/*
 * Gauss Jordan Elimination consists of two parts, first we elimnate elements in the matrix A
 * until we have an upper diagonal matrix and then we backpropogate a solution through the matrix.
 * Forward elimination runs with O(N^3) time complexity which can easily be seen as the three for-loops
 * iterate N = A.size() times. The backpropogation runs with O(N^2) time complexity.
 */
std::vector<double> gaussElimination(Matrix& A,Vector& b, int16_t N){
    // If we took a step during the forward propagation -> matrix is singular.
    if(forwardElimination(A, b)){
        auto res = multiple(A,b);
    }
    else{
        return backwardSubstitution(A, b, N);;
    }
}

int main(){
    int16_t N;
    while(std::cin >> N && N){
        // --- INPUT ---
        std::vector<std::vector<double>> A(N, std::vector<double>(N));
        for(int16_t i{0}; i < N; ++i){
            for(int16_t j{0}; j < N; ++j){
                std::cin >> A[i][j];
            }
        }
        std::vector<double> b(N);
        for(int16_t i{0}; i < N; ++i){
            std::cin >> b[i];
        }
        // --- SOLVER ---
        auto solution = gaussElimination(A, b, N);

        // --- OUTPUT ---
        if(solution.empty()){
            std::cout << "inconsistent";
        }
        else{
            for(const auto& ele : solution){
                if(ele == 0){
                    std::cout << "? ";
                }
                else{
                    std::cout << ele << " ";
                }
            }
        }
        std::cout << "\n";
    }
    return 0;
}