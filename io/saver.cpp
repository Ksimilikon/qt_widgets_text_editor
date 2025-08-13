#include "saver.h"

#include <QHash>
#include <QFile>
#include <QTextStream>
#include <QDebug>

namespace io {
Saver::Saver(DataForSave& data){
    this->m_data = &data;
}
void Saver::save(const QString& path){
    QString styles;
    QString vars;
    QString text;

    styles.append("styles{\n");
    for(QHash<QString, StyleProperties>::const_iterator iter = m_data->styles.constBegin();iter!=m_data->styles.constEnd();++iter){
        styles.append(iter.key()+"(\n");
        styles.append("colorText="+iter.value().textColor.name(QColor::HexRgb)+"\n");
        styles.append("colorBg="+iter.value().bgColor.name(QColor::HexRgb)+"\n");
        styles.append("fontSize="+QString::number(iter.value().fontSize)+"\n");
        styles.append("lineHeight="+QString::number(iter.value().lineHeight)+"\n");
        styles.append("fontName="+iter.value().fontName+"\n");
        switch (iter.value().aligment) {
        case Qt::AlignLeft:
            styles.append("aligmentH=left\n");
            break;
        case Qt::AlignRight:
            styles.append("aligmentH=right\n");
            break;
        case Qt::AlignCenter:
            styles.append("aligmentH=center\n");
            break;
        case Qt::AlignJustify:
            styles.append("aligmentH=justify\n");
            break;
        default:
            styles.append("aligmentH=left\n");
            break;
        }
        styles.append(")\n");
    }
    styles.append("}\n");

    vars.append("vars{\n");
    for(QHash<QString, QString>::const_iterator iter = m_data->vars.constBegin();iter!=m_data->vars.constEnd();++iter){
        vars.append(iter.key()+"="+iter.value()+"\n");
    }
    vars.append("}\n");

    text.append("text{");
    text.append(m_data->text);
    text.append("}");

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error opening file:" << path << file.errorString();
        return;
    }
    QTextStream out(&file);
    out << styles;
    out << vars;
    out << text;

    file.close();
    qDebug() << "file save " << path;
}
DataForSave Saver::load(const QString &fullPath){
    QFile file(fullPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "error read file" << fullPath;
        return DataForSave{};
    }
    QString fileText = QString::fromUtf8(file.readAll());
    file.close();

    QString text = "";
    QHash<QString, QString> vars;
    QHash<QString, StyleProperties> styles;
    text = executeProps(fileText, "text");
    QString varsText = executeProps(fileText, "vars");
    QString stylesText = executeProps(fileText, "styles");

    QStringList varsStrokes = varsText.split('\n');
    foreach (QString str, varsStrokes) {
        QStringList words = str.split('=');
        if(words.length()==2){
            vars[words[0].trimmed()]=words[1];
        }
        else{
            continue;
        }
    }

    QString nameStyle = "";
    for(int i=0;i<stylesText.length();++i){

        QChar ch = stylesText[i];
        if(ch.isLetter()){
            nameStyle.append(ch);
        }
        if(ch=='(' && nameStyle!=""){
            int posStart = i;

            QColor textColor = QColor::fromRgb(0, 0, 0);
            QColor bgColor = QColor::fromRgb(255, 255, 255);
            float fontSize = float(14);
            float lineHeight = float(1);
            QString fontFamily = "Arial";
            Qt::Alignment aligment = Qt::AlignLeft;

            while(i<stylesText.length() && stylesText[i]!=')'){
                i++;
            }
            QStringList props = stylesText.mid(posStart, i).split('\n');
            foreach (QString p, props) {
                QStringList words = p.split('=');
                if(words.length()==2){
                    if(words[0]=="colorText"){
                        textColor=QColor(words[1]);
                    }
                    if(words[0]=="colorBg"){
                        bgColor=words[1];
                    }
                    if(words[0]=="fontSize"){
                        fontSize=words[1].toFloat();
                    }
                    if(words[0]=="lineHeight"){
                        lineHeight=words[1].toFloat();
                    }
                    if(words[0]=="fontName"){
                        fontFamily=words[1];
                    }
                    if(words[0]=="aligmentH"){
                        if(words[1]=="left"){
                            aligment=Qt::AlignLeft;
                        }
                        if(words[1]=="right"){
                            aligment=Qt::AlignRight;
                        }
                        if(words[1]=="center"){
                            aligment=Qt::AlignCenter;
                        }
                        if(words[1]=="justify"){
                            aligment=Qt::AlignJustify;
                        }
                    }
                }
                else{
                    continue;
                }
            }
            styles[nameStyle]=StyleProperties{
                textColor,
                bgColor,
                fontSize,
                lineHeight,
                fontFamily,
                aligment
            };
            nameStyle="";
        }
    }

    return DataForSave{text, vars, styles};
}

QString executeProps(const QString& text, QString&& nameProperty, QChar bracketStart, QChar bracketEnd){
    int pos = 0;
    int posStart = 0;
    qsizetype cap = 0;
    bool inBrackets = false;
    if((pos = text.indexOf(nameProperty)) != -1){
        for (int i = pos; i < text.length(); ++i) {
            if(text[i]==bracketStart && text.length() > (i+1)){
                posStart=i+1;
                inBrackets=true;
            }
            if(inBrackets && text[i]!=bracketEnd){
                cap++;
            }
            if(text[i]==bracketEnd){
                break;
            }
        }
        if(cap>0){
            cap--;
        }
    }
    if(posStart!=pos && cap > 0){
        return text.mid(posStart, cap);
    }

    return "";
}
}
