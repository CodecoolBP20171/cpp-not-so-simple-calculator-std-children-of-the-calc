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
    unsigned int slowIndex = 0;
    for (unsigned int i = 0; i < expr.size(); ++i) {
        if ( !isdigit(expr[i]) && expr[i] !='.'){
            if (isValidOperator(expr[i])) {
                parsedExpr.emplace_back( ExprElem( std::stod( expr.substr(slowIndex, i-slowIndex))));
                slowIndex = i+1;
                parsedExpr.emplace_back( ExprElem(OperType(expr[i])));
            } else {
                throw "Ejnye no! -->";
            }
        }
    }
    parsedExpr.emplace_back( ExprElem( std::stod( expr.substr(slowIndex))));
    return std::vector<ExprElem>();
}

double Calculator::calculateExpr(std::vector<ExprElem>) {
    return 0;
}

double Calculator::evaluate(std::string expr) {
    expr = eliminateSpaces(expr);
    //NEED TO HANDLE: not valid expr. eg: 5**3, 5.5.2+4
    std::vector<ExprElem> parsedExpr;

    try {
        parsedExpr = parseExpr(expr);
    }
    catch (std::string e){
        std::cout << e << expr << std::endl;
    };

    double result = calculateExpr(parsedExpr);

    return 0;
}