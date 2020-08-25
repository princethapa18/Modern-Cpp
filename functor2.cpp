// 25 aug 2020

#include <iostream>

// using function pointers
double add(double left, double right) {
    return left + right;
}

double multiply(double left, double right) {
    return left * right;
}

double binary_op(double left, double right, double (*f)(double, double)) {
    return (*f)(left, right);
}

// Using functors   
// functors can remember state

// Abstract base class                                                                                                                                                                                                  
class BinaryFunction {
public:
  BinaryFunction() {};
  virtual double operator() (double left, double right) = 0;
};

// Add two doubles                                                                                                                                                                                                      
class Add : public BinaryFunction {
public:
  Add() {};
  virtual double operator() (double left, double right) { return left+right; }
};

// Multiply two doubles                                                                                                                                                                                                 
class Multiply : public BinaryFunction {
public:
  Multiply() {};
  virtual double operator() (double left, double right) { return left*right; }
};

double binary_op2(double left, double right, BinaryFunction* bin_func) {
  return (*bin_func)(left, right);
}

int main( ) {
    double a = 5.0;
    double b = 10.0;

    //std::cout << "Add: " << binary_op(a, b, add) << std::endl;
    //std::cout << "Multiply: " << binary_op(a, b, multiply) << std::endl;
    
    BinaryFunction* pAdd = new Add();
    BinaryFunction* pMultiply = new Multiply();

    std::cout << "Add: " << binary_op2(a, b, pAdd) << std::endl;
    std::cout << "Multiply: " << binary_op2(a, b, pMultiply) << std::endl;

    return 0;
}