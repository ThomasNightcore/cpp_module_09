#ifndef __RPN_HPP__
#define __RPN_HPP__

#include <list>
#include <stack>
#include <string>

class RPN {
private:
    std::stack<double, std::list<double> > m_stack;

    bool tryValidateFormula(const std::string &formula) const;
    bool tryUseOperator(const char &op);

    static bool isOperator(const char c);
    static void printError(const std::string &str);

public:
    RPN(void);
    RPN(const RPN &other);
    ~RPN(void);
    RPN &operator=(const RPN &other);

    void calculateFormula(const std::string &formula);
};

#endif
