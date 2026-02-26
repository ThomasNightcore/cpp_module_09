
#include "RPN.hpp"
#include <cctype>
#include <iostream>
#include <stack>

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

bool RPN::tryUseOperator(const char &op) {
    if (m_stack.size() < 2) {
        m_stack.pop();
        printError("Invalid formula");
        return false;
    }

    double b = m_stack.top();
    m_stack.pop();
    double a = m_stack.top();
    m_stack.pop();
    double res;

    switch (op) {
        case '*': {
            res = a * b;
            break;
        }
        case '/': {
            if (b == 0) {
                m_stack = std::stack<double, std::list<double> >();
                printError("Division by zero");
                return false;
            }
            res = a / b;
            break;
        }
        case '+': {
            res = a + b;
            break;
        }
        case '-': {
            res = a - b;
            break;
        }
        default: {
            printError("Invalid character found");
            return false;
        }
    }

    m_stack.push(res);
    return true;
}

void RPN::calculateFormula(const std::string &formula) {
    bool has_whitespace = true;
    std::string::const_iterator it = formula.begin();

    for (; it != formula.end(); it++) {
        if (std::isspace(*it)) {
            has_whitespace = true;
            continue;
        }
        if (!has_whitespace) {
            printError("Only single characters are accepted as formula "
                       "variables/operators");
            return;
        }

        if (std::isdigit(*it)) {
            m_stack.push(*it - '0');
        } else if (!tryUseOperator(*it)) {
            return;
        }
    }
    if (m_stack.size() != 1) {
        m_stack = std::stack<double, std::list<double> >();
        printError("Invalid formula");
        return;
    }

    std::cout << m_stack.top() << std::endl;
    m_stack.pop();
}

void RPN::printError(const std::string &str) {
    std::cerr << "\033[31mError: " << str << "\033[0m" << std::endl;
}
