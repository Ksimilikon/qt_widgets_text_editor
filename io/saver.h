#ifndef SAVER_H
#define SAVER_H

#include <QString>
#include <QHash>
#include "../styleclass.h"

namespace io {
struct DataForSave{
    QString text;
    QHash<QString, QString> vars;
    QHash<QString, StyleProperties> styles;
};

class Saver
{
public:
    Saver(DataForSave& data);
    void save(const QString &path);
    void load(const QString &fullPath);
private:
    DataForSave* m_data;
};
}


#endif // SAVER_H
