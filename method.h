#ifndef METHOD_H
#define METHOD_H
#include "attribute.h"
#include <QTextStream>
class Method : public Attribute
{
public:
    Method();
    Method(const Method&);
    ~Method();
    QList<Attribute*> _attributes;
};

#endif // METHOD_H
