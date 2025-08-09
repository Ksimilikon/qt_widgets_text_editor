#ifndef TEXTSEGMENT_H
#define TEXTSEGMENT_H
#include <QString>
class TextSegment
{
public:
    TextSegment(QString text, QString nameStyle);
    QString getHtml();
private:
    QString text;
    QString nameStyle;
};

#endif // TEXTSEGMENT_H
