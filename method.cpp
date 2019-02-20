#include "method.h"

Method::Method() : Attribute()
{
}

Method::Method(const Method &method)
{
    this->_attributes = method._attributes;
    this->_keywords = method._keywords;
    this->_name = method._name;
    this->_type = method._type;
}

Method::~Method()
{
    this->_attributes.clear();
    this->_keywords.clear();
    this->_name.clear();
    this->_type.clear();
}
