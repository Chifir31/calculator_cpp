#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath>

double operand1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(unary_clicked()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(unary_clicked()));
    connect(ui->pushButton_changeSign, SIGNAL(clicked()), this, SLOT(unary_clicked()));

   connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(actions_with_numbers()));
   connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(actions_with_numbers()));
   connect(ui->pushButton_multiplication, SIGNAL(clicked()), this, SLOT(actions_with_numbers()));
   connect(ui->pushButton_division, SIGNAL(clicked()), this, SLOT(actions_with_numbers()));
   connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(equal_clicked()));

   connect(ui->pushButton_clearAll, SIGNAL(clicked()), this, SLOT(clear_all()));

    ui->pushButton_division->setCheckable(true);
    ui->pushButton_multiplication->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_equal->setCheckable(true);

    setWindowTitle(tr("Калькулятор"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
   QPushButton *button = (QPushButton *) sender();
   double numbers;
   QString new_label;

   if(ui->display->text().contains(".") && button->text() == "0") {
       new_label = ui->display->text() + button->text();
   } else {
      numbers = (ui->display->text() + button->text()).toDouble();
      new_label = QString::number(numbers, 'g', 10);
    }
   if (ui->pushButton_equal->isChecked())
   {
       ui->display->clear();
       ui->pushButton_equal->setCheckable(false);
   }
    ui->display->setText(new_label);
}

void MainWindow::on_pushButton_point_clicked()
{
    if(!(ui->display->text().contains('.')))
    ui->display->setText(ui->display->text() + ".");
}

void MainWindow::unary_clicked()
{
   QPushButton *button = (QPushButton *) sender();
   double operand = (ui->display->text()).toDouble();
   QString new_label;


   if(button->text() == "sqrt") {
       if (operand < 0) {
           error();
           return;
       }
   operand = std::sqrt(operand);
   }

   if(button->text() == "%") {
   operand = operand * 0.01;
   }

   if(button->text() == "+/-") {
   operand = operand * (-1);
   }

   new_label = QString::number(operand, 'g', 10);

    ui->display->setText(new_label);
}

void MainWindow::actions_with_numbers()
{

   QPushButton *button = (QPushButton *) sender();
   result = (ui->display->text()).toDouble();

   ui->display->setText("");
   button->setChecked(true);

}

void MainWindow::equal_clicked()
{
    QString new_label;

    operand1 = ui->display->text().toDouble();

    if(ui->pushButton_plus->isChecked()) {
        result += operand1;
        ui->pushButton_plus->setChecked(false);

    }

    if(ui->pushButton_minus->isChecked()) {
        result -= operand1;
        ui->pushButton_minus->setChecked(false);
    }

    if(ui->pushButton_multiplication->isChecked()) {
        result *= operand1;
        ui->pushButton_multiplication->setChecked(false);
    }

    if(ui->pushButton_division->isChecked()) {
       if (operand1 == 0) {
           error();
           return;
       }
        result /= operand1;
       ui->pushButton_division->setChecked(false);
    }

    new_label = QString::number(result, 'g', 10);

     ui->display->setText(new_label);

}

void MainWindow::clear_all()
{
    ui->display->setText("0");
    result = 0;
    ui->pushButton_division->setCheckable(true);
    ui->pushButton_multiplication->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
}

void MainWindow::error()
{
    clear_all();
    ui->display->setText("#############");
}
