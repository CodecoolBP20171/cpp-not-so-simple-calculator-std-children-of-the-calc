#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOREXCEPTION_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOREXCEPTION_H

#include <iostream>

enum ErrorType {
    zeroDiv,
    negativeRootOperand,
    missingOperand,
    missingClosingParen,
    spellingOrMissingParen
};

class CalculatorException {
public:
    CalculatorException(ErrorType errorType, int errorPlace);

    int getErrorPlace() const;

    ErrorType getErrorType() const;

    void changeErrorPlace(int offset);

public:
private:
    int errorPlace;
    ErrorType errorType;
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_CALCULATOREXCEPTION_H
