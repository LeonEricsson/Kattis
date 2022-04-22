//
// Created by Leon Ericsson on 2022-01-27.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <tuple>

/*
 * Multiplication of polynomials with length N can trivially be done in O(n^2) time. This program
 * performs polynomial multiplication in O(N Log N) time by employing the Fast Fourier Transform (FFT) and
 * the Inverse FFT (IFFT). The main principle revolves around the fact that A * B = IFFT(FFT(A)*FFT(B)).
 * The API includes a function mul() which takes two coefficient vectors and performs the multiplication.
 * Usage:
 *      int32_t[] mul(int32_t[]& A, int32_t[]& B)
 *
 *      @param A        : First polynomial coefficient vector to multiply
 *      @param B        : Second polynomial coefficient vector to multiply
 *
 *      return          : Returns a vector of coefficient representing the product polynomial.
 *
 */


using Complex = std::complex<double>;

/*
 * Fast Fourier Transform algorithm established by Cooley-Turkey which runs in O(N LogN) time by
 * recursively splitting the coefficient vector and then piecing the result back toghether, divide
 * and conquer method.
 */
void fft(std::vector<Complex>& coef){
    int32_t n = coef.size();
    if(n <= 1)
        return;

    bool toggle{false};
    std::vector<Complex> even(n/2), odd(n/2);
    std::partition_copy(coef.begin(), coef.end(), even.begin(), odd.begin(), [&toggle](Complex){
        return toggle = !toggle;
    });

    fft(even);
    fft(odd);

    for(int32_t i{0}; i < n/2; ++i){
        Complex temp{std::polar(1.0, -2.0 * M_PI * i / n) * odd[i]};
        coef[i] = even[i] + temp;
        coef[i + n/2] = even[i] - temp;
    }
}

/*
 * Inverse FFT conjucated the coefficient vector before calling FFT and then reverses
 * the conj operation after FFT.
 */

void ifft(std::vector<Complex>& coef){
    std::transform(coef.cbegin(), coef.cend(), coef.begin(), [](const auto& c){
        return std::conj(c);
    });
    fft(coef);
    std::transform(coef.cbegin(), coef.cend(), coef.begin(), [](const auto& c){
        return std::conj(c);
    });
    double size = coef.size();
    std::transform(coef.cbegin(), coef.cend(), coef.begin(), [&size](const auto& c){
        return c / size;
    });
}

/*
 *   Multiplication of two polynomials from two vectors of coefficients. To begin we
 *   find new size N for the coefficient vectors, N needs to be power of 2, large enough
 *   to store the result of the product operation and same for both vectors. We can't calculate a
 *   pairwise product of the vector elements DFT(A)*DFT(B) if they are of different size. After that
 *   we perform the steps according to the IFFT(FFT(A)*FFT(B)) equation where the product of the two
 *   FFT means a pairwise product of the vector elements. The result is then cast back from complex
 *   to int and rounded.
*/

std::vector<int32_t> mul(std::vector<int32_t>& A, std::vector<int32_t>& B){
    int32_t n{1};
    std::vector<Complex> cA(A.begin(), A.end()), cB(B.begin(), B.end());
    while(n < A.size() + B.size())
        n <<= 1;

    cA.resize(n);
    cB.resize(n);

    fft(cA);
    fft(cB);
    std::transform(cA.cbegin(), cA.cend(), cB.cbegin(), cA.begin(), [](const auto& x, const auto& y){
        return x*y;
    });
    ifft(cA);

    std::vector<int32_t> result(A.size()+B.size()-1);
    for(int32_t i{0}; i < A.size()+B.size()-1; ++i){
        result[i] = (int)std::round(cA[i].real());
    }
    return result;
}

/*
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // --- INPUT ---
    std::vector<int32_t> c1;
    uint32_t deg1;
    std::cin >> deg1;
    c1.resize(++deg1);
    for(uint32_t i{0}; i < deg1; ++i){
        std::cin >> c1[i];
    }

    std::vector<int32_t> c2;
    uint32_t deg2;
    std::cin >> deg2;
    c2.resize(++deg2);
    for(uint32_t i{0}; i < deg2; ++i){
        std::cin >> c2[i];
    }

    // --- SOLVER ---
    auto solution = mul(c1, c2);

    // --- OUTPUT ---
    std::cout << deg1+deg2-2 << std::endl;
    for(const auto& ele : solution){
        std::cout << ele << " ";
    }
    std::cout << "\n";
}*/
