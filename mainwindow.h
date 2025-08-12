#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QApplication>
#include "mainlayout.h"
#include "styleform.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const QApplication* app, QWidget *parent = nullptr);

private slots:
    void slotHandleSwitchStyleView();
    void slotHandleSwitchMain();
    void slotHandleNameFileForm(const QString& path);

private:
    QStackedWidget *m_widgetsStack;
};

#endif // MAINWINDOW_H
