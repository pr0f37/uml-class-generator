#include "aclass.h"

AClass::AClass()
{
}

AClass::AClass(const AClass &AClass)
{
    this->_name = AClass._name;
    this->_file = AClass._file;
    this->_ancestors = AClass._ancestors;
    this->_attributes = AClass._attributes;
    this->_methods = AClass._methods;
}

AClass::~AClass()
{
    this->_name.clear();
    this->_ancestors.clear();
    this->_attributes.clear();
    this->_methods.clear();
    this->_file.clear();
}

