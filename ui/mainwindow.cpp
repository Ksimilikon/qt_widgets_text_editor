#include "mainwindow.h"

#include <QVBoxLayout>
#include <QCoreApplication>
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include "styleviewwidget.h"
#include "forms/namefileform.h"

MainWindow::MainWindow(const QApplication* app, QWidget *parent)
    : QMainWindow(parent){
    m_widgetsStack = new QStackedWidget;
    MainLayout* mainLayout = new MainLayout(this);
    StyleForm* formAddStyle = new StyleForm(this);
    NameFileForm* nameFileForm = new NameFileForm(this);
    setCentralWidget(m_widgetsStack);

    m_widgetsStack->addWidget(mainLayout);
    m_widgetsStack->addWidget(formAddStyle);
    m_widgetsStack->addWidget(nameFileForm);

    connect(mainLayout->getStyleView(), &StyleViewWidget::signalSwitchStyleForm, this, &MainWindow::slotHandleSwitchStyleView);
    connect(formAddStyle, &StyleForm::signalSwitchToMain, this, &MainWindow::slotHandleSwitchMain);
    connect(nameFileForm, &NameFileForm::signalSwitchToMain, this, &MainWindow::slotHandleNameFileForm);

    if(app->arguments().count() > 1){
        QString arg = app->arguments().at(1);
        QDir dir(QCoreApplication::applicationDirPath());
        QString path = dir.absoluteFilePath(arg);
        if(dir.exists() && QFileInfo::exists(path)){
            mainLayout->setFullPath(path);
            mainLayout->setLoadedData(io::Saver::load(path));
        }
        else{
            m_widgetsStack->setCurrentIndex(2);
        }
    }
    else{
        m_widgetsStack->setCurrentIndex(2);
    }
}
void MainWindow::slotHandleSwitchStyleView(){
    StyleForm* form = qobject_cast<StyleForm*>(m_widgetsStack->widget(1));
    if(form){
        form->updateData();
        m_widgetsStack->setCurrentIndex(1);
    }
}
void MainWindow::slotHandleSwitchMain(){
    MainLayout* main = qobject_cast<MainLayout*>(m_widgetsStack->widget(0));
    if(main){
        main->getStyleView()->updateText();
        m_widgetsStack->setCurrentIndex(0);
    }
}
void MainWindow::slotHandleNameFileForm(const QString& path){
    MainLayout* main = qobject_cast<MainLayout*>(m_widgetsStack->widget(0));
    if(main){
        main->setFullPath(path);
        m_widgetsStack->setCurrentIndex(0);
    }
}
