
#include "RPN.hpp"
#include <cctype>
#include <iostream>
#include <sstream>

RPN::RPN(void) {
    m_stack = std::stack<double, std::list<double> >();
}

RPN::RPN(const RPN &other) {
    m_stack = std::stack<double, std::list<double> >(other.m_stack);
}

RPN::~RPN(void) {
}

RPN &RPN::operator=(const RPN &other) {
    if (this != &other) {
        m_stack = other.m_stack;
    }

    return *this;
}

void RPN::calculateFormula(const std::string &formula) {
    if (!tryValidateFormula(formula)) {
        return;
    }
}

bool RPN::tryValidateFormula(const std::string &formula) const {
    if (formula.empty()) {
        printError("Invalid input");
        return false;
    }

    bool has_whitespace = false;
    unsigned int op_count = 0;
    unsigned int nb_count = 0;
    std::string::const_iterator it = formula.begin();

    for (it = formula.begin(); it != formula.end(); it++) {
        if (std::isspace(*it)) {
            has_whitespace = true;
            continue;
        }
        if (!has_whitespace) {
            printError(
                "Only single characters are accepted as formula variables");
            return false;
        }

        has_whitespace = false;
        if (isOperator(*it)) {
            op_count++;
        } else if (std::isdigit(*it)) {
            nb_count++;
        } else {
            printError("Invalid character in formula");
            return false;
        }
    }

    std::cout << "ops=" << op_count << " : nbrs=" << nb_count << std::endl;
    if (nb_count != op_count + 1) {
        printError("Invalid formula");
        return false;
    }

    return true;
}

bool RPN::isOperator(const char c) {
    switch (c) {
        case '*':
        case '/':
        case '+':
        case '-':
            return true;
        default:
            return false;
    }
}

void RPN::printError(const std::string &str) {
    std::cerr << "\033[31mError: " << str << "\033[0m" << std::endl;
}
