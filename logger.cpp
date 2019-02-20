#include "logger.h"

Logger::Logger()
{

}

Logger::Logger(QTextBrowser *output)
{
    _output = output;
}

bool Logger::log(QString message)
{
    _output->setText(message);
    return true;
}

bool Logger::log(QFile *file, QString message)
{
    if (file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(file);
        stream << message;
        stream << endl;
        file->close();
        return true;
    }
    return false;
}

bool Logger::log(QString fileName, QString message)
{
    QFile file(fileName);
    if (this->log(&file, message))
    {
        //_output->setText("Log written to file: " + fileName);
        return true;
    }
    return false;
}
