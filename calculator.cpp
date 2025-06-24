#include "calculator.hpp"
#include "tokens.hpp"


// ---------- BasicCalculator ----------

ld BasicCalculator::add(ld x, ld y) {
    return x + y;
}

ld BasicCalculator::subtract(ld x, ld y) {
    return x - y;
}

ld BasicCalculator::multiply(ld x, ld y) {
    return x * y;
}

ld BasicCalculator::divide(ld x, ld y) {
    if (y == 0) {
        std::cout << "Division by zero" << std::endl;
        return INFINITY;
    }
    return x / y;
}

// ---------- ScientificCalculator ----------

ld ScientificCalculator::log(ld x) {
    if (std::abs(x) <= 1e-6) {
        std::cout << "Invalid value inside log" << std::endl;
        return -1 * INFINITY;
    }
    return log2(x) / log2(E);
}

ld ScientificCalculator::log10(ld x) {
    if (x <= 0) {
        std::cout << "Invalid value inside log10" << std::endl;
        return -1 * INFINITY;
    }
    return std::log10(x);
}

ld ScientificCalculator::exp(ld x) {
    return std::exp(x);
}

ld ScientificCalculator::power(ld base, ld exponent) {
    return std::pow(base, exponent);
}

ld ScientificCalculator::squareRoot(ld x) {
    if (x < 0) {
        std::cout << "Square root of negative number" << std::endl;
        return -1 * INFINITY;
    }
    return std::sqrt(x);
}

// Trigonometric
ld ScientificCalculator::sine(ld x) {
    return std::sin(x);
}

ld ScientificCalculator::cosine(ld x) {
    return std::cos(x);
}

ld ScientificCalculator::tangent(ld x) {
    return std::tan(x);
}

ld ScientificCalculator::cotangent(ld x) {
    return 1.0 / std::tan(x);
}

ld ScientificCalculator::secant(ld x) {
    return 1.0 / std::cos(x);
}

ld ScientificCalculator::cosecant(ld x) {
    return 1.0 / std::sin(x);
}

// Inverse Trigonometric
ld ScientificCalculator::arcsin(ld x) {
    return std::asin(x);
}

ld ScientificCalculator::arccos(ld x) {
    return std::acos(x);
}

ld ScientificCalculator::arctan(ld x) {
    return std::atan(x);
}

// Hyperbolic
ld ScientificCalculator::sinh(ld x) {
    return std::sinh(x);
}

ld ScientificCalculator::cosh(ld x) {
    return std::cosh(x);
}

ld ScientificCalculator::tanh(ld x) {
    return std::tanh(x);
}

