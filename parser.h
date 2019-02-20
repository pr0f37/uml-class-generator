#ifndef PARSER_H
#define PARSER_H
#include "analyser.h"
#include "aclass.h"
#include <QTextBrowser>
#include "method.h"

class Parser : Analyser
{
public:
    Parser();
    Parser(QString, QList<QString>*, QList<AClass*>*, QTextBrowser*);
    void analyse();
private:
    void error(QString);
    void S();
    void H(AClass*);
    void G(AClass*);
    void I(AClass*);
    void L(AClass*);
    void K(AClass*);
    void J(AClass*);
    void F(AClass*, Method*);
    void E(AClass*, Attribute*);
    void D(AClass*, Attribute*);
    void D(AClass*, Method*);
    void C(AClass*, Attribute*);
    void C(AClass*, Method*);
    void B(AClass*, Attribute*);
    void A(AClass*, Attribute*);
    void A(AClass*, Method*);

    bool findKeyWord(QString);
    void advance();
    QList<AClass*> *_classList;
    int _position;
    QTextBrowser* _output;
    static const QString _keyWords[];

};

#endif // PARSER_H
