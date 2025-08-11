#ifndef STYLEVIEWWIDGET_H
#define STYLEVIEWWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextBrowser>

class StyleViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StyleViewWidget(QWidget *parent = nullptr);
    void addElement(QPushButton& btn);
    void updateText();

signals:
    void signalSwitchStyleForm();

private slots:
    void slotSwitchFormStyle();

private:
    QVBoxLayout *m_layout;
    QTextBrowser *m_styleVisual;
};

#endif // STYLEVIEWWIDGET_H
