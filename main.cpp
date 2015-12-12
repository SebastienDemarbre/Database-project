#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <iostream>

#define q2c(string) string.toStdString()


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
