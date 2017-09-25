
#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOR_H

#include <iostream>

class Calculator {
public:
    double evaluate(std::string expr);

private:
    std::string eliminateSpaces(std::string expr);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOR_H
