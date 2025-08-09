#include "preprocessor.h"

QString preprocessor::applyVars(const QString& text, const QHash<QString, QString> &vars){
    QString result = "";
    bool escapeMode = false;
    for (int i=0; i<text.length();i++){
        QChar ch = text[i];
        if(escapeMode){
            if(ch != '%'){
                result.append('\\');
            }
            result.append(ch);
            escapeMode = false;
            continue;
        }
        if(ch == '\\'){
            escapeMode = true;
        }
        else if(ch == '%'){
            QString varName = "";
            if(i<text.length()){
                int j = i+1;
                while(j<text.length()){
                    const QChar nextCh = text[j];
                    if(!(nextCh == " " || nextCh.category() == QChar::Other_Control
                          || nextCh.category() == QChar::Punctuation_Other)){
                        varName.append(nextCh);
                        j++;
                    }
                    else{
                        break;
                    }
                }
                if(!varName.isEmpty() && vars.contains(varName)){
                    result.append(vars.value(varName));
                    //skip var chars
                    i=j-1;
                }
                else{
                    result.append('%');
                    result.append(varName);
                    i=j-1;
                }
            }
        }
        else{
            result.append(ch);
        }

        if(escapeMode){
            result.append('\\');
        }
    }
    return result;
}
QString preprocessor::applyStyleHtml(const QString& text){
    QString result;
    QString css = StyleClass::getStyleSheet();
    result.reserve(300+css.length());
    result.append("<!DOCTYPE html>");
    result.append("<head>");
    result.append("<meta charset=\"UTF-8\">");
    result.append("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    result.append("<title>Document</title>");
    result.append("<style>"+css+"</style");
    result.append("</head>");
    result.append("<body>");
    QString currentStyleName = "def";
    QStringList paragraphs = text.split('\n');
    // std::vector<TextParagraph> paragraphsStructed;
    foreach (QString p, paragraphs) {
        TextParagraph paragraph;

        //find style
        QString textProcessed;
        int length = p.length();
        bool escapeMode = false;
        for (int i = 0; i < length; ) {
            QChar ch = p[i];
            if (escapeMode) {
                textProcessed.append(ch);
                escapeMode = false;
                i++;
            } else if (ch == '\\') {
                escapeMode = true;
                i++;
            } else if (i + 1 < length && ch == '!' && p[i+1] == '!') {
                int j = i + 2;
                int start = j;
                while (j < length && (p[j].isLetterOrNumber() || p[j] == '_') && p[j]!='-') {
                    j++;
                }
                if (j < length && p[j] == '-' && j > start) {
                    currentStyleName = p.mid(start, j - start);
                    TextSegment *sgmt = new TextSegment(textProcessed, currentStyleName);
                    paragraph.addSegment(sgmt);
                    textProcessed = "";
                    i = j + 1;
                } else {
                    textProcessed.append("!!");
                    i += 2;
                }
            } else {
                textProcessed.append(p[i]);
                i++;
            }
        }

        if (escapeMode) {
            textProcessed.append('\\');
        }
        TextSegment *sgmt = new TextSegment(textProcessed, currentStyleName);
        paragraph.addSegment(sgmt);
        // paragraphsStructed.push_back(paragraph);

        result.append(paragraph.getHtml());
    }
    result.append("</body></html>");
    return result;
}

QString preprocessor::preprocessToHtml(const QString& text, const QHash<QString, QString>& vars){
    QString result = applyVars(text, vars);
    result = applyStyleHtml(result);
    return result;
}
