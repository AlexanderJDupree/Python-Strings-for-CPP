/*
File: string.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree

https://github.com/AlexanderJDupree/Python-Strings-for-CPP

*/

#ifndef STRING_CPP
#define STRING_CPP

#include "string.hpp"

/* Constructors */
String::String(const_pointer str) : String(len(str) + 1)
{
    _length = copy(str, _capacity);
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

String::size_type String::copy(const_pointer str, size_type len)
{
    // TODO resize if len is bigger than capacity
    // TODO Validate pointer
    size_type pos = 0;
    for(; pos < len && str[pos] != '\0'; ++pos)
    {
        _data[pos] = str[pos];
    }
    return pos;
}

bool String::compare_equal(const_pointer str) const
{
    // TODO package this into seperate function
    try
    {
        validate_pointer(str);
        validate_pointer(_data);
    }
    catch (const std::invalid_argument& err)
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
void String::validate_pointer(const_pointer str) const
{
    if(str) { return; }

    throw std::invalid_argument("char pointer points to null");
}

#endif // STRING_CPP
