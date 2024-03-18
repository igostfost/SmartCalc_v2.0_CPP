#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "../model/ModelCalculator.h"
#include "../model/ModelCredit.h"
#include "../model/ModelDeposit.h"

namespace s21 {
class CalcController {
 public:
  CalcController() = default;
  double calculateExpression(const std::string &expression);
  void calculateCredit(double credit_sum, double credit_time, double percent,
                       int type_payment, Credit::PaymentOutput &output);
  void calculateDeposit(double summ, double n, double interest_rate,
                        double tax_rate, int periodicity_payments,
                        int capitalization, int count_add, double add,
                        int count_sub, double sub,
                        Deposit::DepositOutput &output);

 private:
  ModelCalculator model_;
  Credit credit_;
  Deposit deposit_;
};
}  // namespace s21

#endif