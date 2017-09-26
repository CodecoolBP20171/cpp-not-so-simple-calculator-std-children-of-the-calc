#include "Operators.h"
#include <iostream>


double Add::doOperation(double a, double b) {
    return a+b;
}

double Substract::doOperation(double a, double b) {
    return a-b;
}

double Multiply::doOperation(double a, double b) {
    return a*b;
}

double Divide::doOperation(double a, double b) {
    return a/b;
}
