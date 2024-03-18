#ifndef MODEL_CREDIT
#define MODEL_CREDIT

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace s21 {

class Credit {
 public:
  struct PaymentOutput {
    double total_payment;
    double first_payment;
    double last_payment;
    double overpayment;
  };

  Credit() {}
  void calculate_credit(double credit_sum, double credit_time, double percent,
                        int type_payment, PaymentOutput &output);

 private:
};

}  // namespace s21

#endif  // MODEL_CREDIT
