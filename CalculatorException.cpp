#include "CalculatorException.h"

CalculatorException::CalculatorException(ErrorType errorType, int errorPlace) : errorPlace(errorPlace),
                                                                                errorType(errorType) {}

int CalculatorException::getErrorPlace() const {
    return errorPlace;
}

ErrorType CalculatorException::getErrorType() const {
    return errorType;
}

void CalculatorException::changeErrorPlace(int offset) {
    errorPlace += offset;
}
