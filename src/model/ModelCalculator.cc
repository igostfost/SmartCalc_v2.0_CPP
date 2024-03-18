#include "ModelCalculator.h"

double s21::ModelCalculator::evaluateExpression(const std::string &expression) {
  setlocale(LC_NUMERIC, "C");
  std::string postfix = polishNotation::toPostfix(expression);
  std::stack<double> operands;

  std::istringstream inputStream(postfix);
  std::string token;
  while (inputStream >> token) {
    // for (char ch : postfix) {
    if (token[0] == '+' || token[0] == '-' || token[0] == '*' ||
        token[0] == '/' || token[0] == '^' ||
        token[0] == '%') {  // || token[0] == 'u') {
      if (operands.size() < 2) {
        throw std::runtime_error("Недостаточно чисел для операции");
      }

      double operand2 = operands.top();
      operands.pop();
      double operand1 = operands.top();
      operands.pop();
      operands.push(binaryCalculate(token[0], operand1, operand2));
    }

    else if (isalpha(token[0])) {
      // Если символ - буква (проверка на унарные операторы)
      if (operands.empty()) {
        throw std::runtime_error("Ожидался аргумент для унарной функции");
      }
      double operand1 = operands.top();
      operands.pop();
      operands.push(unaryCalculate(token[0], operand1));
    } else {
      operands.push(std::stod(token));
    }
  }
  if (operands.size() != 1) {
    throw std::runtime_error("Ошибка в выражении");
  }

  // Результат будет находиться на вершине стека
  return operands.top();
}

double s21::ModelCalculator::unaryCalculate(char func, double operand) {
  switch (func) {
    case 's':
      return sin(operand);
    case 'c':
      return cos(operand);
    case 't':
      return tan(operand);
    case 'i':
      return asin(operand);
    case 'o':
      return acos(operand);
    case 'n':
      return atan(operand);
    case 'q':
      if (operand < 0.0) {
        throw std::runtime_error("Отрицательное значение под корнем");
      }
      return sqrt(operand);
    case 'l':
      if (operand <= 0.0) {
        throw std::runtime_error("ln от неположительного числа");
      }
      return log(operand);
    case 'g':
      if (operand <= 0.0) {
        throw std::runtime_error("log от неположительного числа");
      }
      return log10(operand);
    case 'u':
      return 0 - operand;
    default:
      throw std::runtime_error("Неизвестная унарная функция");
  }
}

double s21::ModelCalculator::binaryCalculate(char operation, double operand1,
                                             double operand2) {
  switch (operation) {
    case '+':
      return operand1 + operand2;
    case '-':
      return operand1 - operand2;
    case '*':
      return operand1 * operand2;
    case '/':
      if (operand2 == 0.0) {
        throw std::runtime_error("Деление на ноль");
      }
      return operand1 / operand2;
    case '%':
      return fmod(operand1, operand2);
    case '^':
      return pow(operand1, operand2);
    default:
      throw std::runtime_error("Неизвестная бинарная операция");
  }
}

// int main() {
//    std::string infix;
//   std::cout << "Введите инфиксное выражение: ";
//   std::cin >> infix;
//   std::cout << infix<< std::endl;
//     s21::ModelCalculator result;
//     double calculatedResult = result.evaluateExpression(infix);
//     std::cout << "Результат вычисления: " << calculatedResult << std::endl;

//     return 0;
// }