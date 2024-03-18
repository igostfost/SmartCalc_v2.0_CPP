#include "graphwindow.h"

#include <iostream>

#include "ui_graphwindow.h"

graphWindow::graphWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::graphWindow) {
  ui->setupUi(this);
  ui->widget->setBackground(QBrush(Qt::black));
  // Основные оси
  ui->widget->xAxis->setBasePen(QPen(Qt::white));
  ui->widget->yAxis->setBasePen(QPen(Qt::white));
  // Деления
  ui->widget->xAxis->setTickPen(QPen(Qt::white));
  ui->widget->yAxis->setTickPen(QPen(Qt::white));
  // Под-деления
  ui->widget->xAxis->setSubTickPen(QPen(Qt::white));
  ui->widget->yAxis->setSubTickPen(QPen(Qt::white));
  // Метки делений
  ui->widget->xAxis->setTickLabelColor(Qt::white);
  ui->widget->yAxis->setTickLabelColor(Qt::white);
  // Подписи к осям
  ui->widget->xAxis->setLabelColor(Qt::white);
  ui->widget->yAxis->setLabelColor(Qt::white);
}

graphWindow::~graphWindow() { delete ui; }

void graphWindow::on_pushButton_back_clicked() {
  this->close();
  emit MainWindow();
}

void graphWindow::pasteEquation(QString plotLine) {
  ui->lineEdit_equation->setText(plotLine);

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->replot();
}

void graphWindow::on_pushButton_create_clicked() {
  // Получаем границы по осям x и y из пользовательского интерфейса
  double xMax = ui->lineEdit_right_xZone->text().toDouble();
  double xMin = ui->lineEdit_left_xZone->text().toDouble();
  double yMax = ui->lineEdit_right_yZone->text().toDouble();
  double yMin = ui->lineEdit_left_yZone->text().toDouble();

  if ((xMax >= 1000000) || (xMin <= -1000000) || (yMax >= 1000000) ||
      (yMin <= -1000000)) {
    QMessageBox::critical(this, "Ошибка",
                          "Превышены максимальные области отображения");
    return;
  }
  // Количество точек, которые будут отрисованы на графике
  const int numPoints = 801;
  // Инициализируем векторы для хранения значений по осям x и y
  QVector<double> x(numPoints), y(numPoints);
  // Вычисляем шаг для оси x
  double step = (xMax - xMin) / numPoints;
  // Вычисляются значения для каждой точки на графике
  for (int i = 0; i < numPoints; ++i) {
    double xValue = xMin + i * step;  // Вычисляем значение x
    // qDebug() << "xValue[" << i << "]: " << xValue;
    x[i] = xValue;
    QString expression = ui->lineEdit_equation->text();
    // Заменяем "x" в нашем выражении на текущее значение xValue
    expression.replace("x", QString::number(xValue, 'g', 7));
    // std::string expressionStd = expression.toStdString();
    QByteArray ba = expression.toLatin1();
    char *line = ba.data();

    // Вычисляем значение y для каждого x с помощью нашей функции
    try {
      double yValue = controller.calculateExpression(line);
      // Устанавливаем порог, чтобы скрыть асимптоты
      if (yValue > 10 || yValue < -10) {
        yValue = qQNaN();  // Ставим значение "не число", чтобы оно не
                           // отображалось на графике
      }
      y[i] = yValue;
    } catch (const std::invalid_argument &e) {
      // В случае исключения, создаем QMessageBox и отображаем сообщение об
      // ошибке
      QMessageBox::critical(this, "Ошибка",
                            QString("Ошибка построения: %1").arg(e.what()));
      return;
    } catch (const std::runtime_error &e) {
      y[i] = qQNaN();
    }
  }

  // Создаем график и присваиваем ему данные:
  ui->widget->addGraph();
  QPen linePen(Qt::yellow);
  linePen.setWidth(2);
  ui->widget->graph(0)->setPen(linePen);
  ui->widget->graph(0)->setData(x, y);
  // Устанавливаем диапазоны для осей, чтобы отобразить все данные:
  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);
  // Перерисовываем график
  ui->widget->replot();
}
