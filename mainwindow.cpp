#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    m_mainWidget = new MainLayout(this);
    setCentralWidget(m_mainWidget);
}
