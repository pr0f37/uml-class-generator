#ifndef ANALYSER_H
#define ANALYSER_H
#include "logger.h"

class Analyser
{
public:
    Analyser();
    Analyser(QString, QList<QString>*);
    void setLogFile(QString);
    void log(QString);
protected:
    Logger _logger;
    QString _logFile;
    QList<QString>* _list;

};

#endif // ANALYSER_H
