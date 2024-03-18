#ifndef MODELDEPOSIT_H
#define MODELDEPOSIT_H

#include <cmath>
#include <iostream>

namespace s21 {

class Deposit {
 public:
  struct DepositOutput {
    double result;            // сумма вклада с процентами
    double tax_with;          // - удержано налогов
    double accrued_interest;  // - начислено процентов
  };

  Deposit() {}
  void deposit_calc(double summ, double n, double interest_rate,
                    double tax_rate, int periodicity_payments,
                    int capitalization, int count_add, double add,
                    int count_sub, double sub, DepositOutput &output);
};
}  // namespace s21

#endif  // MODELDEPOSIT_H