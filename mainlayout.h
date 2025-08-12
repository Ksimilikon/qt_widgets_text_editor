#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QSplitter>
#include <QTextBrowser>
#include <QKeyEvent>
#include "preprocessor/preprocessor.h"
#include "styleviewwidget.h"
#include "io/saver.h"

class MainLayout : public QWidget
{
    Q_OBJECT
public:
    explicit MainLayout(QWidget *parent = nullptr);
    StyleViewWidget* getStyleView() const {return m_rightStyleView;}
    void setFullPath(const QString& path);
    QString getFullPath(){m_fullPath->text();}

private slots:
    void slotTextProcessed();
    void slotTextRaw();
    void slotTextVar();

private:
    QLabel* m_fullPath;
    QPlainTextEdit *m_leftVars;
    QPlainTextEdit *m_leftTextEdit;
    QTextBrowser *m_rightTextEdit;
    StyleViewWidget *m_rightStyleView;
    QSplitter *m_splitter;

    QString textToProcessed(const QString& text);
    QString textToRaw(const QString& text);
    QHash<QString, QString> getTextVar(const QString& text);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINLAYOUT_H
