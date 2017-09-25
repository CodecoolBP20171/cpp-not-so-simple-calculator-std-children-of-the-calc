//
// Created by birop on 2017.09.25..
//

#include "ExprElem.h"

ElemType ExprElem::getElemType() const {
    return elemType;
}

double ExprElem::getValue() const {
    return value;
}

OperType ExprElem::getOperation() const {
    return operation;
}

ExprElem::ExprElem(double value) : value(value) {
    elemType = num;
}

ExprElem::ExprElem(OperType operation) : operation(operation) {
    elemType = oper;
}
