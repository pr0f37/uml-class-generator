#ifndef ACLASS_H
#define ACLASS_H
#include <QTextStream>
#include "attribute.h"
#include "method.h"

class AClass
{
public:
    AClass();
    AClass(const AClass&);
    ~AClass();
    QList<QString> _ancestors;
    QList<QString> _nestedclasses;
    QList<QString> _nests;
    QList<Attribute*> _attributes;
    QList<Method*> _methods;
    QString _file;
    QString _name;
    QString _protection;
};

#endif // ACLASS_H
