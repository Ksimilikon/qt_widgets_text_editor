#include "mainlayout.h"
// #define DEBUG

#include <QDebug>
#include <QStackedWidget>
#include <QTimer>
#include "styleform.h"

QHash<QString, QString> globalTextVars;

MainLayout::MainLayout(QWidget *parent)
    : QWidget(parent)
{
    m_fullPath = new QLabel("none");
    m_fullPath->setMaximumSize(QWIDGETSIZE_MAX, 20);
    m_fullPath->setAlignment(Qt::AlignCenter);

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

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_fullPath);
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
void MainLayout::setFullPath(const QString& path){
    m_fullPath->setText(path);
}
void MainLayout::keyPressEvent(QKeyEvent *event){
    if(event->modifiers()==Qt::ControlModifier
        && event->key() == Qt::Key_S){
        io::DataForSave data = {
            m_leftTextEdit->toPlainText(),
            globalTextVars,
            StyleClass::getStyles()
        };
        io::Saver* saver = new io::Saver(data);
        saver->save(m_fullPath->text());
    }
}
void MainLayout::setLoadedData(const io::DataForSave& data){
    //vars
    globalTextVars = data.vars;
    qDebug() << globalTextVars;
    qDebug() << data.vars.size() << "size";
    QString varsText;
    for(QHash<QString, QString>::const_iterator iter = data.vars.constBegin();iter!=data.vars.constEnd();iter++){
        varsText.append(iter.key()+"="+iter.value()+"\n");
    }
    m_leftVars->setPlainText(varsText);

    //text
    m_leftTextEdit->setPlainText(data.text);

    //styles
    StyleClass::setStyles(data.styles);
    m_rightStyleView->updateText();

    slotTextProcessed();
}
