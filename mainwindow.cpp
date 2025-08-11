#include "mainwindow.h"

#include <QVBoxLayout>
#include "styleviewwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    m_widgetsStack = new QStackedWidget;
    MainLayout* mainLayout = new MainLayout(this);
    StyleForm* formAddStyle = new StyleForm(this);
    setCentralWidget(m_widgetsStack);

    m_widgetsStack->addWidget(mainLayout);
    m_widgetsStack->addWidget(formAddStyle);

    connect(mainLayout->getStyleView(), &StyleViewWidget::signalSwitchStyleForm, this, &MainWindow::slotHandleSwitchStyleView);
    connect(formAddStyle, &StyleForm::signalSwitchToMain, this, &MainWindow::slotHandleSwitchMain);
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
