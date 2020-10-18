#include "Windows.h"
#include "stdio.h"
#include "wincrypt.h"
#include "iostream"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
