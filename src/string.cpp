/*
File: string.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree

https://github.com/AlexanderJDupree/Python-Strings-for-CPP

*/

#ifndef STRING_CPP
#define STRING_CPP

#include <iostream>
#include "string.hpp"

/* Constructors */
String::String(const_pointer str) : String(len(str) + 1)
{
    copy(str, _capacity);
    _data[_length] = '\0';
}

String::String(size_type n) : _data(new char[n]), _length(0), _capacity(n) {}

/* Capacity */
String::size_type String::size()
{
    return _length;
}

String::size_type String::length()
{
    return _length;
}

String::size_type String::capacity()
{
    return _capacity;
}

void String::reserve(size_type n)
{
    if(_capacity > n) { return; }

    resize(n - 1);
}

void String::resize(size_type n)
{
    _capacity = n + 1;
    if(_data == nullptr)
    {
        _data = new char[_capacity];
        return;
    }

    pointer temp = new char[_capacity];

    this->_length = copy(*this, temp, _capacity - 1);

    temp[_length] = '\0';

    delete [] this->_data;

    this->_data = temp;

    return;
}

bool String::empty()
{
    return !(_length);
}

/* Operations */
String::size_type String::len(const_pointer str)
{
    validate_pointer(str);

    size_type length;
    for(length = 0; str[length] != '\0'; ++length);

    return length;
}

String::size_type String::copy(const self_type& in_str, pointer out_str, size_type len, size_type pos)
{
    validate_pointer(out_str);
    validate_pointer(in_str._data);

    size_type i = 0;
    for(; i < len && in_str._data[pos] != '\0'; ++i)
    {
        //TODO access data member through the [] function
        out_str[i] = in_str._data[pos++];
    }
    return i;
}

String::size_type String::copy(const_pointer str, size_type len)
{
    validate_pointer(str);
    if (len > _capacity) { resize(len); }

    size_type i = 0;
    for(; i < len && str[i] != '\0'; ++i)
    {
        _data[i] = str[i];
    }
    _length = i;
    return i;
}

bool String::compare_equal(const_pointer str) const
{
    if(catch_null_exception(str) || catch_null_exception(_data))
    {
        return false;
    }

    size_type i = 0;
    for (; _data[i] != '\0' && str[i] != '\0' && _data[i] == str[i]; ++i);

    return i == _length;
}

bool String::compare_equal(const self_type& str) const
{
    if(_length != str._length)
    {
        return false;
    }
    else if(_length == 0 && str._length == 0)
    {
        return true;
    }

    return compare_equal(str._data);
}

/* Operator Overloads */
bool operator==(const String& lhs, const char* rhs)
{
    return lhs.compare_equal(rhs);
}
bool operator==(const char* lhs, const String& rhs)
{
    return (rhs == lhs);
}
bool operator==(const String& lhs, const String& rhs)
{
    return lhs.compare_equal(rhs);
}
bool operator!=(const String& lhs, const char* rhs)
{
    return !(lhs == rhs);
}
bool operator!=(const char* lhs, const String& rhs)
{
    return (rhs != lhs);
}
bool operator!=(const String& lhs, const String& rhs)
{
    return !(lhs == rhs);
}

/* Private */
void String::validate_pointer(const_pointer str)
{
    if(str) { return; }

    throw std::invalid_argument("char pointer points to null");
}

bool String::catch_null_exception(const_pointer str)
{
    try
    {
        validate_pointer(str);
        return false;
    }
    catch(const std::invalid_argument& err)
    {
        return true;
    }
}

#endif // STRING_CPP
