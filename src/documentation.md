# Implementation of SmartCalc v2.0.

## Instruction for Makefile:

Make all: testing and install an app 
протестировать и установить приложение

Make uninstall: uninstall an app 
удалить приложение

Make dvi: open this documentation 
открыть эту документацию

Make dist: tar an app 
создать архив со всеми файлами для этого приложения

Make test: run unit tests for model part of an app 
запустить модульные тесты для модельной части приложения

Make format: reformat all code
переформатировать весь код

Make clean: clear the project of excess
очистить проект от лишнего

## SmartCalc v2.0 by Oceanusp


### Описание проекта:

Эта программа представляет собой универсальный калькулятор, который позволяет пользователям выполнять различные вычисления, включая вычисление арифметических выражений, построение графиков функций, расчет кредитов и депозитов.

Программа предоставляет интуитивно понятный пользовательский интерфейс для ввода выражений и просмотра результатов.

Калькулятор предлагает большую гибкость и точность, что делает его пригодным для различных математических расчетов и финансовых расчетов.

Пользователи могут эффективно считать сложные арифметические выражения, визуализировать графики функций и принимать обоснованные финансовые решения, используя режим кредитного и депозитного калькуляторов. 

Программа реализована с использованием паттерна MVC что подразумевает деление программы на 3 части View, Controller, Model.

#### View 
Включает в себя визуальную часть приложения разработанную в прилдожении QT qreator включает в себя 4 окна - основоное mainwindow, которое содержит кнопки и место для ввода выражения, graphwindow окно которое содержит виджет отрисовки график сторонней библиотеки qcustomplot и поля для изменения поля отрисовки, creditwindow - окно для отображение всего функционала кредитного калькулятора и  depositwindow - окно для отображение всего функционала депозитного калькулятора.

#### Controller 
Включает в себя класс CalculatorController который находится в пространстве имен s21 и имеет методы для взаимодействия модельной части и визуальной.

#### Model 
Включает в себя модельную часть программы со всей бизнес логикой. Включает в себя классы: ModelСalculator, stringValidator,polishNotation, Credit, Deposit которые находятся в пространстве имен s21.

##### ModelСalculator
Основоной класс модельной части содержащий в себе всю логику вычислительного процесса.
ModelСalculator: в метод класса evaluateExpression подается валидное уравнение в постфиксной записи, затем метод смотрит унарная операция или бинарная и вызывает соответсвующие методы для расчетов. В итоге возвращаем ответ типа double.

##### stringValidator
stringValidator: Здесь происходит валидация входной строки. Содержит в себе проверки на число, бинарный оператор, унарный оператор префиксный/постфиксный, унарная функция, отрытие скобок, закрытие скобок, приоритет, асоциативность. 

##### polishNotation
polishNotation: Этот класс выполняет преобразование инфиксной записи в постфиксную. Используется стек для временного хранения операторов. В результате работы этого этапа формируется строка в постфиксной нотации.


Весь процесс направлен на преобразование входного арифметического выражения в форму, которую легко вычислить. Это включает в себя разбиение выражения на токены,проверку корректности выраженияб обработку унарных операторов, преобразование инфиксной нотации в постфиксную и, наконец, вычисление значения выражения.


##### CreditCalculator 
Класс кредитной модели получает параметры для вычислений в конструкторе, есть методы для возврата ответов.

##### DepositCalculator 
Класс депозитной модели получает параметры для вычислений в конструкторе, есть методы для возврата ответов.

### Вычисление арифметического выражения:

Пользователи могут вводить произвольные арифметические выражения в инфиксной нотации, используя распространенные арифметические операторы, такие как сложение, вычитание, умножение, деление, степень и модуль.

Калькулятор точно вычисляет выражения до 7 знаков после запятой и может обрабатывать выражения до 255 символов.

Он поддерживает математические функции, такие как косинус, синус, тангенс, арккосинус, арксинус, арктангенс, квадратный корень, натуральный логарифм и десятичный логарифм.

### Построение графика:

Пользователи могут строить графики функций, заданных в инфиксной нотации с переменной «x».

Программа предоставляет удобную систему координат с нанесенными шкалами и адаптивной сеткой.

Домен и кодовый домен функции ограничены диапазоном от -1 000 000 до 1 000 000, но пользователь может указать отображаемый домен и кодовый домен для построения графика.

Чтобы создать изображение графика, пользователь должен ввести уравнение, щелкнуть кнопку "GRAPH" и нажать кнопку "Нарисовать". Также есть возможность ввода уравнения гафика в этом же окне и просмотр масштаба графика, с помощью колеса мыши.

### Кредитный калькулятор:

В программу включен специальный режим, известный как "Кредитный калькулятор".

