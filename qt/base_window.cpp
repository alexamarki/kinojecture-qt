#include "base_window.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ui::MainWindow w;
    w.show();
    return a.exec();
}