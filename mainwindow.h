#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "mainlayout.h"
#include "styleform.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void slotHandleSwitchStyleView();
    void slotHandleSwitchMain();

private:
    QStackedWidget *m_widgetsStack;
};

#endif // MAINWINDOW_H
