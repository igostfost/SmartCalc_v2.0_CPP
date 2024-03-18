#include "CalcController.h"

double s21::CalcController::calculateExpression(const std::string &expression) {
  return model_.evaluateExpression(expression);
}

void s21::CalcController::calculateCredit(double credit_sum, double credit_time,
                                          double percent, int type_payment,
                                          s21::Credit::PaymentOutput &output) {
  // Вызываем метод calculate_credit из модели кредита
  credit_.calculate_credit(credit_sum, credit_time, percent, type_payment,
                           output);
}

void s21::CalcController::calculateDeposit(
    double summ, double n, double interest_rate, double tax_rate,
    int periodicity_payments, int capitalization, int count_add, double add,
    int count_sub, double sub, s21::Deposit::DepositOutput &output) {
  deposit_.deposit_calc(summ, n, interest_rate, tax_rate, periodicity_payments,
                        capitalization, count_add, add, count_sub, sub, output);
}
