#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Windows.h"
#include "stdio.h"
#include "wincrypt.h"
#include "iostream"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
