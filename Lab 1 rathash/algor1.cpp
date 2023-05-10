#include <iostream>
#include <unordered_map>
#include <numeric>

struct Rational {
    int numerator;
    int denominator;
};


int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void normalize(Rational& r) {
    int g = gcd(r.numerator, r.denominator);
    r.numerator /= g;
    r.denominator /= g;
    if (r.denominator < 0) {
        r.numerator *= -1;
        r.denominator *= -1;
    }
}


struct RationalHash {
    std::size_t operator()(const Rational& r) const {
        return std::hash<int>()(r.numerator) ^ std::hash<int>()(r.denominator);
    }
};


struct RationalEqual {
    bool operator()(const Rational& r1, const Rational& r2) const {
        return r1.numerator == r2.numerator && r1.denominator == r2.denominator;
    }
};

int main() {
    std::unordered_map<Rational, int, RationalHash, RationalEqual> rational_map;

    Rational r1{ 2, 4 };
    Rational r2{ 1, 2 };
    normalize(r1);
    normalize(r2);

    rational_map[r1] = 1;
    rational_map[r2] = 2;

    std::cout << "Rational numbers in map:" << std::endl;
    for (const auto& entry : rational_map) {
        std::cout << entry.first.numerator << "/" << entry.first.denominator << " => " << entry.second << std::endl;
    }

    return 0;
}