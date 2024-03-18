#ifndef STRING_VALIDATION
#define STRING_VALIDATION

#include <cctype>
#include <iostream>
#include <set>
#include <string>

namespace s21 {

class StringValidator {
 public:
  explicit StringValidator(const std::string &input) : stringEquation_(input) {}

  /**
   * @brief Проверяет, корректная ли строка нам подана
   *
   * @return true Если строка корректна.
   * @return false Если строка некорректна.
   */
  bool IsValid() const;

 private:
  const std::string operators = "+-*/^%";
  const std::set<std::string> functions = {
      "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};
  mutable int open_bracket = 0;
  mutable int close_bracket = 0;
  bool IsValidNumber(const std::string &equation, size_t &index) const;
  bool IsValidOperator(size_t i) const;
  bool HandleOpenBracket(size_t i) const;
  bool HandleCloseBracket(size_t i) const;
  bool IsValidFunction(size_t &i) const;

  std::string stringEquation_;
};
}  // namespace s21

#endif