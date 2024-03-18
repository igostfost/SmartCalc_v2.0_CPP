#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QMessageBox>

#include "../controller/CalcController.h"

namespace Ui {
class depositWindow;
}

class depositWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit depositWindow(QWidget *parent = nullptr);
  ~depositWindow();

 private slots:
  void on_pushButton_back_clicked();

  void on_pushButton_clear_clicked();

  void on_pushButton_calk_res_clicked();

 private:
  Ui::depositWindow *ui;
  s21::CalcController controller;
};

#endif  // DEPOSITWINDOW_H
