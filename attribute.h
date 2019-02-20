#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <QTextStream>
class Attribute
{
public:
    Attribute();
    Attribute(const Attribute&);
    ~Attribute();
    QString _type;
    QString _name;
    QList<QString> _keywords;
    QString _expression;
};

#endif // ATTRIBUTE_H
