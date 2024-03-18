#include <gtest/gtest.h>

#include "ModelCalculator.h"
#include "ModelCredit.h"
#include "ModelDeposit.h"
#include "polishNotation.h"
#include "stringValidation.h"

TEST(StringValidatorTest, ValidString1) {
  s21::StringValidator validator("1+2*3-sin(90)/tan(45+2*3)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString2) {
  s21::StringValidator validator("ln(2+2)*log(10)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString3) {
  s21::StringValidator validator("sqrt(16*16+9*9)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString4) {
  s21::StringValidator validator("1+(2*(3+4)-5)/6");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString5) {
  s21::StringValidator validator("asin(0.5)^2");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString6) {
  s21::StringValidator validator("cos(90)*tan(45)");
  ASSERT_TRUE(validator.IsValid());
}

// TEST(StringValidatorTest, ValidString7) {
//   s21::StringValidator validator("ln(2.71)");
//   ASSERT_TRUE(validator.IsValid());
// }

TEST(StringValidatorTest, ValidString8) {
  s21::StringValidator validator("sqrt(2+2*2)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString9) {
  s21::StringValidator validator("(2+2)*(3+3)/(4+4)");
  ASSERT_TRUE(validator.IsValid());
}

// TEST(StringValidatorTest, ValidString10) {
//   s21::StringValidator validator("acos(0.5)*atan(1)");
//   ASSERT_TRUE(validator.IsValid());
//}

TEST(StringValidatorTest, ValidString11) {
  s21::StringValidator validator("2^3^2");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString12) {
  s21::StringValidator validator("log(100/10)*ln(7+7)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString13) {
  s21::StringValidator validator("1/(1+1)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString14) {
  s21::StringValidator validator("sin(30+30)+cos(60)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString15) {
  s21::StringValidator validator("sqrt(2)*sqrt(2)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString16) {
  s21::StringValidator validator("acos(0.5)^atan(1)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString17) {
  s21::StringValidator validator("-5+5*(-6)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString1) {
  s21::StringValidator validator("1+2++3");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString2) {
  s21::StringValidator validator("sin(90(90))");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString3) {
  s21::StringValidator validator("1()2");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString4) {
  s21::StringValidator validator("(1+2");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString5) {
  s21::StringValidator validator("tan(45)+");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString6) {
  s21::StringValidator validator("cos90)*tan(45)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString7) {
  s21::StringValidator validator("ln(2.71");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString8) {
  s21::StringValidator validator("sqrt+2+2*2)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString9) {
  s21::StringValidator validator("(2+2(3+3)/(4+4)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString10) {
  s21::StringValidator validator("2^3^");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString11) {
  s21::StringValidator validator("log(100/10)*ln(7+7+)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString12) {
  s21::StringValidator validator("sin30+30)+cos(60)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString13) {
  s21::StringValidator validator("sqrt(2*sqrt(2)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString14) {
  s21::StringValidator validator("1..2+2");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString15) {
  s21::StringValidator validator("()");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString16) {
  s21::StringValidator validator("sin5");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, UnknownFunction) {
  s21::StringValidator validator("blah(30)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, ClosingParenthesisBeforeNumber) {
  s21::StringValidator validator("1+2)3");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, ClosingParenthesisAfterOperator) {
  s21::StringValidator validator("1+*2)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString18) {
  s21::StringValidator validator("1.340781e+154");
  ASSERT_TRUE(validator.IsValid());
}

TEST(polishNotationTest, BasicConversion) {
  EXPECT_EQ(s21::polishNotation::toPostfix("1+2"), "1 2 + ");
  EXPECT_EQ(s21::polishNotation::toPostfix("3*4-5"), "3 4 * 5 - ");
  EXPECT_EQ(s21::polishNotation::toPostfix("6/(7+8)"), "6 7 8 + / ");
}

TEST(polishNotationTest, MultipleOperators) {
  EXPECT_EQ(s21::polishNotation::toPostfix("3+5*2-8/4"), "3 5 2 * + 8 4 / - ");
}

TEST(polishNotationTest, WithFunctions) {
  EXPECT_EQ(s21::polishNotation::toPostfix("sin(90)+cos(0)"), "90 s 0 c + ");
}

TEST(polishNotationTest, MultipleFunctionsAndPriorities) {
  EXPECT_EQ(s21::polishNotation::toPostfix("tan(45)+sin(30)*cos(60)-sqrt(9)/3"),
            "45 t 30 s 60 c * + 9 q 3 / - ");
}

TEST(polishNotationTest, NestedFunctions) {
  EXPECT_EQ(s21::polishNotation::toPostfix("sin(cos(45)+tan(30))"),
            "45 c 30 t + s ");
}

TEST(polishNotationTest, LongExpression) {
  EXPECT_EQ(s21::polishNotation::toPostfix(
                "2+3*4-5^6/tan(30)+7*8/9-10+asin(1)-acos(0)+atan(1)"),
            "2 3 4 * + 5 6 ^ 30 t / - 7 8 * 9 / + 10 - 1 i + 0 o - 1 n + ");
}

TEST(polishNotationTest, SequenceOfOperatorsAndFunctions) {
  EXPECT_EQ(s21::polishNotation::toPostfix("2*3+4/5-6^7%8"),
            "2 3 * 4 5 / + 6 7 ^ 8 % - ");
}

TEST(polishNotationTest, InvalidExpressionThrowsException) {
  EXPECT_THROW(s21::polishNotation::toPostfix("2+*3"), std::invalid_argument);
}

TEST(polishNotationTest, SequenceWithFloatingPointNumbers) {
  EXPECT_EQ(s21::polishNotation::toPostfix("2.5*3.1+4.6/5.7-6.8^7.9%8.2"),
            "2.5 3.1 * 4.6 5.7 / + 6.8 7.9 ^ 8.2 % - ");
}

TEST(StringValidatorTest, ValidString33) {
  s21::StringValidator validator("1.1.1+3");
  ASSERT_FALSE(validator.IsValid());
}

TEST(CalcTest, Test1) {
  s21::ModelCalculator test("2+5*3");
  EXPECT_NEAR(test.evaluateExpression("2+5*3"), 17, 1e-6);
}

TEST(CalcTest, Test2) {
  s21::ModelCalculator test("(3^3+4^2)*2");
  EXPECT_NEAR(test.evaluateExpression("(3^3+4^2)*2"), 86, 1e-6);
}

TEST(CalcTest, Test3) {
  s21::ModelCalculator test(
      "2+3*4-5^6/tan(30)+7*8/9-10+asin(1)-acos(0)+atan(1)");
  EXPECT_NEAR(test.evaluateExpression(
                  "2+3*4-5^6/tan(30)+7*8/9-10+asin(1)-acos(0)+atan(1)"),
              2450.38, 1e-2);
}

TEST(polishNotationTest, SimpleExponentialNumber) {
  EXPECT_EQ(s21::polishNotation::toPostfix("1.340781e+154+10*2"),
            "1.340781e+154 10 2 * + ");
}

TEST(CalcTest, Test4) {
  s21::ModelCalculator test("sqrt(4)+log(5)");
  EXPECT_NEAR(test.evaluateExpression("sqrt(4)+log(5)"), 2.698970, 1e-6);
}

TEST(CalcTest, Test5) {
  s21::ModelCalculator test;
  EXPECT_THROW(test.evaluateExpression("5/0"), std::runtime_error);
}

TEST(ModelCalculatorTest, UnaryMinusComplexTest) {
  s21::ModelCalculator calc("-4+(-4)*(-2)-sin(-30)");
  EXPECT_NEAR(calc.evaluateExpression("-4+(-4)*(-2)-sin(-30)"), 3.01197, 1e-5);
}

TEST(ModelCalculatorTest, CosFunction) {
  s21::ModelCalculator calc("cos(90)");
  EXPECT_NEAR(calc.evaluateExpression("cos(90)"), -0.44807, 1e-5);
}

TEST(CalcTest, Test6) {
  s21::ModelCalculator test;
  EXPECT_THROW(test.evaluateExpression("log(-5)"), std::runtime_error);
}

TEST(CalcTest, Test7) {
  s21::ModelCalculator test;
  EXPECT_THROW(test.evaluateExpression("ln(-5)"), std::runtime_error);
}

TEST(CalcTest, Test8) {
  s21::ModelCalculator test;
  EXPECT_THROW(test.evaluateExpression("sqrt(-5)"), std::runtime_error);
}

TEST(ModelCalculatorTest, Test9) {
  s21::ModelCalculator calc("10%3");
  EXPECT_NEAR(calc.evaluateExpression("10%3"), 1, 1e-5);
}

TEST(CalcTest, Test10) {
  s21::ModelCalculator test("ln(10)+log(5)");
  EXPECT_NEAR(test.evaluateExpression("ln(10)+log(5)"), 3.001555, 1e-6);
}

TEST(CalcTest, Test11) {
  s21::ModelCalculator test("-3^4");
  EXPECT_NEAR(test.evaluateExpression("-3^4"), -81, 1e-6);
}

TEST(CreditTest, DifferentialPayment) {
  s21::Credit credit;
  double credit_sum = 120000;
  double credit_time = 12;
  double percent = 10;
  int type_payment = 1;
  s21::Credit::PaymentOutput output;

  credit.calculate_credit(credit_sum, credit_time, percent, type_payment,
                          output);

  ASSERT_NEAR(output.total_payment, 126473.97, 1e-2);
  ASSERT_NEAR(output.first_payment, 11019.18, 1e-2);
  ASSERT_NEAR(output.last_payment, 10084.93, 1e-2);
  ASSERT_NEAR(output.overpayment, 6473.97, 1e-2);
}

TEST(CreditTest, AnnuityPayment) {
  s21::Credit credit;
  double credit_sum = 120000;
  double credit_time = 12;
  double percent = 10;
  int type_payment = 0;
  s21::Credit::PaymentOutput output;

  credit.calculate_credit(credit_sum, credit_time, percent, type_payment,
                          output);

  ASSERT_NEAR(output.total_payment, 126598.88, 1e-2);
  ASSERT_NEAR(output.first_payment, 10549.91, 1e-2);
  ASSERT_NEAR(output.last_payment, 10549.91, 1e-2);
  ASSERT_NEAR(output.overpayment, 6598.88, 1e-2);
}

TEST(DepositTest, TestWithoutOperations) {
  s21::Deposit deposit;

  double sum = 10000;
  double credit_time = 12;
  double interest_rate = 11;
  double tax_rate = 1;
  int periodicity_payments = 2;
  int capitalization = 2;
  int count_add = 2;
  double add = 0;
  int count_sub = 2;
  double sub = 0;
  s21::Deposit::DepositOutput output;

  deposit.deposit_calc(sum, credit_time, interest_rate, tax_rate,
                       periodicity_payments, capitalization, count_add, add,
                       count_sub, sub, output);

  ASSERT_NEAR(output.accrued_interest, 1084.93, 1e-2);
  ASSERT_NEAR(output.result, 11084.93, 1e-2);
  ASSERT_NEAR(output.tax_with, 0.00, 1e-2);
}

TEST(DepositTest, TestWithCapitalisation) {
  s21::Deposit deposit;

  double sum = 10000;
  double credit_time = 12;
  double interest_rate = 11;
  double tax_rate = 1;
  int periodicity_payments = 2;
  int capitalization = 1;
  int count_add = 2;
  double add = 0;
  int count_sub = 2;
  double sub = 0;
  s21::Deposit::DepositOutput output;

  deposit.deposit_calc(sum, credit_time, interest_rate, tax_rate,
                       periodicity_payments, capitalization, count_add, add,
                       count_sub, sub, output);

  ASSERT_NEAR(output.accrued_interest, 1140.54, 1e-2);
  ASSERT_NEAR(output.result, 11140.54, 1e-2);
  ASSERT_NEAR(output.tax_with, 0.00, 1e-2);
}

TEST(DepositTest, TestWithAddOnceMonth) {
  s21::Deposit deposit;

  double sum = 10000;
  double credit_time = 12;
  double interest_rate = 11;
  double tax_rate = 1;
  int periodicity_payments = 2;
  int capitalization = 2;
  int count_add = 1;
  double add = 1000;
  int count_sub = 2;
  double sub = 0;
  s21::Deposit::DepositOutput output;

  deposit.deposit_calc(sum, credit_time, interest_rate, tax_rate,
                       periodicity_payments, capitalization, count_add, add,
                       count_sub, sub, output);

  ASSERT_NEAR(output.accrued_interest, 1790.14, 1e-2);
  ASSERT_NEAR(output.result, 23790.14, 1e-2);
  ASSERT_NEAR(output.tax_with, 0.00, 1e-2);
}

TEST(DepositTest, TestWithSubOnceMonth) {
  s21::Deposit deposit;

  double sum = 10000;
  double credit_time = 12;
  double interest_rate = 11;
  double tax_rate = 1;
  int periodicity_payments = 2;
  int capitalization = 2;
  int count_add = 2;
  double add = 0;
  int count_sub = 1;
  double sub = 100;
  s21::Deposit::DepositOutput output;

  deposit.deposit_calc(sum, credit_time, interest_rate, tax_rate,
                       periodicity_payments, capitalization, count_add, add,
                       count_sub, sub, output);

  ASSERT_NEAR(output.accrued_interest, 1014.41, 1e-2);
  ASSERT_NEAR(output.result, 9814.41, 1e-2);
  ASSERT_NEAR(output.tax_with, 0.00, 1e-2);
}
