#include "parser.h"
#include <QString>

const QString Parser::_keyWords[] =
{
    "include", "define", "ifndef", "endif", "using", "namespace", "int", "double",
    "short", "long", "bool", "char", "float", "string", "const", "volatile", "mutable", "static"
};

Parser::Parser()
{

}

Parser::Parser(QString fileName, QList<QString> *inList, QList<AClass*> *classList, QTextBrowser* output) : Analyser(fileName, inList)
{
    _classList = classList;
    _position = 0;
    _output = output;
}
void Parser::advance()
{
    _position++;
}

void Parser::analyse()
{
    while(_position < _list->size())
    {
        if (_list->at(_position).contains("word:"))
            S();
        advance();
    }
}

void Parser::error(QString msg)
{
    QString message = "At character (";
    message += QString::number(_position);
    message += "): \"";
    message += _list->at(_position);
    message.remove("word:");
    message += "\" occured. ";
    message += msg;
    log(message);
    _output->append(message);
}

bool Parser::findKeyWord(QString word)
{
    for (int i = 0; i < _keyWords->size(); i ++)
    {
        if (_keyWords[i] == word)
            return true;
    }
    return false;
}

void Parser::S()
{
    while (_position < _list->size())
    {
        if (_list->at(_position).contains("class"))
        {
            advance();
            AClass *myClass = new AClass();
            H(myClass);
        }
        else
        {
            error("Class definition expected.(S)");
            advance();
        }
    }
}

void Parser::H(AClass *tempClass)
{
    if(_list->at(_position).contains("word:"))
    {

        tempClass->_file = _logFile;
        tempClass->_file.chop(14);
        tempClass->_file += ".h";
        tempClass->_name = _list->at(_position);
        tempClass->_name.remove("word:");
        _classList->push_back(tempClass);
        advance();
        if (_list->at(_position) == ":") // class myclass : ancestor
        {
            advance();
            if(_list->at(_position).contains("word:"))
            {
                if (_list->at(_position).contains("public") || _list->at(_position).contains("private") || _list->at(_position).contains("protected")) // omits keyword
                    advance();
                while(!_list->at(_position).contains("{") && _position < _list->size())
                {
                    QString ancestor = _list->at(_position);
                    ancestor.remove("word:");
                    tempClass->_ancestors.push_back(ancestor);
                    advance();
                    if(_list->at(_position).contains(","))
                        advance();
                    else if (_list->at(_position).contains("{"))
                            error("ancestor identyfier expected. (H)");
                }
            }
            else error("class definition expected. (H)");
        }
        if (_list->at(_position).contains("{")) // class myclass {
        {
            advance();
            while(_position < _list->size()) // (H|G)*
            {
                if (_list->at(_position).contains("}") && _list->at(_position + 1).contains(";"))
                    break;
                if (_list->at(_position).contains("class")) // class myclass { H
                {
                    advance();
                    AClass *myClass = new AClass();
                    myClass->_nests.push_back(tempClass->_name);
                    if (_list->at(_position).contains("word:"))
                    {
                        QString nestedClassName = _list->at(_position);
                        nestedClassName.remove("word:");
                        tempClass->_nestedclasses.push_back(nestedClassName);
                    }
                    H(myClass);
                }
                else if (_list->at(_position).contains("~") || _list->at(_position).contains("word"))
                {
                    G(tempClass);
                }
            }
            if (_list->at(_position).contains("}") && _list->at(_position + 1).contains(";"))
            {
                advance();
                advance();
            }
            else
            {
                advance();
                error("\"}\" expected.(H)");
            }
        }
    }
}

void Parser::G(AClass* classPosition)
{
    if (_list->at(_position).contains("word") && _list->at(_position + 1) == ":")
        I(classPosition);
    else if (_list->at(_position).contains("~") || _list->at(_position).contains("word"))
        L(classPosition);
}

