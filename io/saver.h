#ifndef SAVER_H
#define SAVER_H

#include <QString>
#include <QHash>
#include "../styleclass.h"

struct DataForSave{
    QString &text;
    QHash<QString, QString>& vars;
    QHash<QString, StyleProperties>& styles;
};

class Saver
{
public:
    Saver(DataForSave& data);
    void save(QString path, QString name);
    void load(QString fullPath);
};

#endif // SAVER_H
