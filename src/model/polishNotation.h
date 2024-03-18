#ifndef POLISH_NOTATION
#define POLISH_NOTATION

#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>

#include "stringValidation.h"

namespace s21 {

class polishNotation {
 public:
  /**
   * Конвертирует инфиксную запись в постфиксную.
   *
   * @param infix строка в инфиксной записи.
   * @return строка в постфиксной записи.
   * @throws std::invalid_argument если входное выражение некорректно.
   */
  static std::string toPostfix(const std::string &infix);
  static const std::map<std::string, char> functions;
  /**
   * @brief Обрабатывает числовые значения, включая десятичные и научную
   * нотацию, добавляя их в постфиксную строку.
   *
   * @param infix Инфиксное выражение для обработки.
   * @param index Индекс текущего символа в инфиксном выражении.
   * @param postfix Строка, в которую добавляется постфиксное выражение.
   */
  static void findNumeric(const std::string &infix, size_t &index,
                          std::string &postfix);

  static bool operation(char c);

  static int priorityOperation(char c);

 private:
};
}  // namespace s21
#endif