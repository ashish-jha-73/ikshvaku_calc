#include "tokens.hpp"

std::vector<Token> tokenize(const std::string& expr) {
    std::vector<Token> tokens;
    std::string numberBuffer;
    std::string funcBuffer;

    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        if (std::isspace(ch)) continue;

        // Building a number
        if (std::isdigit(ch) || ch == '.') {
            if (!funcBuffer.empty()) {
                std::cerr << "❌ Invalid function name: " << funcBuffer << "\n";
                return {};
            }
            numberBuffer += ch;
            continue;
        }

        // Building a function
        if (std::isalpha(ch)) {
            if (!numberBuffer.empty()) {
                tokens.emplace_back(TokenType::Number, numberBuffer);
                numberBuffer.clear();
            }
            funcBuffer += ch;
            continue;
        }

        // Flush function if done and current char is NOT a letter
        if (!funcBuffer.empty()) {
            if (validFunctions.find(funcBuffer) != validFunctions.end()) {
                tokens.emplace_back(TokenType::Function, funcBuffer);
            } else {
                std::cerr << "❌ Invalid function name: " << funcBuffer << "\n";
                return {};
            }
            funcBuffer.clear();
        }

        // Flush number if needed
        if (!numberBuffer.empty()) {
            tokens.emplace_back(TokenType::Number, numberBuffer);
            numberBuffer.clear();
        }

        // Handle operators
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '!') {
            tokens.emplace_back(TokenType::Operator, std::string(1, ch));
        }
        // Handle parentheses
        else if (ch == '(' || ch == ')') {
            tokens.emplace_back(TokenType::Parenthesis, std::string(1, ch));
        }
        // Invalid character
        else {
            std::cerr << "❌ Invalid character in expression: '" << ch << "'\n";
            return {};
        }
    }

    // Final flush
    if (!funcBuffer.empty()) {
        if (validFunctions.find(funcBuffer) != validFunctions.end()) {
            tokens.emplace_back(TokenType::Function, funcBuffer);
        } else {
            std::cerr << "❌ Invalid function name: " << funcBuffer << "\n";
            return {};
        }
    }
    if (!numberBuffer.empty()) {
        tokens.emplace_back(TokenType::Number, numberBuffer);
    }

    return tokens;
}

