#include "stringValidation.h"

bool s21::StringValidator::IsValid() const {
  bool valid = true;
  for (size_t i = 0; i < stringEquation_.length() && valid; ++i) {
    char currentSymbol = stringEquation_[i];
    // Проверка на число, десятичную точку или экспоненту
    if (std::isdigit(currentSymbol) || currentSymbol == '.' ||
        currentSymbol == 'e' || currentSymbol == 'E') {
      if (!IsValidNumber(stringEquation_, i)) {
        valid = false;
        break;
      }
    }
    // Проверка на наличие оператора
    else if (operators.find(currentSymbol) != std::string::npos) {
      if (!IsValidOperator(i)) {
        valid = false;
      }
    }
    // Проверка на открывающую скобку
    else if (currentSymbol == '(') {
      valid = HandleOpenBracket(i);
    }
    // Проверка на закрывающую скобку
    else if (currentSymbol == ')') {
      valid = HandleCloseBracket(i);
    }
    // Проверка на наличие функции
    else {
      if (!IsValidFunction(i)) {
        valid = false;
        break;
      }
    }
  }
  // Проверка на корректность окончания строки и парность скобок
  if (operators.find(stringEquation_.back()) != std::string::npos ||
      open_bracket != close_bracket) {
    valid = false;
  }

  return valid;
};

bool s21::StringValidator::IsValidNumber(const std::string& str,
                                         size_t& pos) const {
  bool hasDot = false;  // Есть ли точка в числе
  bool hasExp = false;  // Есть ли экспоненциальный символ ('e' или 'E')
  bool digitBefore = false;  // Была ли цифра перед текущим символом

  while (pos < str.length()) {
    char ch = str[pos];

    if (std::isdigit(ch)) {
      digitBefore = true;
    } else if (ch == '.') {
      if (hasDot || hasExp) {
        return false;  // Уже есть точка или экспонента
      }
      hasDot = true;
    } else if (ch == 'e' || ch == 'E') {
      if (!digitBefore || hasExp) {
        return false;
      }
      hasExp = true;
      digitBefore = false;

      // Переходим к следующему символу для проверки наличия знака и цифры после
      // экспоненты
      if (++pos < str.length()) {
        char nextChar = str[pos];
        if (nextChar == '+' || nextChar == '-') {
          // Пропускаем знак, убеждаемся, что после него идет цифра
          if (++pos < str.length() && std::isdigit(str[pos])) {
            digitBefore = true;
          } else {
            return false;  // После 'e' или 'E' идет знак, но нет цифры
          }
        } else if (!std::isdigit(nextChar)) {
          return false;  // Сразу после 'e' или 'E' нет ни знака, ни цифры
        } else {
          digitBefore = true;  // Сразу после 'e' или 'E' идет цифра
        }
      } else {
        return false;  // Строка заканчивается на 'e' или 'E'
      }
    } else {
      // Выходим из цикла, так как следующий символ не является частью числа
      pos--;
      break;
    }

    pos++;
  }

  // Проверяем, что после экспоненты есть число
  if (hasExp && !digitBefore) {
    return false;
  }

  return true;  // Число валидно
}

bool s21::StringValidator::IsValidOperator(size_t i) const {
  if (i == 0 && stringEquation_[i] != '-') return false;
  // Унарный минус может стоять в начале строки или после '(' или другого
  // оператора.
  if (stringEquation_[i] == '-' &&
      (i == 0 || stringEquation_[i - 1] == '(' ||
       operators.find(stringEquation_[i - 1]) != std::string::npos)) {
    return true;
  }
  // Проверка на два оператора подряд (кроме унарного минуса).
  if (i > 0 && operators.find(stringEquation_[i - 1]) != std::string::npos)
    return false;
  // Оператор не может идти сразу после открывающей скобки.
  if (i > 0 && stringEquation_[i - 1] == '(') return false;
  // Оператор не может предшествовать закрывающей скобке.
  if (i < stringEquation_.length() - 1 && stringEquation_[i + 1] == ')')
    return false;
  return true;
}

bool s21::StringValidator::HandleOpenBracket(size_t i) const {
  if (i > 0 &&
      (std::isdigit(stringEquation_[i - 1]) || stringEquation_[i - 1] == ')')) {
    return false;
  }
  if (i + 1 < stringEquation_.length() && stringEquation_[i + 1] == ')') {
    return false;
  }
  open_bracket++;
  return true;
}

bool s21::StringValidator::HandleCloseBracket(size_t i) const {
  if (i + 1 < stringEquation_.length() &&
      std::isdigit(stringEquation_[i + 1])) {
    return false;
  }
  close_bracket++;
  if (i == 0 || operators.find(stringEquation_[i - 1]) != std::string::npos) {
    return false;
  }

  return true;
}

bool s21::StringValidator::IsValidFunction(size_t& i) const {
  bool found_func = false;
  for (const std::string& func : functions) {
    if (stringEquation_.substr(i, func.length()) == func) {
      found_func = true;
      // Пропуск названия функции
      i += func.length() - 1;
      // Проверка на открывающую скобку после функции
      if (i + 1 == stringEquation_.length() || stringEquation_[i + 1] != '(') {
        return false;  // Отсутствие открывающей скобки после функции делает
                       // выражение невалидным
      }
      break;
    }
  }
  return found_func;  // Возвращает true, если найдена функция, иначе false
}

// int main() {

//   std::string infix;
//   std::cout << "Введите инфиксное выражение: ";
//   std::cin >> infix;
//   std::cout << infix<< std::endl;
//  s21::StringValidator result =  s21::StringValidator(infix);

// bool res = result.IsValid();
//   std::cout << res;

//   return 0;
// }