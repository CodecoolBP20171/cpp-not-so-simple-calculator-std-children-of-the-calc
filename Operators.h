
#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_OPERATORS_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_OPERATORS_H

class Operator {
public:
    virtual double doOperation(double a, double b) = 0;

};

class Add : public Operator {
public:
    double doOperation(double a, double b) override;
};

class Substract : public Operator {
public:
    double doOperation(double a, double b) override;
};

class Multiply : public Operator {
public:
    double doOperation(double a, double b) override;
};

class Divide : public Operator {
public:
    double doOperation(double a, double b) override;
};

#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_STD_CHILDREN_OF_THE_CALC_OPERATORS_H
