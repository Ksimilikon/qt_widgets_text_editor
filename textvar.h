#ifndef TEXTVAR_H
#define TEXTVAR_H

#include <QString>

class TextVar
{
public:
    explicit TextVar(const QString &name, const QString &value);
    QString getName();
    QString getValue();
private:
    QString *name;
    QString *value;
};

#endif // TEXTVAR_H
