#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digits_numbers();
    void on_pushButton_point_clicked();
    void unary_clicked();
    void actions_with_numbers();
    void equal_clicked();
    void clear_all();

    void error();

private:
    double result;
    QString operation;
};
#endif // MAINWINDOW_H
