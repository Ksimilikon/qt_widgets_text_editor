#ifndef NAMEFILEFORM_H
#define NAMEFILEFORM_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QPushButton>

class NameFileForm : public QWidget
{
    Q_OBJECT
public:
    explicit NameFileForm(QWidget *parent = nullptr);
signals:
    void signalSwitchToMain(const QString& path);
private slots:
    void slotSubmit();
private:
    QLineEdit* m_lineEdit;
};

#endif // NAMEFILEFORM_H
