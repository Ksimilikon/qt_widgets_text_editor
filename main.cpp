#define DEBUG

// #include "widget.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    // w.show();
    MainWindow *w = new MainWindow(&a);
    w->setStyleSheet("* {background-color: #111; color: #fff}");
    w->show();

    return a.exec();
}