// Miscellaneous
ld ScientificCalculator::factorial(int n) {
    if (n < 0) {
        std::cout << "Factorial of negative number" << std::endl;
        return -1;
    }
    ld result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

ld ScientificCalculator::absolute(ld x) {
    return std::abs(x);
}

ld ScientificCalculator::modulus(ld a, ld b) {
    if (b == 0) {
        std::cout << "Modulus by zero" << std::endl;
        return INFINITY;
    }
    return std::fmod(a, b);
}

int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

bool isRightAssociative(const std::string& op) {
    return op == "^"; 
}

std::vector<Token> infixToPostfix(const std::vector<Token>& tokens) {
    std::vector<Token> output;
    std::vector<Token> opStack;

    for (const Token& token : tokens) {
        if (token.type == TokenType::Number) {
            output.push_back(token);
        }
        else if (token.type == TokenType::Function) {
            opStack.push_back(token);
        }
        else if (token.type == TokenType::Operator) {
            while (!opStack.empty()) {
                Token top = opStack.back();
                if (
                    (top.type == TokenType::Operator &&
                        (precedence(top.value) > precedence(token.value) ||
                         (precedence(top.value) == precedence(token.value) && !isRightAssociative(token.value))))
                    || top.type == TokenType::Function
                ) {
                    output.push_back(top);
                    opStack.pop_back();
                } else break;
            }
            opStack.push_back(token);
        }
        else if (token.value == "(") {
            opStack.push_back(token);
        }
        else if (token.value == ")") {
            while (!opStack.empty() && opStack.back().value != "(") {
                output.push_back(opStack.back());
                opStack.pop_back();
            }
            if (!opStack.empty() && opStack.back().value == "(")
                opStack.pop_back();  // Pop the '('
            if (!opStack.empty() && opStack.back().type == TokenType::Function) {
                output.push_back(opStack.back());
                opStack.pop_back();  // Pop the function
            }
        }
    }

    while (!opStack.empty()) {
        if (opStack.back().value == "(" || opStack.back().value == ")") {
            std::cerr << "❌ Mismatched parentheses.\n";
            return {};
        }
        output.push_back(opStack.back());
        opStack.pop_back();
    }

    return output;
}

ld evaluatePostfix(const std::vector<Token>& postfix, ScientificCalculator& calc) {
    std::stack<ld> stk;

    for (const auto& token : postfix) {
        if (token.type == TokenType::Number) {
            stk.push(std::stold(token.value));
        }
        else if (token.type == TokenType::Operator) {
            if (stk.size() < 2) {
                std::cerr << "❌ Not enough operands for operator " << token.value << "\n";
                return INFINITY;
            }

            ld b = stk.top(); stk.pop();
            ld a = stk.top(); stk.pop();
            ld res = 0;

            if (token.value == "+") res = calc.add(a, b);
            else if (token.value == "-") res = calc.subtract(a, b);
            else if (token.value == "*") res = calc.multiply(a, b);
            else if (token.value == "/") res = calc.divide(a, b);
            else if (token.value == "^") res = calc.power(a, b);
            else {
                std::cerr << "❌ Unknown operator: " << token.value << "\n";
                return INFINITY;
            }

            stk.push(res);
        }
        else if (token.type == TokenType::Function) {
            if (stk.empty()) {
                std::cerr << "❌ Not enough operands for function " << token.value << "\n";
                return INFINITY;
            }

            ld x = stk.top(); stk.pop();
            ld res = 0;

            if (token.value == "sin") res = calc.sine(x);
            else if (token.value == "cos") res = calc.cosine(x);
            else if (token.value == "tan") res = calc.tangent(x);
            else if (token.value == "cot") res = calc.cotangent(x);
            else if (token.value == "sec") res = calc.secant(x);
            else if (token.value == "cosec") res = calc.cosecant(x);
            else if (token.value == "log") res = calc.log(x);
            else if (token.value == "log10") res = calc.log10(x);
            else if (token.value == "sqrt") res = calc.squareRoot(x);
            else if (token.value == "exp") res = calc.exp(x);
            else if (token.value == "abs") res = calc.absolute(x);
            else if (token.value == "asin") res = calc.arcsin(x);
            else if (token.value == "acos") res = calc.arccos(x);
            else if (token.value == "atan") res = calc.arctan(x);
            else if (token.value == "sinh") res = calc.sinh(x);
            else if (token.value == "cosh") res = calc.cosh(x);
            else if (token.value == "tanh") res = calc.tanh(x);
            else {
                std::cerr << "❌ Unknown function: " << token.value << "\n";
                return INFINITY;
            }

            stk.push(res);
        }
    }

    if (stk.size() != 1) {
        std::cerr << "❌ Invalid postfix expression\n";
        return INFINITY;
    }

    return stk.top();
}


void printHelp() {
    std::cout << "\n===== 📘 IKSHVAKU CALCULATOR HELP MENU =====\n";
    std::cout << "Operators:\n";
    std::cout << "  +   Addition\n";
    std::cout << "  -   Subtraction\n";
    std::cout << "  *   Multiplication\n";
    std::cout << "  /   Division\n";
    std::cout << "  ^   Exponentiation\n";
    std::cout << "\nScientific Functions (use parentheses):\n";
    std::cout << "  log(x)     : Natural logarithm (base e)\n";
    std::cout << "  log10(x)   : Base-10 logarithm\n";
    std::cout << "  exp(x)     : Exponential function e^x\n";
    std::cout << "  sqrt(x)    : Square root\n";
    std::cout << "\nTrigonometric (in radians):\n";
    std::cout << "  sin(x), cos(x), tan(x)\n";
    std::cout << "  cot(x), sec(x), csc(x)\n";
    std::cout << "\nInverse Trigonometric:\n";
    std::cout << "  asin(x), acos(x), atan(x)\n";
    std::cout << "\nHyperbolic:\n";
    std::cout << "  sinh(x), cosh(x), tanh(x)\n";
    std::cout << "\nMiscellaneous:\n";
    std::cout << "  abs(x)       : Absolute value\n";
    std::cout << "  mod(a, b)    : a % b (modulus)\n";
    std::cout << "  fact(n)      : Factorial (integer n)\n";
    std::cout << "\nOther Commands:\n";
    std::cout << "  HELP         : Show this menu\n";
    std::cout << "  ABORT        : Exit the calculator\n";
    std::cout << "============================================\n\n";
}
