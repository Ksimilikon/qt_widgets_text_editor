#ifndef STYLEFORM_H
#define STYLEFORM_H

#include <QWidget>
// #include <QVBoxLayout>
#include <QValidator>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
// #include <QSlider>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFontComboBox>

class StyleForm : public QWidget
{
    Q_OBJECT
public:
    explicit StyleForm(QWidget *parent = nullptr);
    void updateData();

signals:
    void signalSwitchToMain();
    void signalUpdateStyles();
private slots:
    void slotSwitchMain();
    void setProperties();
private:
    QString m_preloadStyle;
    QComboBox *m_nameStyle;

    QFormLayout *m_layout;
    QLineEdit *m_textColor;
    QLineEdit *m_bgColor;
    QDoubleSpinBox *m_fontSize;
    QDoubleSpinBox *m_lineHeight;
    QFontComboBox *m_fontFamily;
    QComboBox *m_aligmentH;

};

#endif // STYLEFORM_H
