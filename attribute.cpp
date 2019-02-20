#include "attribute.h"

Attribute::Attribute()
{
}

Attribute::Attribute(const Attribute &attribute)
{
    this->_keywords = attribute._keywords;
    this->_name = attribute._name;
    this->_type = attribute._type;
}

Attribute::~Attribute()
{
    this->_keywords.clear();
    this->_name.clear();
    this->_type.clear();
}
