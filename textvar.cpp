#include "textvar.h"

TextVar::TextVar(const QString &name, const QString &value) {
    this->name = new QString(name);
    this->value = new QString(value);
}
QString TextVar::getValue(){
    return *value;
}
QString TextVar::getName(){
    return *name;
}
