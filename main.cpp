#include "mainwindow.h"
#include "application.h"
#include <QApplication>
#include <Application.cpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;

    w.show();

    return a.exec();
}
