#include "Calculator.h"

Calculator::Calculator() {
    validOperators = "+-/*r^";
    validOperators += SIGN_INDICATOR;
    opmaps = std::vector<opMap>({
                                        opMap{{power, new Power()},
                                              {root,  new Root()}},
                                        opMap{{multiply, new Multiply()},
                                              {divide,   new Divide()}},
                                        opMap{{add,       new Add()},
                                              {substract, new Substract()}}
                                });
}

Calculator::~Calculator() {
    for (opMap ops : opmaps) {
        for (auto op : ops) delete op.second;
    }
}

std::string Calculator::prepareExpression(std::string expr) {
    expr = std::regex_replace(expr, std::regex("root"), "r");
    std::string newExpr;
    for (int i =0; i < expr.length(); ++i) {
        char c = expr[i];
        if (c == SIGN_INDICATOR) throw CalculatorException(spellingOrMissingParen, i);
        if (!isspace(c) ) newExpr += c;
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
    if (parentCount != 0) throw CalculatorException(missingClosingParen, i);
    return i;
}

void Calculator::replaceParenthesesWithResult(std::string &expr, unsigned long openIndex, long i) {
    double result;
    try {
        result = calculate(expr.substr(openIndex + 1, i - openIndex - 2));
    } catch (CalculatorException &e) {
        e.changeErrorPlace(openIndex);
        throw e;
    }
    std::string stringToReplace;

    if (isdigit(expr[openIndex - 1])) {
        stringToReplace = "*";
    }
    if (result < 0) {
        stringToReplace += SIGN_INDICATOR + std::to_string(result).substr(1);
    }
    else {
        stringToReplace += std::to_string(result);
    }
    expr.replace(openIndex, i - openIndex, stringToReplace);
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
                    throw CalculatorException(missingOperand, i);
                }
            } else {
                throw CalculatorException(spellingOrMissingParen, i);
            }
        }
    }
    parsedExpr.emplace_back(ExprElem(sign * std::stod(expr.substr(slowIndex))));

    return parsedExpr;
}

bool Calculator::isNotSign(const std::string &expr, unsigned int i) const { return expr[i] != '-' || i != 0; }

bool Calculator::isCharPartOfNum(char c) const { return isdigit(c) || c == '.'; }

bool Calculator::isOperatorAfterNum(unsigned int slowIndex, unsigned int i) const {
    return i - slowIndex > 0;
}

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

            if (std::isnan(tempResult)) throw CalculatorException(negativeRootOperand, i);
            if (std::isinf(tempResult)) throw CalculatorException(zeroDiv, i);

            //replacing operator and its operands to the partial result
            expr.erase(expr.begin() + i - 1, expr.begin() + i + 2);
            expr.emplace(expr.begin() + i - 1, ExprElem(tempResult));
        } else i += 2;
    }
}

double Calculator::calculateExpr(expression expr) {
    for (const opMap &ops : opmaps) {
        reduceExprWithOperators(expr, ops);
    }
    return expr[0].getValue();
}

double Calculator::calculate(std::string expr) {
    expr = prepareExpression(expr);
    expression parsedExpr = parseExpr(expr);
    return calculateExpr(parsedExpr);
}

double Calculator::evaluate(std::string expr) {
    try {
        return calculate(expr);
    } catch (CalculatorException &e) {
        handleErronousExpression(expr, e);
        return 0;
    }
}

void Calculator::handleErronousExpression(const std::string &expr, const CalculatorException &e) const {
    printBaseMessage(e.getErrorType());
    std::cout << expr << std::endl;
    int errorPlace = e.getErrorPlace();
    for (int i = 0; i < expr.length() && errorPlace > 0; ++i) {
        if (!isspace(expr[i])) --errorPlace;
        if (expr[i] == 'r') {
            if (errorPlace > 1) errorPlace += 3;
            else break;
        }
        std::cout << "-";
    }
    std::cout << "^" << std::endl;
}

void Calculator::printBaseMessage(const ErrorType &errorType) const {
    switch (errorType) {
        case zeroDiv:
            std::cout << "Dividing by zero?? Nice try! :)" << std::endl;
            break;
        case negativeRootOperand:
            std::cout << "Negative under root?? Go back to kindergarten! :)" << std::endl;
            break;
        case missingClosingParen:
            std::cout << "Missing closing parentheses" << std::endl;
            break;
        case missingOperand:
            std::cout << "Invalid expression, missing operand" << std::endl;
            break;
        case spellingOrMissingParen:
            std::cout << "Invalid expression, probably misspelling, missing parentheses" << std::endl;
            break;
        default:
            std::cout << "This should never happen!" << std::endl;
            break;
    }
}