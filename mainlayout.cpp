#include "mainlayout.h"
#define DEBUG

#include <QDebug>
#include <QStackedWidget>
#include <QTimer>
#include "styleform.h"

QHash<QString, QString> globalTextVars;

MainLayout::MainLayout(QWidget *parent)
    : QWidget(parent)
{
    m_leftVars =       new QPlainTextEdit;
    m_leftTextEdit =   new QPlainTextEdit;
    m_rightTextEdit =  new QTextBrowser;
    m_rightStyleView = new StyleViewWidget;
    m_leftVars->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_leftTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_rightTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_rightStyleView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    QSplitter *leftSplitter = new QSplitter(Qt::Vertical);
    leftSplitter->addWidget(m_leftVars);
    leftSplitter->addWidget(m_leftTextEdit);\
    leftSplitter->setStretchFactor(0, 1);
    leftSplitter->setStretchFactor(1, 3);
    // leftSplitter->setChildrenCollapsible(false);


    QSplitter *rightSplitter = new QSplitter(Qt::Vertical);
    rightSplitter->addWidget(m_rightStyleView);
    rightSplitter->addWidget(m_rightTextEdit);
    rightSplitter->setStretchFactor(0, 1);
    rightSplitter->setStretchFactor(1, 3);

    splitter->addWidget(leftSplitter);
    splitter->addWidget(rightSplitter);
    splitter->setSizes({INT_MAX, INT_MAX});
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    QTimer::singleShot(10, this, [this](){
        m_leftTextEdit->setFocus();
    });

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(splitter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);


    //bindings
    connect(m_leftTextEdit, &QPlainTextEdit::textChanged,
            this, &MainLayout::slotTextProcessed);
    connect(m_leftVars, &QPlainTextEdit::textChanged,
            this, &MainLayout::slotTextVar);

}
void MainLayout::slotTextProcessed(){
    QString rawText = m_leftTextEdit->toPlainText();
    QString resText = textToProcessed(rawText);

    m_rightTextEdit->blockSignals(true);
    m_rightTextEdit->setHtml(resText);
    m_rightTextEdit->blockSignals(false);
}
void MainLayout::slotTextRaw(){
    QString resText = textToRaw(m_rightTextEdit->toPlainText());
    m_leftTextEdit->blockSignals(true);
    m_leftTextEdit->setPlainText(resText);
    m_leftTextEdit->blockSignals(false);
}
void MainLayout::slotTextVar(){
    globalTextVars = getTextVar(m_leftVars->toPlainText());;
}

QString MainLayout::textToProcessed(const QString& text){
    return preprocessor::preprocessToHtml(text, globalTextVars);
}
QString MainLayout::textToRaw(const QString& text){
    return text;
}

QHash<QString, QString> MainLayout::getTextVar(const QString& text){
    QHash<QString, QString> result;
    QStringList lines = text.split('\n');
    foreach (const QString& line, lines) {
        QStringList words = line.split('=');
        if(words.size() == 2){
            if(words[0] != "" && words[1] != ""){
                result.insert(words[0], words[1]);
            }
        }
    }
#ifdef DEBUG
    qDebug() << globalTextVars.keys() << " value " << globalTextVars.values();
#endif
    return result;
}

