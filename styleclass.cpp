#include "styleclass.h"

QHash<QString, StyleProperties> StyleClass::styles;

void StyleClass::addStyle(QString nameClass, StyleProperties properties){
    styles[nameClass] = properties;
}
void StyleClass::setStyles(const QHash<QString, StyleProperties>& styles){
    StyleClass::styles = styles;
}
QString StyleClass::getStyleSheet(){
    QString result = "*{margin:0;padding:0;}";
    for(QHash<QString, StyleProperties>::const_iterator iter = styles.constBegin();iter!=styles.constEnd();++iter){
        result.append(StyleClass::getStyleCss(iter.key()));
    }
    return result;
}

QString StyleClass::getStyleCss(QString name){
    QString result;
    StyleProperties p;
    if(!styles.contains(name)){
        p = {QColor::fromRgb(0, 0, 0), QColor::fromRgb(255, 255, 255), 14, 1, "Arial", Qt::AlignLeft};
    }else{
        p = styles[name];
    }
    result.append("."+name+"{");
    result.append("color:"+p.textColor.name(QColor::HexRgb)+";");
    result.append("background-color:"+p.bgColor.name(QColor::HexArgb)+";");
    if(p.fontSize == std::floor(p.fontSize)){
        result.append("font-size:"+QString::number(static_cast<int>(p.fontSize))+"px;");
    }
    else{
        result.append("font-size:"+QString::number(p.fontSize, 'f', 2)+"px;");
    }
    if(p.lineHeight == std::floor(p.lineHeight)){
        result.append("line-height:"+QString::number(static_cast<int>(p.lineHeight))+";");
    }
    else{
        result.append("line-height:"+QString::number(p.lineHeight, 'f', 2)+";");
    }
    result.append("font-family:\""+p.fontName+"\";");
    switch (p.aligment) {
    case Qt::AlignLeft:
        result.append("text-align:left;");
        break;
    case Qt::AlignRight:
        result.append("text-align:right;");
        break;
    case Qt::AlignJustify:
        result.append("text-align:justify;");
        break;
    case Qt::AlignCenter:
        result.append("text-align:center;");
        break;
    default:
        result.append("text-align:left;");
        break;
    }
    result.append("}");
    return result;
}

StyleProperties StyleClass::getDefaultStyle(){
    return StyleProperties{
        QColor::fromRgb(0, 0, 0),
        QColor::fromRgb(255, 255, 255),
        14,
        1,
        "Arial",
        Qt::AlignLeft,
    };
}

StyleProperties StyleClass::getStyle(QString nameStyle){
    if(StyleClass::styles.contains(nameStyle)){
        return styles[nameStyle];
    }
    else{
        return getDefaultStyle();
    }
}
QHash<QString, StyleProperties> StyleClass::getStyles(){
    return styles;
}
QString StyleClass::getHtml(){
    QString result;
    QString css = getStyleSheet();
    result.reserve(200+css.length());
    result.append("<!DOCTYPE html>");
    result.append("<head>");
    result.append("<meta charset=\"UTF-8\">");
    result.append("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    result.append("<title>Document</title>");
    result.append("<style>"+css+"</style");
    result.append("</head>");
    result.append("<body>");
    for(QHash<QString, StyleProperties>::const_iterator iter = styles.constBegin();iter!=styles.constEnd();++iter){
        result.append("<p class=\""+iter.key()+"\">");
        result.append(iter.key()+"</p>");
    }
    result.append("</body></html>");
    return result;
}
