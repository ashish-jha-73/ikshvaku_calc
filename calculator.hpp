#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>
#include <stack>
#include <vector>
#include "tokens.hpp"

typedef long double ld;
const ld PI = 3.14159265358979323846;
const ld E = 2.71828182845904523536;

class BasicCalculator {
public:
    ld add(ld x, ld y);
    ld subtract(ld x, ld y);
    ld multiply(ld x, ld y);
    ld divide(ld x, ld y);
};

class ScientificCalculator : public BasicCalculator {
public:
    // Exponential & Logarithmic
    ld log(ld x);           
    ld log10(ld x);         
    ld exp(ld x);           
    ld power(ld base, ld exponent);
    ld squareRoot(ld x);

    // Trigonometric (assume input in radians)
    ld sine(ld x);
    ld cosine(ld x);
    ld tangent(ld x);
    ld cotangent(ld x);
    ld secant(ld x);
    ld cosecant(ld x);

    // Inverse Trigonometric
    ld arcsin(ld x);
    ld arccos(ld x);
    ld arctan(ld x);

    // Hyperbolic functions
    ld sinh(ld x);
    ld cosh(ld x);
    ld tanh(ld x);

    // Misc
    ld factorial(int n);        
    ld absolute(ld x);
    ld modulus(ld a, ld b);
};

ld evaluatePostfix(const std::vector<Token>& postfix, ScientificCalculator& calc);
std::vector<Token> infixToPostfix(const std::vector<Token>& tokens);
void printHelp();

#endif
