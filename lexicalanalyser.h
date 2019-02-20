#ifndef LEXICALANALYSER_H
#define LEXICALANALYSER_H
#include "analyser.h"
class LexicalAnalyser : Analyser
{
public:
    LexicalAnalyser();
    LexicalAnalyser(QString, QList<QString>*);
    bool analyse(QFile*, int*);
private:
    static const QString _keySymbols[];
};

#endif // LEXICALANALYSER_H
