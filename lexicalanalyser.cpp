#include "lexicalanalyser.h"

const QString LexicalAnalyser::_keySymbols[] =
{
    "include", "define", "ifndef", "endif", "using"
};

LexicalAnalyser::LexicalAnalyser()
{
}

LexicalAnalyser::LexicalAnalyser(QString fileName, QList<QString> *list) : Analyser(fileName, list)
{
}

bool LexicalAnalyser::analyse(QFile *file, int * counter)
{
    if (file->open(QIODevice::ReadOnly))
    {
        QChar symbol;
        char symbolRead;
        QString word;
        int symbolCounter = 0;
        int state  = 0;
        while(state != 9999)
        {
            symbolCounter++;
            if(file->getChar(&symbolRead))
            {
                symbol = (QChar) symbolRead;
                switch (state)
                {
                case 0: // start symbol
                    if (symbol == '#') state = 2;
                    else if ((symbol.isLetter() || symbol == '_') && symbolRead != '\n' && symbolRead != '\r' && symbolRead != '\t')
                    {
                        word.clear();
                        word += symbol;
                        state = 3;
                    }
                    else if (symbol.isNumber())
                    {
                        word.clear();
                        word += symbol;
                        state = 4;
                    }
                    else if (symbol == '-' || symbol == '+' || symbol == '*' || symbol == '/' || symbol == '<' || symbol == '>' || symbol == ':' || symbol == '=' || symbol == '!')
                    {
                        word.clear();
                        word += symbol;
                        state = 11;

                    }
                    else if ( symbol == '~' || symbol == '{' || symbol == '}' || symbol == '[' || symbol == ']' || symbol == '(' || symbol == ')' || symbol == '"' || symbol == '&' || symbol == '\'' || symbol == '|'
                              || symbol == '&')
                    {
                        log("symbol:" + QString(symbol));
                        _list->push_back(QString(symbol));
                        state = 0;

                    }
                    else if (symbol == ';' || symbol == ',')
                    {
                        log("separator:" + QString(symbol));
                        _list->push_back( QString(symbol));
                        state = 0;
                    }
                    else if (symbol.isSpace()) state = 0;
                    else state = 999;
                    break;
                case 1: // comment 1st state
                    if (symbol == '/') state = 5;
                    else if (symbol == '*') state = 6;
                    else
                    {
                        file->ungetChar(symbolRead);
                        symbolCounter--;
                        state = 0;
                    }
                    break;
                case 2:
                    if (symbol.isLetter()) word += symbol;
                    else if (symbol.isSpace())
                    {
                        for (int i = 0; i < _keySymbols->size(); i++)
                        {
                            if (_keySymbols[i] == word)
                            {
                                state = i*10 + 20;
                                word.clear(); // makes the word clear
                                break;
                            }
                            else state = 999; // error symbol not recognised
                        }
                    }
                    else state = 999; // error, there should be only letters after "#" character
                    break;
                case 3: // letter
                    if (symbol.isLetterOrNumber() || symbol == '_' ) word += symbol;
                    else if (symbol.isSpace()) state = 8;
                    else if (symbol == ';' || symbol == ',')
                    {
                        log("word:" + word);
                        _list->push_back("word:" + word);
                        word.clear();
                        log("separator:" + QString(symbol));
                        _list->push_back( QString(symbol));
                        state = 0;
                    }
                    else if (symbol == '-' || symbol == '+' || symbol == '*' || symbol == '/' || symbol == '<' || symbol == '>' || symbol == ':')
                    {
                        file->ungetChar(symbolRead);
                        symbolCounter--;
                        state = 8;
                    }
                    else if (symbol == '{' || symbol == '}' || symbol == '[' || symbol == ']' || symbol == '('
                             || symbol == ')' || symbol == '<' || symbol == '>' || symbol == '"' || symbol == '&'
                             || symbol == '*' || symbol == ',')
                    {
                        log("word:" + word);
                        _list->push_back("word:" + word);
                        word.clear();
                        log("symbol:" + QString(symbol));
                        _list->push_back(QString(symbol));
                        state = 0;
                    }
                    else state = 999; // error, type and name identifiers can only contain letters, numbers and "_" sign
                    break;
                case 4: // number
                    if (symbol.isNumber()) word += symbol;
                    else if (symbol == '.')
                    {
                        word += symbol;
                        state = 9;
                    }
                    else if (symbol.isSpace()) state = 10; // number
                    else if (symbol == ';')
                    {
                        log("number:" + word);
                        _list->push_back("number:" + word);
                        word.clear();
                        log("separator:" + QString(symbol));
                        _list->push_back( QString(symbol));
                        state = 0;
                    }
                    else if (symbol == ']' || symbol == ')')
                    {
                        log("number:" + word);
                        _list->push_back("number:" + word);
                        word.clear();
                        log("symbol:" + QString(symbol));
                        _list->push_back(QString(symbol));
                        state = 0;
                    }
                    else if (!symbol.isLetter() && symbol.isPrint()) state = 11; // operator
                    else state = 999;
                    break;
                case 5: // // comment
                    if (!symbol.isPrint()) state = 0; // read symbols until symbol == eol.
                    break;
                case 6: // /*...*/ comment
                    if (symbol == '*') state = 7;
                    break;
                case 7: // ending /*...*/ comment
                    if (symbol == '/') state = 0;
                    else state = 6;
                    break;
                case 8: // some word
                    log("word:" + word);
                    _list->push_back("word:" + word);
                    word.clear();
                    file->ungetChar(symbolRead);
                    symbolCounter--;
                    state = 0;
                    break;
                case 9: // number after .
                    if (symbol.isNumber()) word += symbol;
                    else if (symbol.isSpace()) state = 10;
                    else if (symbol == ';')
                    {
                        log("number:" + word);
                        _list->push_back("number:" + word);
                        word.clear();
                        log("separator:" + QString(symbol));
                        _list->push_back( QString(symbol));
                        state = 0;
                    }
                    else if (!symbol.isLetter() && symbol.isPrint()) state = 11; // operator
                    else state = 999;
                    break;
                case 10: // some number
                    log("number:" + word);
                    _list->push_back("number" + word);
                    word.clear();
                    file->ungetChar(symbolRead);
                    symbolCounter--;
                    state = 0;
                    break;
                case 11: // operator
                    if (word == "/" && (symbol == '/' || symbol == '*')) // operator seems to be a comment
                    {
                        file->ungetChar(symbolRead);
                        symbolCounter--;
                        word.clear();
                        state = 1;
                    }
                    else if (symbol.isLetterOrNumber() || symbol.isSpace() || symbol == '_')
                    {
                        log("symbol:" + word);
                        _list->push_back(word);
                        file->ungetChar(symbolRead);
                        symbolCounter--;
                        word.clear();
                        state = 0;
                    }
                    else if ((word == "!" && symbol == '=') || (word == "-" && symbol =='>') || (word == "=" && symbol == '=') || (word == "<" && (symbol == '=' )) || (word == ">" && (symbol == '=')))
                    {
                        word += symbol;
                        log("symbol:" + word);
                        _list->push_back(word);
                        word.clear();
                        state = 0;
                    }
                    else if ((word == "<" && symbol == '<' ) || (word == ">" && symbol == '>'))
                    {
                        log("symbol:" + word);
                        log("symbol:" + QString(symbol));
                        _list->push_back(word);
                        _list->push_back(symbol);
                        word.clear();
                        state = 0;
                    }
                    else if ((word == "+" && symbol == '+') || (word == "-" && symbol == '-'))
                    {
                        word += symbol;
                        log("symbol:" + word);
                        _list->push_back(word);
                        word.clear();
                        state = 12;
                    }
                    else if (word == ":" && symbol == ':')
                    {
                        word += symbol;
                        log("symbol:" + word);
                        _list->push_back(word);
                        word.clear();
                        state = 13;
                    }
                    else if ((word == ">" || word == ")") && symbol == '*')
                    {
                        log("symbol:" + word);
                        _list->push_back(word);
                        word.clear();
                        log("symbol:" + QString(symbol));
                        _list->push_back(QString(symbol));
                        state = 0;
                    }
                    else if (word == "*" && (symbol == ')' || symbol == '>'))
                    {
                        log("symbol:" + word);
                        _list->push_back(word);
                        word.clear();
                        log("symbol:" + QString(symbol));
                        _list->push_back(QString(symbol));
                        state = 0;
                    }
                    else if (word == "*" && symbol == ',')
                    {
                        log("symbol:" + word);
                        _list->push_back(word);
                        word.clear();
                        log("separator:" + QString(symbol));
                        _list->push_back( QString(symbol));
                        state = 0;
                    }
                    else if ((word == "*" || word == "&") && (symbol.isLetter() || symbol == '_' || symbol == '*' || symbol == '&'))
                    {
                        log("symbol:" + word);
                        _list->push_back(word);
                        word.clear();
                        file->ungetChar(symbolRead);
                        symbolCounter--;
                        state = 0;
                    }
                    else state = 999;
                    break;
                case 12:
                    if (symbol.isSpace()) state = 0;
                    else if (symbol == ';')
                    {
                        log("separator:" + QString(symbol));
                        _list->push_back( QString(symbol));
                        state = 0;
                    }
                    else if (symbol.isLetterOrNumber())
                    {
                        file->ungetChar(symbolRead);
                        symbolCounter--;
                        state = 0;
                    }
                    else state = 999;
                    break;
                case 13:
                    if (symbol.isSpace()) state = 0;
                    else if (symbol.isLetterOrNumber() || symbol == '_' || symbol == '*')
                    {
                        file->ungetChar(symbolRead);
                        symbolCounter--;
                        state = 0;
                    }
                    else state = 999;
                    break;
                case 20: // #include
                    if (symbol == '<') state = 21;
                    else if (symbol == '"') state = 22;
                    else state = 999; // error niedozwolony znak, oczekiwano < lub "
                    break;
                case 21: // #inlcude <
                    if (symbol == '>') state = 23;
                    else if(symbol.isLetterOrNumber()) word += symbol;
                    else state = 999; // error w includach mog¹ wystêpowaæ tylko litery i cyfry
                    break;
                case 22: // #inlcude "
                    if (symbol.isPunct())
                    {
                        word += symbol;
                        state = 24;
                    }
                    else if (symbol.isPrint()) word += symbol;
                    else state = 999; // error w includach "" nie mog¹ wystêpowaæ znaki niedrukowane
                    break;
                case 23: // #inlclude <...>
                    log("include:" + word);
                    word.clear();
                    state = 0;
                    break;
                case 24:
                    if (symbol == 'h')
                    {
                        word += symbol;
                        state = 25;
                    }
                    else state = 999; // error, biblioteki tylko z rozszerzeniem .h
                    break;
                case 25:
                    if (symbol == '"')
                    {
                        log("include:" + word);
                        word.clear();
                        state = 0;
                    }
                    else state = 999;
                    break;
                case 30: // #define
                    if (!symbol.isPrint()) state = 0; // read symbols until symbol == eol.
                    break;
                case 40: // #ifndef
                    if (!symbol.isPrint()) state = 0; // read symbols until symbol == eol.
                    break;
                case 50: // #endif
                    if (!symbol.isPrint()) state = 0; // read symbols until symbol == eol.
                    break;
                case 60: // using
                    if (symbol == ';') state = 0;
                    break;
                case 999:
                default:
                    QString message = "Error at symbol: " + QString(symbol);
                    message += " Symbol number: ";
                    message += QString::number(--symbolCounter);
                    *counter = symbolCounter;
                    log(message);
                    state = 9999;
                    return false;
                }
            }
            else
            {
                QString message = "File ended, number of symbols:" + QString::number(symbolCounter);
                log(message);
                state = 9999;
                file->close();
                return true;
            }
        }
    }
    else log("Error opening the file\n");
    return false;
}
