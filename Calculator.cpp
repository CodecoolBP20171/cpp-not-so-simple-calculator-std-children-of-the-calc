#include "Calculator.h"


std::string Calculator::eliminateSpaces(std::string expr) {
    std::string newExpr;
    for (char c: expr) {
        if (!isspace(c)) {
            newExpr += c;
        }
    }
    return newExpr;
}

bool Calculator::isValidOperator(char oper){
    const std::string validOperators= "+-*/";
    return validOperators.find(oper)>=0;
}

std::vector<ExprElem> Calculator::parseExpr(std::string expr) {
    std::vector<ExprElem> parsedExpr;
    int slowIndex = 0;
    for (int i = 0; i < expr.size(); ++i) {
        if ( !isdigit(expr[i]) && expr[i] !='.'){
            if (isValidOperator(expr[i])) {
                parsedExpr.push_back( ExprElem( std::stod( expr.substr(slowIndex, i-slowIndex))));
                slowIndex = i+1;
                parsedExpr.push_back( ExprElem(OperType(expr[i])));
            } else {
                throw "Ejnye no! -->" + expr;
            }
        }
    }
    parsedExpr.push_back( ExprElem( std::stod( expr.substr(slowIndex))));
    return std::vector<ExprElem>();
}

double Calculator::evaluate(std::string expr) {
    expr = eliminateSpaces(expr);
    //NEED TO HANDLE: not valid expr. eg: 5**3, 5.5.2+4
    std::vector<ExprElem> parsedExpr = parseExpr(expr);

    return 0;
}