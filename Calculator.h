
#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOR_H

#include <iostream>
#include <vector>
#include <map>
#include <regex>
#include <string>
#include <cmath>
#include "Operators.h"
#include "ExprElem.h"
#include "CalculatorException.h"

const char SIGN_INDICATOR = 'z';

typedef std::vector<ExprElem> expression;
typedef std::map<OperType, Operator *> opMap;

class Calculator {
public:
    double evaluate(std::string expr);
    Calculator();
    virtual ~Calculator();

private:
    std::string validOperators;
    std::vector<opMap> opmaps;
    std::string prepareExpression(std::string expr);
    expression parseExpr(std::string expr);
    bool isValidOperator(char oper);
    double calculateExpr(expression expr);
    void reduceExprWithOperators(expression &expr, opMap operatorMap);
    std::string dealWithParentheses(std::string expr);
    void replaceParenthesesWithResult(std::string &expr, unsigned long openIndex, long i);
    long getMatchingParenIndex(std::string &expr, unsigned long openIndex);
    bool isOperatorAfterNum(unsigned int slowIndex, unsigned int i) const;
    bool isCharPartOfNum(char c) const;
    bool isNotSign(const std::string &expr, unsigned int i) const;
    double calculate(std::string expr);
    void handleErronousExpression(const std::string &expr, const CalculatorException &e) const;
    void printBaseMessage(const ErrorType &errorType) const;
};

#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOR_H
