#include "styleform.h"

#include <QString>
#include <QPushButton>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QMessageBox>
#include <QString>
#include "../../styleclass.h"


StyleForm::StyleForm(QWidget *parent)
    : QWidget(parent)
{
    QRegularExpression regcheck("#[0-9A-Fa-f]{6}");
    QRegularExpressionValidator* colorValidator = new QRegularExpressionValidator(regcheck, this);

    m_layout = new QFormLayout(this);
    m_nameStyle = new QComboBox();
    m_nameStyle->setEditable(true);
    QHash<QString, StyleProperties> styles = StyleClass::getStyles();
    for(QHash<QString, StyleProperties>::iterator iter = styles.begin();iter!=styles.end();++iter){
        m_nameStyle->addItem(iter.key());
    }

    m_textColor = new QLineEdit();
    m_textColor->setText("#000000");
    m_textColor->setValidator(colorValidator);

    m_bgColor = new QLineEdit();
    m_bgColor->setText("#ff000000");
    m_bgColor->setValidator(new QRegularExpressionValidator(QRegularExpression("#[0-9A-Fa-f]{8}")));

    m_fontSize = new QDoubleSpinBox();
    m_fontSize->setDecimals(1);
    m_fontSize->setSingleStep(1);
    m_fontSize->setValue(14);

    m_lineHeight = new QDoubleSpinBox();
    m_lineHeight->setDecimals(1);
    m_lineHeight->setSingleStep(0.5);
    m_lineHeight->setValue(1);

    m_fontFamily = new QFontComboBox();
    m_fontFamily->setMaxVisibleItems(10);

    m_aligmentH = new QComboBox();
    m_aligmentH->addItem("left");
    m_aligmentH->addItem("right");
    m_aligmentH->addItem("center");
    m_aligmentH->addItem("justify");
    QPushButton* submit = new QPushButton("Submit");

    m_layout->addRow("name", m_nameStyle);
    m_layout->addRow("font-color", m_textColor);
    m_layout->addRow("background-color", m_bgColor);
    m_layout->addRow("font-size", m_fontSize);
    m_layout->addRow("line-height", m_lineHeight);
    m_layout->addRow("font-family", m_fontFamily);
    m_layout->addRow("aligment-horizontal", m_aligmentH);
    m_layout->addWidget(submit);

    connect(submit, &QPushButton::clicked, this, &StyleForm::slotSwitchMain);
    connect(m_nameStyle, &QComboBox::currentTextChanged, this, &StyleForm::setProperties);

}
void StyleForm::setProperties(){
    //general
    m_preloadStyle = m_nameStyle->currentText();
    StyleProperties props = StyleClass::getStyle(m_preloadStyle);
    m_textColor->setText(props.textColor.name(QColor::HexRgb));
    m_bgColor->setText(props.bgColor.name(QColor::HexArgb));
    m_fontSize->setValue(props.fontSize);
    m_lineHeight->setValue(props.lineHeight);
    m_fontFamily->setCurrentFont(QFont(props.fontName));
    switch (props.aligment) {
    case Qt::AlignLeft:
        m_aligmentH->setCurrentIndex(0);
        break;
    case Qt::AlignRight:
        m_aligmentH->setCurrentIndex(1);
        break;
    case Qt::AlignCenter:
        m_aligmentH->setCurrentIndex(2);
        break;
    case Qt::AlignJustify:
        m_aligmentH->setCurrentIndex(3);
        break;
    default:
        m_aligmentH->setCurrentIndex(0);
        break;
    }
}

void StyleForm::slotSwitchMain(){
    if(m_nameStyle->currentText().trimmed().isEmpty()){
        QMessageBox::warning(this, "Error", "name is empty");
        return;
    }
    if(m_textColor->text().length() < 6){
        QMessageBox::warning(this, "Error", "text color is not complete");
        return;
    }
    if(m_bgColor->text().length() < 8){
        QMessageBox::warning(this, "Error", "background color is not complete");
        return;
    }

    QColor bgColor(m_bgColor->text());

    Qt::Alignment aligment;
    switch (m_aligmentH->currentIndex()) {
    case 0:
        aligment=Qt::AlignLeft;
        break;
    case 1:
        aligment=Qt::AlignRight;
        break;
    case 2:
        aligment=Qt::AlignCenter;
        break;
    case 3:
        aligment=Qt::AlignJustify;
        break;
    default:
        aligment=Qt::AlignLeft;
        break;
    }
    StyleProperties props = {
        m_textColor->text(),
        bgColor,
        float(m_fontSize->value()),
        float(m_lineHeight->value()),
        m_fontFamily->currentFont().family(),
        aligment
    };
    StyleClass::addStyle(m_nameStyle->currentText().trimmed(), props);
    m_nameStyle->clearEditText();
    m_nameStyle->clear();
    emit signalSwitchToMain();
}
void StyleForm::updateData(){
    QHash<QString, StyleProperties> styles = StyleClass::getStyles();
    for(QHash<QString, StyleProperties>::iterator iter = styles.begin();iter!=styles.end();++iter){
        m_nameStyle->addItem(iter.key());
    }
}
