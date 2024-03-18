#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "../controller/CalcController.h"

namespace Ui {
class creditWindow;
}

class creditWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit creditWindow(QWidget *parent = nullptr);
  ~creditWindow();

 private slots:
  void on_pushButton_back_clicked();

  void on_pushButton_clear_clicked();

  void on_pushButton_calk_res_clicked();

 private:
  Ui::creditWindow *ui;
  s21::CalcController controller;
};

#endif  // CREDITWINDOW_H
