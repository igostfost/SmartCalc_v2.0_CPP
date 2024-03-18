#include "polishNotation.h"

const std::map<std::string, char> s21::polishNotation::functions = {
    {"sin", 's'},  {"cos", 'c'},  {"tan", 't'}, {"asin", 'i'}, {"acos", 'o'},
    {"atan", 'n'}, {"sqrt", 'q'}, {"ln", 'l'},  {"log", 'g'}};

std::string s21::polishNotation::toPostfix(const std::string &infix) {
  std::stack<char> operatorStack;
  std::string postfix = "";
  // // Определение приоритетов операторов
  std::map<char, int> Priority = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},
                                  {'%', 2}, {'u', 4}, {'^', 5}};

  s21::StringValidator checkString(infix);
  if (!checkString.IsValid()) {
    throw std::invalid_argument("Уравнение некорректно!");
  }
  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    if (std::isdigit(c) || c == '.') {
      findNumeric(infix, i, postfix);
    }
    // Если встретили открывающую скобку, то кладем ее в стек
    else if (c == '(') {
      operatorStack.push(c);
    }
    // Если встретили закрывающую скобку, то кладем ее в стек
    else if (c == ')') {
      // Убираем все операторы из стека до открывающей скобки.
      while (!operatorStack.empty() && operatorStack.top() != '(') {
        postfix += operatorStack.top();
        postfix += ' ';
        operatorStack.pop();
      }
      // Убрать открывающую скобку из стека
      if (!operatorStack.empty()) {
        operatorStack.pop();
      }
    }
    // Если текущий символ — это унарный минус.
    else if (c == '-') {
      // Проверка на унарный минус
      if (i == 0 || infix[i - 1] == '(' || operation(infix[i - 1])) {
        operatorStack.push('u');
      } else {
        // Если это не унарный минус, обрабатываем как обычный бинарный оператор
        while (!operatorStack.empty() && operatorStack.top() != '(' &&
               priorityOperation(operatorStack.top()) >= priorityOperation(c)) {
          //  Priority[operatorStack.top()] >= Priority[c]) {
          postfix += operatorStack.top();
          postfix += ' ';
          operatorStack.pop();
        }
        operatorStack.push(c);
      }
    }
    //// Если символ является другим оператором
    else if (operation(c)) {
      while (
          !operatorStack.empty() && operatorStack.top() != '(' &&
          (c != '^'
               ? priorityOperation(operatorStack.top()) >= priorityOperation(c)
               : priorityOperation(operatorStack.top()) >
                     priorityOperation(
                         c))) {  // для степени приоритет строго больше,
                                 // чтобы соблюсти правую ассоциативность

        postfix += operatorStack.top();
        postfix += ' ';
        operatorStack.pop();
      }
      operatorStack.push(c);
    } else {
      std::string fx = "";
      // Извлечь имя функции.
      while (i < infix.size() && std::isalpha(infix[i])) {
        fx += infix[i++];
      }
      --i;  // Корректируем сетчик после взятия символа для поиска функции
      // Если такая функция есть в нашей мапе, то  добавляем ее значение в стек.
      if (functions.find(fx) != functions.end()) {
        operatorStack.push(functions.at(fx));
      }
    }
  }
  // Добавление оставшихся операторов из стека в конец постфиксной строки
  while (!operatorStack.empty()) {
    postfix += operatorStack.top();
    postfix += ' ';
    operatorStack.pop();
  }

  return postfix;
}

void s21::polishNotation::findNumeric(const std::string &infix, size_t &index,
                                      std::string &postfix) {
  while (index < infix.size() &&
         (std::isdigit(infix[index]) || infix[index] == '.' ||
          infix[index] == 'e' || infix[index] == 'E')) {
    postfix += infix[index];
    if ((infix[index] == 'e' || infix[index] == 'E') &&
        index + 1 < infix.size() &&
        (infix[index + 1] == '+' || infix[index + 1] == '-')) {
      postfix += infix[++index];  // Добавляем '+' или '-'
      // Удостоверимся, что за '+' или '-' следует число
      if (index + 1 < infix.size() && std::isdigit(infix[index + 1])) {
        postfix += infix[++index];
      } else {
        // Если за '+' или '-' не следует число, то выбрасываем исключение
        throw std::invalid_argument("Некорректная научная нотация числа");
      }
    }
    index++;
  }
  postfix += ' ';
  index--;  // Компенсируем инкремент index на послед
}

bool s21::polishNotation::operation(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' ||
         c == 'u';
}

int s21::polishNotation::priorityOperation(char c) {
  switch (c) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
    case '%':
      return 2;
    case 'u':
      return 4;
    case '^':
      return 5;
    default:
      return 6;
  }
}

// int main() {

//   std::string infix;
//   std::cout << "Введите инфиксное выражение: ";
//   std::cin >> infix;
//   std::cout << infix<< std::endl;

//   std::string result = s21::polishNotation::toPostfix(infix);
//   std::cout << result;

//   return 0;
// }
