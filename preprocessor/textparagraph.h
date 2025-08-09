#ifndef TEXTPARAGRAPH_H
#define TEXTPARAGRAPH_H

#include <QString>
#include "textsegment.h"

class TextParagraph
{
public:
    TextParagraph();
    void addSegment(TextSegment* sgmt);
    QString getHtml();
private:
    std::vector<TextSegment> segments;
};

#endif // TEXTPARAGRAPH_H