void Parser::I(AClass* classPosition)
{
    if (_list->at(_position).contains("word:") && _list->at(_position + 1) == ":")
    {
        QString msg = _list->at(_position);
        msg.remove("word:");
        classPosition->_protection = msg;
        classPosition->_protection.remove("word:");
        advance();
        advance();
    }
}

void Parser::L(AClass* classPosition)
{
    if (_list->at(_position).contains("~"))
    {
        J(classPosition);
    }
    else if (_list->at(_position).contains("word"))
    {
        K(classPosition);

    }
    while (!_list->at(_position).contains(";") && _position < _list->size())
    {
        error("\";\" expected.(L)");
        advance();
    }
    advance(); // and we are at the character which is the next one after ;
}

void Parser::J(AClass* classPosition)
{
    if (_list->at(_position).contains("~"))
    {
        QString destructor = "~";
        advance();
        if (_list->at(_position).contains(classPosition->_name))
        {
            destructor += _list->at(_position);
            destructor.remove("word:");
            advance();
            if (_list->at(_position) == "(")
            {
                advance();
                if (_list->at(_position) == ")")
                {
                    Method *tempMeth = new Method();
                    tempMeth->_keywords.push_back(classPosition->_protection);
                    tempMeth->_name = destructor;
                    tempMeth->_type = "destructor";
                    classPosition->_methods.push_back(tempMeth);
                    advance();
                } else error("\")\" expected (J).");
            } else error("\"(\" expected (J).");
        }else error("destructor must have the same name as class (J).");
    }
}

void Parser::K(AClass* classPosition)
{
    if (_list->at(_position).contains("word:"))
    {
        int i = _position;
        bool method = false;
        while (_list->at(i) != ";" && _position < _list->size())
        {
            i++;
            if (_list->at(i) == "(")  // this means we are building a method
            {
                method = true;
                break;
            }
        }
        if (method == true)
        {
            Method *tempMeth = new Method();
            D(classPosition, tempMeth);
            classPosition->_methods.push_back(tempMeth);
            if (_list->at(_position) == "(")
            {
                advance();
                if (_list->at(_position).contains("word:"))
                {
                    F(classPosition, tempMeth);
                }
                if (_list->at(_position) == ")")
                    advance();
                else error("\")\" expected.(K)");
            } else error("\"(\" expected.(K)");
        }
        else if (method == false)
        {
            Attribute *tempAttr = new Attribute();
            classPosition->_attributes.push_back(tempAttr);
            D(classPosition, tempAttr);
            while (_list->at(_position) == "[")
            {
                tempAttr->_name += "[";
                advance();
                while (_list->at(_position) != "]")
                {
                    if (_list->at(_position).contains("word:") || _list->at(_position).contains("number:"))
                    {
                        tempAttr->_name += _list->at(_position);
                    } else
                    {
                        error("expression expected.(K)");
                        break;
                    }
                    advance();
                }
                tempAttr->_name += "]";
                tempAttr->_name.remove("word:");
                tempAttr->_name.remove("number:");
                advance();
            }
        }
    }
    else error("definition expected.(K)");

}

void Parser::F(AClass* classPosition, Method* method)
{
    if (_list->at(_position).contains("word:"))
    {
        Attribute *tempAttr = new Attribute();
        method->_attributes.push_back(tempAttr);
        E(classPosition, tempAttr);
    }
    while (_list->at(_position) == "," && _position < _list->size())
    {
        advance();
        if (_list->at(_position).contains("word:"))
        {
            Attribute *tempAttr = new Attribute();
            method->_attributes.push_back(tempAttr);
            E(classPosition, tempAttr);
        }
        else error("type identifier expected.(F)");
    }
}

void Parser::E(AClass *classPosition, Attribute *tempAttr)
{
    if (_list->at(_position).contains("word:"))
    {
        D(classPosition,tempAttr);
        if (_list->at(_position) == "=")
        {
            B(classPosition, tempAttr);
        }
    }
}

