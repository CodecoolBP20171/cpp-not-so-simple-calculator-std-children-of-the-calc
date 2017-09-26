#include "Operators.h"


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

double Power::doOperation(double a, double b) {
    return pow(a,b);
}
double Root::doOperation(double a, double b) {
    return pow(b, 1/a);
}

