#include "textsegment.h"

TextSegment::TextSegment(QString text, QString nameStyle){
    this->text=text;
    this->nameStyle=nameStyle;
}
QString TextSegment::getHtml(){
    return "<span class='"+nameStyle+"'>"+text+"</span>";
}
