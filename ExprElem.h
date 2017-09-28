
#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_EXPRELEM_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_EXPRELEM_H


enum ElemType {oper, num};
enum OperType { multiply = '*', divide = '/', add = '+', substract = '-', root = 'r', power = '^'};

class ExprElem {
private:
    ElemType elemType;
    double value;
    OperType operation;

public:
    ExprElem(double value);
    ExprElem(OperType operation);
    ElemType getElemType() const;
    double getValue() const;
    OperType getOperation() const;

};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_EXPRELEM_H
