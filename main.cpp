#include "calculator.hpp"
#include "tokens.hpp"

int main() {
    
    std::cout << "Hello this calculator built by Ikshvaku to start click 's' or to abort click 'a' " << std::endl;
    char ch;
    std::cin >> ch;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (ch == 'a') {
        std::cout << "BYE comeback again !! " << std::endl;
    }
    else {
        std::cout << "Welcome to the era of Ikshvaku dynasty >> \nfor aborting in between write 'ABORT' for help write 'HELP'\nlet the journey begin !!" << std::endl;
        while (1) {
            std::cout << std::endl;
            std::cout << ">> ";
            std::string input;
            std::getline(std::cin, input);
            if (input == "ABORT") break;
            if (input == "HELP") {
                printHelp();
                continue;
            }

            std::vector<Token> tokens = tokenize(input);
            if (tokens.empty()) {
                std::cout << "Invalid expression.\n";
                return 0;
            }
            std::vector<Token> postfix = infixToPostfix(tokens);
            ScientificCalculator calc;
            ld result = evaluatePostfix(postfix, calc);
            std::cout << "Result: " << result << "\n";
        }
    }
    std::cout << "\n";

}