#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QSplitter>
#include <QTextBrowser>
#include "preprocessor/preprocessor.h"
#include "styleviewwidget.h"

class MainLayout : public QWidget
{
    Q_OBJECT
public:
    explicit MainLayout(QWidget *parent = nullptr);
    StyleViewWidget* getStyleView() const {return m_rightStyleView;}

private slots:
    void slotTextProcessed();
    void slotTextRaw();
    void slotTextVar();

private:
    QPlainTextEdit *m_leftVars;
    QPlainTextEdit *m_leftTextEdit;
    QTextBrowser *m_rightTextEdit;
    StyleViewWidget *m_rightStyleView;
    QSplitter *m_splitter;

    QString textToProcessed(const QString& text);
    QString textToRaw(const QString& text);
    QHash<QString, QString> getTextVar(const QString& text);

};

#endif // MAINLAYOUT_H
