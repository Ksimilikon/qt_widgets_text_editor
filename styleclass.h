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
    static void setStyles(const QHash<QString, StyleProperties>&);
    static QString getHtml();
    static QString getStyleSheet();
    static QString getStyleCss(QString nameClass);
    static StyleProperties getStyle(QString name);
    static StyleProperties getDefaultStyle();
    static QHash<QString, StyleProperties> getStyles();
private:
    static QHash<QString, StyleProperties> styles;
};

#endif // STYLECLASS_H
