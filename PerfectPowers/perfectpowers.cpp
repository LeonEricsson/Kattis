

#include <vector>
#include <iostream>
#include <cmath>

int32_t perf(int64_t x, bool neg){
    int32_t p{1};
    int32_t best;
    double b;
    do{
        b = std::pow(x, 1.0/p);
        if(std::abs(std::round(b) - b) < 0.0001){
            if(std::pow(round(b), p) == x){
                b = round(b);
            }
        }
        if(neg){
            best = (std::floor(b) == b) && (p % 2 != 0) ? p : best;
        } else{
            best = std::floor(b) == b ? p : best;
        }
        p++;
    } while(b > 2);
    return best;
}

int main() {
    int64_t x;
    while (std::cin >> x && x) {
        std::cout << perf(std::abs(x), x < 1) << "\n";
    }
}