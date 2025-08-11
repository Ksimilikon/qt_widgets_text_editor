#include "styleviewwidget.h"

#include <QStackedWidget>
#include "styleform.h"
#include "mainlayout.h"

#include <QDebug>

StyleViewWidget::StyleViewWidget(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_styleVisual = new QTextBrowser;
    QPushButton *btnNew = new QPushButton("ADD/CHANGE");
    // btnNew->setMaximumSize({50, 25});
    m_layout->addWidget(btnNew);
    m_layout->addWidget(m_styleVisual);

    update();

    connect(btnNew, &QPushButton::clicked, this, &StyleViewWidget::slotSwitchFormStyle);
}
void StyleViewWidget::addElement(QPushButton &btn){
    m_layout->addWidget(&btn);
}
void StyleViewWidget::slotSwitchFormStyle(){
    emit signalSwitchStyleForm();
}
void StyleViewWidget::updateText(){
    m_styleVisual->setHtml(StyleClass::getHtml());
}
