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

String::String(size_type n, char c) : String(n + 1)
{
    while(n-- > 0)
    {
        push_back(c);
    }
}

String::String(const self_type& origin) : String()
{
    if(origin.empty()) { return; }

    copy(origin._data, len(origin._data));
    _data[_length] = '\0';
}

String::~String()
{
    delete [] _data;
}

/* Iterators */
String::const_iterator String::cbegin() const noexcept
{
    return &_data[0];
}

String::const_iterator String::begin() const
{
    return &_data[0];
}

String::iterator String::begin()
{
    return &_data[0];
}

String::const_iterator String::cend() const noexcept
{
    return &_data[_length];
}

String::const_iterator String::end() const
{
    return &_data[_length];
}

String::iterator String::end()
{
    return &_data[_length];
}

/* Capacity */
String::size_type String::size() const
{
    return _length;
}

String::size_type String::length() const
{
    return _length;
}

String::size_type String::capacity() const
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

bool String::empty() const
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

/* Modifiers */
String::self_type& String::push_back(const_reference character)
{
    if(_length >= _capacity - 1) { resize(_capacity * 2); }

    _data[_length++] = character;
    _data[_length] = '\0';

    return *this;
}

String::self_type& String::append(const self_type& str)
{
    reserve(_capacity + str._capacity);
    return append(str._data);
}

String::self_type& String::append(const_pointer str)
{
    if (catch_null_exception(str)) { return *this; }

    for (size_type index = 0; str[index] != '\0'; ++index)
    {
        push_back(str[index]);
    }
    _data[_length] = '\0';

    return *this;
}

String::self_type& String::append(const_pointer str, size_type n)
{
    if (catch_null_exception(str)) { return *this; }

    for (size_type i = 0; str[i] != '\0' && n-- > 0; ++i)
    {
        push_back(str[i]);
    }
    _data[_length] = '\0';

    return *this;

}

String::self_type& String::append(size_type n, char c)
{
    return append(String(n, c));
}

String::self_type& String::append(std::initializer_list<char> list)
{
    return append(list.begin(), list.end());
}

/* Pythonic Modifiers */

String::self_type& String::upper()
{
    for(iterator it = begin(); it != end(); ++it)
    {
        *it = std::toupper(*it);
    }
    return *this;
}

String::self_type& String::lower()
{
    for(iterator it = begin(); it != end(); ++it)
    {
        *it = std::tolower(*it);
    }
    return *this;
}

String::self_type& String::swapcase()
{
    for(iterator it = begin(); it != end(); ++it)
    {
        std::isupper(*it) ? *it = std::tolower(*it) : *it = std::toupper(*it);
    }
    return *this;
}

bool String::isupper()
{
    bool result = false;
    for(const_iterator it = cbegin(); it != cend(); ++it)
    {
        if (std::isalpha(*it))
        {
            if(std::islower(*it))
            {
                return false;
            }
            result = true;
        }
    }
    return result;
}

bool String::islower()
{
    bool result = false;
    for(const_iterator it = cbegin(); it != cend(); ++it)
    {
        if(std::isalpha(*it))
        {
            if(std::isupper(*it))
            {
                return false;
            }
            result = true;
        }
    }
    return result;
}
bool String::isnumeric()
{
    bool result = false;
    for(const_iterator it = cbegin(); it != cend(); ++it)
    {
        if(!std::isdigit(*it)) 
        {
            return false;
        }
        result = true;
    }
    return result;
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

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str._data;
    return os;
}

String::reference String::operator[](index_type pos)
{
    validate_position(pos);

    return _data[pos];
} 

String::const_reference String::operator[](index_type pos) const
{
    validate_position(pos);

    return _data[pos];
}

/* Private */
void String::validate_pointer(const_pointer str)
{
    if(str) { return; }

    throw std::invalid_argument("char pointer points to null");
}

void String::validate_position(index_type& pos) const
{
    if (pos < 0) { pos += _length; }
    if(pos < static_cast<index_type>(_length) && pos >= 0) { return; }

    throw out_of_range("error, index pos is out of bounds", pos);
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
