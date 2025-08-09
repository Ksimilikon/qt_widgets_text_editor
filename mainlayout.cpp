#include "mainlayout.h"
#define DEBUG

#include <QDebug>

QHash<QString, QString> globalTextVars;

MainLayout::MainLayout(QWidget *parent)
    : QWidget(parent)
{
    m_leftTopTextEdit =     new QPlainTextEdit(this);
    m_leftBottomTextEdit =  new QPlainTextEdit(this);
    m_rightTextEdit =       new QTextBrowser(this);

    QWidget *leftWidget = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->addWidget(m_leftTopTextEdit, 1);
    leftLayout->addWidget(m_leftBottomTextEdit, 3);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(5);

    QWidget *rightWidget = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->addWidget(m_rightTextEdit);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    m_splitter = new QSplitter(Qt::Horizontal, this);
    m_splitter->addWidget(leftWidget);
    m_splitter->addWidget(rightWidget);
    m_splitter->setChildrenCollapsible(false);
    m_splitter->resize({400, 400});

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_splitter);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    m_leftBottomTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_rightTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_leftTopTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //bindings
    connect(m_leftBottomTextEdit, &QPlainTextEdit::textChanged,
            this, &MainLayout::slotTextProcessed);
    // connect(m_rightTextEdit, &QPlainTextEdit::textChanged,
    //         this, &MainLayout::slotTextRaw);
    connect(m_leftTopTextEdit, &QPlainTextEdit::textChanged,
            this, &MainLayout::slotTextVar);

}
void MainLayout::slotTextProcessed(){
    QString rawText = m_leftBottomTextEdit->toPlainText();
    QString resText = textToProcessed(rawText);

    m_rightTextEdit->blockSignals(true);
    m_rightTextEdit->setHtml(resText);
    m_rightTextEdit->blockSignals(false);
}
void MainLayout::slotTextRaw(){
    QString resText = textToRaw(m_rightTextEdit->toPlainText());
    m_leftBottomTextEdit->blockSignals(true);
    m_leftBottomTextEdit->setPlainText(resText);
    m_leftBottomTextEdit->blockSignals(false);
}
void MainLayout::slotTextVar(){
    globalTextVars = getTextVar(m_leftTopTextEdit->toPlainText());;
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

