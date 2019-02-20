#include "analyser.h"
#include "mainwindow.h"
Analyser::Analyser()
{
}

Analyser::Analyser(QString fileName, QList<QString>* list)
{
    _logFile = fileName;
    _list = list;
}

void Analyser::setLogFile(QString fileName)
{
    _logFile = fileName;
}

void Analyser::log(QString message)
{
    _logger.log(_logFile, message);
}

