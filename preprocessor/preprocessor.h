#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <QString>
#include <QHash>

#include "../styleclass.h"
#include "textparagraph.h"

namespace preprocessor {
    QString preprocessToHtml(const QString& text, const QHash<QString, QString> &vars);
    QString applyVars(const QString& text, const QHash<QString, QString> &vars);
    QString applyStyleHtml(const QString& text);
}
#endif // PREPROCESSOR_H
