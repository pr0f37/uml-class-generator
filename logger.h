#ifndef LOGGER_H
#define LOGGER_H
#include <QTextBrowser>
#include <QFile>
#include <QTextStream>

class Logger
{
public:
    Logger();
    Logger(QTextBrowser*);
    bool log(QString);
    bool log(QString, QString);
    bool log(QFile*, QString);
private:
    QTextBrowser* _output;

};

#endif // LOGGER_H