void Parser::D(AClass* classPosition, Attribute *tempAttr)
{

    if (classPosition->_protection != "")
    {
        tempAttr->_keywords.push_back(classPosition->_protection);
    } else tempAttr->_keywords.push_back("private");

    while ((_list->at(_position).contains("const") || _list->at(_position).contains("static") ||
           _list->at(_position).contains("volatile") || _list->at(_position).contains("mutable")) && _position < _list->size())
    {
        QString keyword = _list->at(_position);
        keyword.remove("word:");
        tempAttr->_keywords.push_back(keyword);
        advance();
    }
    if (_list->at(_position).contains("word:"))
    {
        QString aType = _list->at(_position);
        aType.remove("word:");
        tempAttr->_type = aType;
        advance();
        if (_list->at(_position) == "<")
        {
            A(classPosition, tempAttr);
        }
        while (_list->at((_position)) == "[")
        {
            advance();
            if ((_list->at(_position).contains("word:") || _list->at(_position).contains("number:")) && _list->at(_position + 1) == "]")
            {
                tempAttr->_type += "[" + _list->at(_position);
                tempAttr->_type += "]";
                tempAttr->_type.remove("word:");
                tempAttr->_type.remove("number");
                advance();
                advance();
            }
            else if (_list->at(_position) == "]")
            {
                tempAttr->_type += "[]";
                advance();
            }
            else error("] expected.");
        }
        while ((_list->at(_position) == "*" || _list->at(_position) == "&") && _position < _list->size())
        {
            C(classPosition, tempAttr);
        }
        if (_list->at(_position).contains("word:"))
        {
            QString aName = _list->at(_position);
            aName.remove("word:");
            if (!findKeyWord(aName))
            {
                tempAttr->_name = aName;
                advance();
            } else error("name expected. (D)");
        }
        else if(_list->at(_position) == "," || _list->at(_position) == "=" )
        {
            tempAttr->_name = "";
        }
    } else error("type identifier expected.(D)");

}

void Parser::D(AClass *classPosition, Method *tempMeth)
{

    if (classPosition->_protection != "")
    {
        tempMeth->Attribute::_keywords.push_back(classPosition->_protection);
    } else tempMeth->_keywords.push_back("private");

    while ((_list->at(_position).contains("const") || _list->at(_position).contains("static") ||
           _list->at(_position).contains("volatile") || _list->at(_position).contains("mutable")) && _position < _list->size())
    {
        QString keyword = _list->at(_position);
        keyword.remove("word:");
        tempMeth->_keywords.push_back(keyword);
        advance();
    }
    if (_list->at(_position).contains("word:"))
    {
        QString aType = _list->at(_position);
        aType.remove("word:");
        tempMeth->_type = aType;
        advance();
        if (_list->at(_position) == "<")
        {
            A(classPosition, tempMeth);
            advance();
        }
        while (_list->at((_position)) == "[")
        {
            advance();
            if ((_list->at(_position).contains("word:") || _list->at(_position).contains("number:")) && _list->at(_position + 1) == "]")
            {
                tempMeth->_type += "[" + _list->at(_position);
                tempMeth->_type += "]";
                tempMeth->_type.remove("word:");
                tempMeth->_type.remove("number");
                advance();
                advance();
            }
            else if (_list->at(_position) == "]")
            {
                tempMeth->_type += "[]";
                advance();
            }
            else error("] expected.");
        }
        while (_list->at(_position) == "*" || _list->at(_position) == "&")
        {
            C(classPosition, tempMeth);
        }
        if (_list->at(_position).contains("word:"))
        {
            QString aName = _list->at(_position);
            aName.remove("word:");
            if (!findKeyWord(aName))
            {
                tempMeth->_name = aName;
                advance();
            } else error("method name expected. (D)");
        }
        else if(_list->at(_position).contains("(")) // we've got the constructor!
        {
            if (tempMeth->_type.contains(classPosition->_name))
            {
                tempMeth->_name = tempMeth->_type;
                tempMeth->_type = "constructor";
            }
            else error ("constructor must have the same name as class. (D)");
        }
    } else error("type identifier expected.(D)");

}

