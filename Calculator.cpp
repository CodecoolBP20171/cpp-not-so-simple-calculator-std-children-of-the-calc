#include "Calculator.h"

std::string Calculator::eliminateSpaces(std::string expr) {
    std::string newExpr;
    for (char c: expr) {
        if (c != ' ') {
            newExpr += c;
        }
    }
    return newExpr;
}

double Calculator::evaluate(std::string expr) {
    expr = eliminateSpaces(expr);

    return 0;
}