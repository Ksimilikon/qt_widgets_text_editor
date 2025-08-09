#ifndef STYLECLASS_H
#define STYLECLASS_H

#include <QColor>
#include <QHash>

struct StyleProperties
{
    QColor          textColor;
    QColor          bgColor;
    float           fontSize;
    float           lineHeight;
    QString         fontName;
    Qt::Alignment   aligment;
};

class StyleClass
{
public:
    static void addStyle(QString nameClass, StyleProperties properties);
    static QString getStyleSheet();
    static QString getStyleCss(QString nameClass);
private:
    static QHash<QString, StyleProperties> styles;
};

#endif // STYLECLASS_H