void Parser::C(AClass *classPosition, Attribute *attribute)
{
    if (_list->at(_position) == "*" || _list->at(_position) == "&")
    {
        attribute->_type += _list->at(_position);
        advance();
    }
}

void Parser::C(AClass *classPosition, Method *method)
{
    if (_list->at(_position) == "*" || _list->at(_position) == "&")
    {
        method->_type += _list->at(_position);
        advance();
    }
}

void Parser::B(AClass *classPosition, Attribute *attribute)
{
    if (_list->at(_position) == "=")
    {
        QString expr = "= ";
        advance();
        if (_list->at(_position).contains("word:")  || _list->at(_position).contains("number:"))
        {
            QString word = _list->at(_position);
            if (!findKeyWord(word.remove("word:")))
            {
                expr += _list->at(_position);
                expr += " ";
                advance();
                while ((_list->at(_position) == "+" || _list->at(_position) == "-"
                       || _list->at(_position) == "="  || _list->at(_position) == "*" || _list->at(_position) == "/" ) && _position < _list->size())
                {
                    expr += _list->at(_position);
                    expr += " ";
                    advance();
                    if (_list->at(_position).contains("word:") || _list->at(_position).contains("number:"))
                    {
                        expr += _list->at(_position);
                        expr += " ";
                        advance();
                    }
                }
            } else error ("variable name expected");
        }
        else if (_list->at(_position) == "\"") // = "some words"
        {
            expr += "\"";
            advance();
            while (_list->at(_position) != "\"" && _position < _list->size())
            {
                expr += _list->at(_position);
                expr += " ";
                advance();
            }
            expr += "\"";
            advance();
        }
        else if (_list->at(_position) == "'") // = 'letter'
        {
            expr += "'";
            advance();
            expr += _list->at(_position);
            advance();

            if (_list->at(_position) == "'")
                expr += "'";
            else
                error("' expected.(B)");
            advance();
        }
        expr.remove("word:");
        expr.remove("number:"); // removes every occurance of the "word:" or "numer:" string
        attribute->_expression = expr;
    }
}

void Parser::A(AClass *classPosition, Attribute *attribute)
{
    if(_list->at(_position) == "<")
    {
        QString expr = _list->at(_position);
        advance();
        if(_list->at(_position).contains("word:"))
        {
            expr += _list->at(_position);
            advance();
            expr.remove("word:");
            attribute->_type += expr;
            if (_list->at(_position).contains("<"))
            {
                A(classPosition,attribute);
            }
            else if (_list->at(_position) == "*" || _list->at(_position) == "&")
            {
                C(classPosition, attribute);
            }
            if (_list->at(_position) == ">")
            {
                expr = ">";
                attribute->_type += expr;
                advance();
            }
        }
        else
        {
            error("expression expected.(A)");
            advance();
        }
    }
    else
    {
        error("< expected.(A)");
        advance();
    }
}

void Parser::A(AClass *classPosition, Method *method)
{
    if(_list->at(_position) == "<")
    {
        QString expr = _list->at(_position);
        advance();
        if(_list->at(_position).contains("word:"))
        {
            expr += _list->at(_position);
            advance();
            if (_list->at(_position).contains("<"))
            {
                expr.remove("word:");
                method->_type += expr;
                A(classPosition,method);
            }
            else if (_list->at(_position) == "*" || _list->at(_position) == "&")
            {
                C(classPosition, method);
            }
            else if (_list->at(_position) == ">")
            {
                expr = ">";
                method->_type += expr;
                advance();
            }
        }
        else
        {
            error("expression expected.(A)");
            advance();
        }
    }
    else
    {
        error("< expected.(A)");
        advance();
    }
    // dodawanie <word<word>> do method._keywords
}