Пользователи могут вводить такие данные, как общая сумма кредита, срок (длительность), процентная ставка и тип кредита (аннуитетный или дифференцированный).

На основе введенных данных калькулятор предоставляет такую ​​информацию, как ежемесячный платеж, переплата по кредиту и общая сумма платежа.

### Депозитный калькулятор:

В программу включен специальный режим, известный как "Депозитный калькулятор".

Пользователи могут вводить такие данные, как общая сумма вклада, срок (длительность), процентная ставка, налоговая ставка, переодичность выплат, капитализация и также есть опции пополнения и снятия.

На основе введенных данных калькулятор предоставляет такую ​​информацию, сумма начислений, сумма вклада с процентами и сумма уержанных налогов.

### INGLISH DOC

### Makefile Instructions:
Make all: Test and install the app.
Test and install the application.

Make uninstall: Uninstall the app.
Uninstall the application.

Make dvi: Open this documentation.
Open this documentation.

Make dist: Create an archive for the app.
Create an archive with all the files for this application.

Make test: Run unit tests for the model part of the app.
Run unit tests for the model part of the application.

Make format: Reformat all code.
Reformat all code.

Make clean: Clear the project of excess.
Clean the project from unnecessary files.

### SmartCalc v2.0 by Oceanusp
Project Description:
This program is a universal calculator that allows users to perform various computations, including arithmetic expressions, function graphing, credit and deposit calculations.

The program offers an intuitive user interface for expression input and result visualization.

The calculator offers great flexibility and precision, making it suitable for various mathematical and financial calculations.

Users can efficiently perform complex arithmetic expressions, visualize function graphs, and make informed financial decisions using the credit and deposit calculator modes.

The program is implemented using the MVC pattern, which involves dividing the program into 3 parts: View, Controller, Model.

### View:
Includes the visual part of the application developed in QT creator. It includes 4 windows: the main window containing buttons and space for expression input, the graph window with QCustomPlot widget for graph rendering and fields for adjusting the graph, the credit window displaying the credit calculator functionality, and the deposit window for the deposit calculator functionality.

### Controller:
Includes the CalculatorController class located in the s21 namespace and contains methods for interaction between the model and the view.

### Model:
Includes the model part of the program with all the business logic. It comprises classes: ModelCalculator, stringValidator, polishNotation, Credit, Deposit located in the s21 namespace.

### ModelCalculator:
The main class containing all the computational logic. In the evaluateExpression method, a valid postfix equation is provided, where unary or binary operations are checked, and corresponding methods for calculations are invoked. Eventually, it returns the answer as a double.

### stringValidator:
Performs validation of the input string. It includes checks for a number, binary operator, prefix/postfix unary operator, unary function, opening and closing brackets, priority, and associativity.

### polishNotation:
This class performs the transformation of infix notation to postfix notation. It utilizes a stack for temporarily storing operators. The output of this phase is a string in postfix notation.

### CreditCalculator:
The credit model class receives parameters for calculations in the constructor and has methods to return the answers.

### DepositCalculator:
The deposit model class receives parameters for calculations in the constructor and has methods to return the answers.

### Arithmetic Expression Evaluation:
Users can enter arbitrary arithmetic expressions in infix notation using common arithmetic operators such as addition, subtraction, multiplication, division, exponentiation, and modulus.

The calculator accurately computes expressions up to 7 decimal places and can handle expressions up to 255 characters.

It supports mathematical functions like cosine, sine, tangent, arccosine, arcsine, arctangent, square root, natural logarithm, and decimal logarithm.

### Graph Plotting:
Users can plot graphs of functions specified in infix notation with the variable 'x'.

The program provides a convenient coordinate system with scales and an adaptive grid.

The domain and code domain of the function are limited to the range from -1,000,000 to 1,000,000, but the user can specify the displayed domain and code domain for graph plotting.

To create a graph image, the user needs to input the equation, click the "GRAPH" button, and press the "Draw" button. There is also an option to input the graph equation in the same window and view the graph scale using the mouse wheel.

### Credit Calculator:
The application includes a special mode known as the "Credit Calculator".

Users can input data such as the total loan amount, term (duration), interest rate, and loan type (annuity or differentiated).

Based on the entered data, the calculator provides information such as the monthly payment, overpayment on the loan, and the total payment amount.

### Deposit Calculator:
The application includes a special mode known as the "Deposit Calculator".

Users can input data such as the total deposit amount, term (duration), interest rate, tax rate, payment periodicity, capitalization, and also have options for additional contributions and withdrawals.

Based on the entered data, the calculator provides information such as the total accrued interest, total deposit with interest, and the amount of withheld taxes.