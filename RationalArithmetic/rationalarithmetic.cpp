//
// Created by Leon Ericsson on 2022-04-17.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
/*
 * Implementation of a Rational class that handles arithmetic and streaming operators for rational numbers
 * described as a fraction. The following operators are available: +, -, /, *, <, >, <=, >=, ==, !=, <<, >>.
 * Usage:
 *      Rational(int x, int y)
 *
 *      @param x      : Numerator
 *      @param text   : Denominator
 *
 */

class Rational{
public:
    Rational() : num{}, den{} {}
    Rational(int64_t x, int64_t y){
        auto gcd = std::gcd(x, y); // x0 = x1 = 0 -> gdc = 0
        if(!gcd)
            gcd = 1;
        num = x / gcd;
        den = std::abs(y / gcd);
        if(y < 0){
            num = -num;
        }
    }

    Rational operator+(const Rational& other) const{
        auto d = den*other.den;
        return {num*other.den + other.num * den, d};
    }

    Rational operator-(const Rational& other) const{
        auto d = den*other.den;
        return {num*other.den - other.num * den, d};
    }

    Rational operator/(const Rational& other) const{
        return {num * other.den,den*other.num};
    }

    Rational operator*(const Rational& other) const{
        return {num*other.num, den*other.den};
    }

    bool operator<(const Rational& other) const{

        return (double)num/den < (double)other.num/other.den;
    }

    bool operator>(const Rational& other) const{
        return (double)num/den > (double)other.num/other.den;
    }

    bool operator<=(const Rational& other) const{
        return (double)num/den <= (double)other.num/other.den;
    }

    bool operator>=(const Rational& other) const{
        return (double)num/den >= (double)other.num/other.den;
    }

    bool operator==(const Rational& other) const{
        return num == other.num && den == other.den;
    }

    bool operator!=(const Rational& other) const{
        return !(*this == other);
    }

    int64_t num;
    int64_t den;
};

std::ostream& operator<<(std::ostream& os, const Rational& rt){
    std::cout << rt.num << " / " << rt.den;
    return os;
}

std::istream& operator>>(std::istream& is, Rational& rt){
    is >> rt.num >> rt.den;
    return is;
}


int main(){
    int32_t n,x1,x2,y1,y2;
    char op;
    std::cin >> n;

    while(n--){
        std::cin >> x1 >> y1 >> op >> x2 >> y2;
        Rational a{x1, y1};
        Rational b{x2, y2};
        Rational res;
        switch(op){
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '/':
                res = a / b;
                break;
            case '*':
                res = a * b;
                break;
            default:
                break;
        }
        std::cout << res << "\n";
    }
    return 0;
}

