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
}
