#include "Calculator.h"

Calculator::Calculator() {
    validOperators = "+-/*r^";
    validOperators += SIGN_INDICATOR;
}

std::string Calculator::prepareExpression(std::string expr) {
    expr = std::regex_replace(expr, std::regex("root"), "r");
    std::string newExpr;
    for (char c: expr) {
        if (!isspace(c) && c != SIGN_INDICATOR) {
            newExpr += c;
        }
    }
    return newExpr;
}

bool Calculator::isValidOperator(char oper) {
    return validOperators.find(oper) != std::string::npos;
}

std::string Calculator::dealWithParentheses(std::string expr) {
    unsigned long openIndex = expr.find('(');
    while (openIndex != std::string::npos) {
        long i = getMatchingParenIndex(expr, openIndex);
        replaceParenthesesWithResult(expr, openIndex, i);
        openIndex = expr.find('(');
    }
    return expr;
}

long Calculator::getMatchingParenIndex(std::string &expr, unsigned long openIndex) {
    int parentCount = 1;
    long i = openIndex + 1;
    while (parentCount > 0 && i < expr.size()) {
        if (expr[i] == '(') ++parentCount;
        if (expr[i] == ')') --parentCount;
        ++i;
    }
    if (parentCount != 0) throw "Missing closing parentheses";
    return i;
}

void Calculator::replaceParenthesesWithResult(std::string &expr, unsigned long openIndex, long i) {
    double result = evaluate(expr.substr(openIndex + 1, i - openIndex - 2));
    if (result < 0)
        expr.replace(openIndex, i - openIndex, SIGN_INDICATOR + std::to_string(result).substr(1));
    else
        expr.replace(openIndex, i - openIndex, std::to_string(result));
}

expression Calculator::parseExpr(std::string expr) {
    expr = dealWithParentheses(expr);
    expression parsedExpr;
    unsigned int slowIndex = 0;
    int sign = 1;
    for (unsigned int i = 0; i < expr.size(); ++i) {
        if (!isCharPartOfNum(expr[i])) {
            if (isValidOperator(expr[i])) {
                if (isOperatorAfterNum(slowIndex, i)) {
                    parsedExpr.emplace_back(ExprElem(sign * std::stod(expr.substr(slowIndex, i - slowIndex))));
                    slowIndex = i + 1;
                    sign = 1;
                    parsedExpr.emplace_back(ExprElem(OperType(expr[i])));
                } else if (expr[i] == SIGN_INDICATOR) {
                    slowIndex++;
                    sign = -1;
                } else if (isNotSign(expr, i)) {
                    throw "Invalid expression, missing operand";
                }
            } else {
                throw "Invalid expression, probably misspelling, missing parentheses";
            }
        }
    }
    parsedExpr.emplace_back(ExprElem(sign * std::stod(expr.substr(slowIndex))));

    return parsedExpr;
}

bool Calculator::isNotSign(const std::string &expr, unsigned int i) const { return expr[i] != '-' || i != 0; }

bool Calculator::isCharPartOfNum(char c) const { return isdigit(c) || c == '.'; }

bool Calculator::isOperatorAfterNum(unsigned int slowIndex, unsigned int i) const { return i - slowIndex > 0; }

void Calculator::reduceExprWithOperators(expression &expr, opMap operatorMap) {
    int i = 1;
    while (i < expr.size()) {
        OperType actualOper = expr[i].getOperation();
        if (operatorMap.find(actualOper) != operatorMap.end()) {

            //calculating the partial result around operator
            double firstValue = expr[i - 1].getValue();
            double secondValue = expr[i + 1].getValue();
            Operator *operObject = operatorMap[actualOper];
            double tempResult = operObject->doOperation(firstValue, secondValue);

            //replacing operator and its operands to the partial result
            expr.erase(expr.begin() + i - 1, expr.begin() + i + 2);
            expr.emplace(expr.begin() + i - 1, ExprElem(tempResult));
        } else i += 2;
    }
}

double Calculator::calculateExpr(expression expr) {

    opMap operatorMap({{power, new Power()},
                       {root,  new Root()}});
    reduceExprWithOperators(expr, operatorMap);

    operatorMap = opMap({{multiply, new Multiply()},
                         {divide,   new Divide()}});
    reduceExprWithOperators(expr, operatorMap);

    operatorMap = opMap({{add,       new Add()},
                         {substract, new Substract()}});
    reduceExprWithOperators(expr, operatorMap);
    return expr[0].getValue();
}

double Calculator::evaluate(std::string expr) {
    expr = prepareExpression(expr);
    expression parsedExpr;

    try {
        parsedExpr = parseExpr(expr);
    }
    catch (const char *error) {
        std::cout << error << std::endl;
        return 0;
    };

    double result = calculateExpr(parsedExpr);
    if (std::isnan(result)){
        std::cout << "Negative under root?? Go back to kindergarten! :)" << std::endl;
        return 0;
    }
    if (std::isinf(result)){
        std::cout << "Dividing by zero?? Nice try! :)" << std::endl;
        return 0;
    }
    return result;
}