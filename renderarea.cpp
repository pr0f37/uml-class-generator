#include "renderarea.h"
#include <QPainter>
RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setPen(palette().dark().color());
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

    for (int i = 0; i < _classList->size(); i++)
    {
        int k = 0;
        if (i > 2)
            k = 2;
        int height = (_classList->at(i)->_methods.size() + _classList->at(i)->_attributes.size()
                      + _classList->at(i)->_nests.size() + _classList->at(i)->_nestedclasses.size() + 1) * 20;
        int width = 300;
        painter.setPen(QColor(0,0,0));
        paintClass((i%3)*width + (i%3) *10 + 10, 150*k + 10*k +10, width, height, _classList->at(i), &painter);
        painter.drawRect(QRect((i%3) * width + (i%3)*10 + 10, 150 *k  + 10*k + 10, width, height));
    }


}

void RenderArea::getClassList(QList<AClass *> * classList)
{
    _classList = classList;
}

void RenderArea::paintClass(int x, int y, int width, int height, AClass * myClass, QPainter *painter)
{
    QFont f("Arial");
    painter->setFont(f);
    QString className = myClass->_name;
    if (myClass->_ancestors.size() > 0)
    {
        className += " : ";
        for (int i = 0; i < myClass->_ancestors.size(); i++)
        {
            className += myClass->_ancestors.at(i);
            if (i < myClass->_ancestors.size() -1)
                className += ", ";
        }
    }
    height = 20;
    painter->drawRect(QRect(x,y,width, height));
    painter->drawText(QRectF(x,y,width, height), className, QTextOption(Qt::AlignCenter));
    if (myClass->_nests.size() > 0)
    {
        painter->drawRect(QRect(x, y + height, width, myClass->_nests.size()*20));
        painter->drawText(QRectF(x + 5, y + height,width, 20), "Nested in:", QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        for (int i = 0; i < myClass->_nests.size(); i++)
        {
            QString message;
            message = myClass->_nests.at(i);
            painter->drawText(QRectF(x, y+20 + i*20,width, 20), message, QTextOption(Qt::AlignCenter));
        }
        height += myClass->_nests.size() * 20;
    }

    if (myClass->_nestedclasses.size() > 0)
    {
        painter->drawRect(QRect(x, y + height, width, myClass->_nestedclasses.size() * 20));
        painter->drawText(QRectF(x + 5, y + height,width, 20), "Nested classes:", QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        for (int i = 0; i < myClass->_nestedclasses.size(); i++)
        {
            QString message;
            message = myClass->_nestedclasses.at(i);
            painter->drawText(QRectF(x, y + i*20 + height,width, 20), message, QTextOption(Qt::AlignCenter));
        }
        height += myClass->_nestedclasses.size() *20;

    }

    painter->drawRect(QRect(x, y + height, width, myClass->_methods.size()*20));
    for (int i = 0; i < myClass->_methods.size(); i++)
    {

        QString message;
        for (int j = 1; j < myClass->_methods.at(i)->_keywords.size(); j++)
        {
            message += myClass->_methods.at(i)->_keywords.at(j);
            message += " ";
        }
        message += myClass->_methods.at(i)->_type;
        message += " ";
        message += myClass->_methods.at(i)->_name;
        message += "(";

        for (int j = 0; j < myClass->_methods.at(i)->_attributes.size(); j++)
        {
            for (int k = 1; k < myClass->_methods.at(i)->_attributes.at(j)->_keywords.size(); k ++)
            {
                message += myClass->_methods.at(i)->_attributes.at(j)->_keywords.at(k);
                message += " ";
            }
            message += myClass->_methods.at(i)->_attributes.at(j)->_type;
            if (!myClass->_methods.at(i)->_attributes.at(j)->_name.isEmpty())
            {
                message += " ";
                message += myClass->_methods.at(i)->_attributes.at(j)->_name;
            }
            if (!(myClass->_methods.at(i)->_attributes.at(j)->_expression.isEmpty()))
            {
                message += " ";
                message += myClass->_methods.at(i)->_attributes.at(j)->_expression;
            }
            if ( j < (myClass->_methods.at(i)->_attributes.size() - 1))
                message += ", ";
        }
        message += ");";
        if (myClass->_methods.at(i)->_keywords.at(0).contains("public"))
            painter->setPen(QColor(0,125,0));
        else if (myClass->_methods.at(i)->_keywords.at(0).contains("private"))
            painter->setPen(QColor(255,0,0));
        else if (myClass->_methods.at(i)->_keywords.at(0).contains("protected"))
            painter->setPen(QColor(0,125,200));
        if (myClass->_methods.at(i)->_keywords.contains("const") || myClass->_methods.at(i)->_keywords.contains("volatile")
            || myClass->_methods.at(i)->_keywords.contains("mutable") || myClass->_methods.at(i)->_keywords.contains("static"))
        {
            f.setItalic(true);
            painter->setFont(f);
        }
        painter->drawText(QRectF(x,y + height + i*20,width, 20), message, QTextOption(Qt::AlignCenter));
        painter->setPen(QColor(0,0,0));
        f.setItalic(false);
        painter->setFont(f);

    }
    height += myClass->_methods.size() *20;

    painter->drawRect(QRect(x,y + height, width, myClass->_attributes.size() *20));
    for (int i = 0; i < myClass->_attributes.size(); i ++)
    {
        QString message;
        for (int j = 1; j < myClass->_attributes.at(i)->_keywords.size(); j++)
        {
            message += myClass->_attributes.at(i)->_keywords.at(j);
            message += " ";
        }
        message += myClass->_attributes.at(i)->_type;
        message += " ";
        message += myClass->_attributes.at(i)->_name;
        if (myClass->_attributes.at(i)->_keywords.at(0).contains("public"))
            painter->setPen(QColor(0,125,0));
        else if (myClass->_attributes.at(i)->_keywords.at(0).contains("private"))
            painter->setPen(QColor(255,0,0));
        else if (myClass->_attributes.at(i)->_keywords.at(0).contains("protected"))
            painter->setPen(QColor(0,125,200));
        if (myClass->_attributes.at(i)->_keywords.contains("const") || myClass->_attributes.at(i)->_keywords.contains("volatile")
            || myClass->_attributes.at(i)->_keywords.contains("mutable") || myClass->_attributes.at(i)->_keywords.contains("static"))
        {
            f.setItalic(true);
            painter->setFont(f);
        }
        painter->drawText(QRectF(x, y + i*20 + height ,width, 20), message, QTextOption(Qt::AlignCenter));
        painter->setPen(QColor(0,0,0));
        f.setItalic(false);
        painter->setFont(f);
    }

}
