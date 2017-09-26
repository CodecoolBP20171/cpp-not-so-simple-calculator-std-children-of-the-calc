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

bool Calculator::isValidOperator(char oper) {
    const std::string validOperators = "+-*/";
    return validOperators.find(oper) >= 0;
}

expression Calculator::parseExpr(std::string expr) {
    expression parsedExpr;
    unsigned int slowIndex = 0;
    for (unsigned int i = 0; i < expr.size(); ++i) {
        if (!isdigit(expr[i]) && expr[i] != '.') {
            if (isValidOperator(expr[i])) {
                parsedExpr.emplace_back(ExprElem(std::stod(expr.substr(slowIndex, i - slowIndex))));
                slowIndex = i + 1;
                parsedExpr.emplace_back(ExprElem(OperType(expr[i])));
            } else {
                throw "Ejnye no! -->";
            }
        }
    }
    parsedExpr.emplace_back(ExprElem(std::stod(expr.substr(slowIndex))));

    return parsedExpr;
}

void Calculator::reduceExprWithOperators(expression &expr, opMap operatorMap) {
    int i = 1;
    while (i < expr.size()) {
        if (operatorMap.find(expr[i].getOperation()) != operatorMap.end()) {

            double tempResult;
            OperType actualOper = expr[i].getOperation();
            double firstValue = expr[i - 1].getValue();
            double secondValue = expr[i + 1].getValue();
            Operator *operObject = operatorMap[actualOper];
            tempResult = operObject->doOperation(firstValue, secondValue);

            expr.erase(expr.begin() + i - 1, expr.begin() + i + 2);
            expr.emplace(expr.begin() + i - 1, ExprElem(tempResult));
        } else i += 2;
    }
}

double Calculator::calculateExpr(expression expr) {
    opMap operatorMap({{multiply, new Multiply()},
                       {divide,   new Divide()}});
    reduceExprWithOperators(expr, operatorMap);

    operatorMap = opMap ({{add, new Add()},
                       {substract, new Substract()}});
    reduceExprWithOperators(expr, operatorMap);
    return expr[0].getValue();
}

double Calculator::evaluate(std::string expr) {
    expr = eliminateSpaces(expr);
    expression parsedExpr;

    try {
        parsedExpr = parseExpr(expr);
    }
    catch (std::string e) {
        return 0;
    };

    return calculateExpr(parsedExpr);
}