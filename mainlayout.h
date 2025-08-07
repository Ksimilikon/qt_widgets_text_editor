#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QtWidgets/QtWidgets>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QSplitter>

#include "textvar.h"

class MainLayout : public QWidget
{
    Q_OBJECT
public:
    explicit MainLayout(QWidget *parent = nullptr);

private slots:
    void slotTextProcessed();
    void slotTextRaw();
    void slotTextVar();

private:
    QPlainTextEdit *m_leftTopTextEdit;
    QPlainTextEdit *m_leftBottomTextEdit;
    QPlainTextEdit *m_rightTextEdit;
    QSplitter *m_splitter;

    QString textToProcessed(const QString& text);
    QString textToRaw(const QString& text);
    QHash<QString, QString> getTextVar(const QString& text);

};

#endif // MAINLAYOUT_H
