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
bool multiple(Matrix& A, Vector& b, int16_t N){
    bool zeros{true};

    for(int32_t i{N-1}; i >= 0; --i){
        for(int32_t j{i}; j < N; ++j){
            if(!threshold(A[i][j])){
                zeros = false;
                break;
            }
        }
        if(!threshold(b[i]) && zeros){
            return false;
        }
        if(!zeros){
            break;
        }
    }
    return true;
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
        if(multiple(A,b,N)){
            std::cout << "multiple";
        } else {
            std::cout << "inconsistent";
        }
        return std::vector<double>{};
    }
    else{
        return backwardSubstitution(A, b, N);;
    }
}
/*

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
        for(const auto& ele : solution){
            std::cout << ele << " ";
        }
        std::cout << "\n";

    }
}*/
