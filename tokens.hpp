#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <set>

const std::set<std::string> validFunctions = {
    "sin", "cos", "tan", "log", "log10", "exp", "sqrt",
    "asin", "acos", "atan", "sinh", "cosh", "tanh", "abs"
};

enum class TokenType {
    Number,
    Operator,
    Function,
    Parenthesis
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, const std::string& val) : type(type), value(val) {}
};

std::vector<Token> tokenize(const std::string& expr);

#endif
