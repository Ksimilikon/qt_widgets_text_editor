#include "namefileform.h"

#include <QFormLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFileInfo>
#include <QLabel>
#include <QDir>


NameFileForm::NameFileForm(QWidget *parent)
    : QWidget{parent}
{

    QFormLayout* layout = new QFormLayout(this);
    QLabel* label = new QLabel;
    label->setText("Current relative path: "+QDir::currentPath());

    m_lineEdit = new QLineEdit;
    QPushButton* submit = new QPushButton("Submit");

    layout->addWidget(label);
    layout->addRow("Full/relative path", m_lineEdit);
    layout->addWidget(submit);

    connect(submit, &QPushButton::clicked, this, &NameFileForm::slotSubmit);
}

void NameFileForm::slotSubmit(){
    QString path = m_lineEdit->text().trimmed();
    if(path.isEmpty()){
        QMessageBox::warning(this, "error", "Field is empty");
        return;
    }
    if (path.contains(QRegularExpression(R"([<>:"|?*\x00-\x1F])"))) {
        QMessageBox::warning(this, "error", "Forbidden chars for path");
        return;
    }

    path+=".rwx";
    QFileInfo fileInfo(path);
    if(fileInfo.isAbsolute()){
        emit signalSwitchToMain(path);
        return;
    }
    else{
        //relative path
        QDir dir(QDir::currentPath());
        path = dir.absoluteFilePath(path);
        emit signalSwitchToMain(path);
        return;
    }
}
