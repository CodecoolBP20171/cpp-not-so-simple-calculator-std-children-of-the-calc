
#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOR_H

#include <iostream>
#include <vector>
#include <map>
#include "Operators.h"
#include "ExprElem.h"

typedef std::vector<ExprElem> expression;
typedef std::map <OperType, Operator> opMap;

class Calculator {
public:
    double evaluate(std::string expr);

private:
    std::string eliminateSpaces(std::string expr);
    expression parseExpr(std::string expr);
    bool isValidOperator(char oper);
    double calculateExpr(expression expr);
    void reduceExprWithOperators(expression expr, opMap operatorMap);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOR_H
