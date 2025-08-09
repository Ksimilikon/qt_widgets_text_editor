#include "textparagraph.h"

TextParagraph::TextParagraph(){}
void TextParagraph::addSegment(TextSegment* sgmt){
    segments.push_back(*sgmt);
}
QString TextParagraph::getHtml(){
    QString result;
    result.append("<p>");
    for(int i=0;i<segments.size();i++){
        result.append(segments[i].getHtml());
    }
    result.append("</p>");

    return result;
}
