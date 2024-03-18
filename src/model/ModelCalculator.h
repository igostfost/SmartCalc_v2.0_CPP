#ifndef MODELCALCULATOR_H
#define MODELCALCULATOR_H

#include <cmath>
#include <sstream>
#include <stack>
#include <stdexcept>

#include "polishNotation.h"

namespace s21 {
class ModelCalculator {
 public:
  ModelCalculator() : answer_(0){};
  ModelCalculator(const std::string &express)
      : answer_(evaluateExpression(express)) {}
  double evaluateExpression(const std::string &expression);
  double unaryCalculate(char func, double operand);
  double binaryCalculate(char operation, double operand1, double operand2);

 private:
  double answer_;
};

}  // namespace s21

#endif