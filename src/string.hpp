/*

File: string_tests.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree

https://github.com/AlexanderJDupree/Python-Strings-for-CPP

*/

#ifndef STRING_H
#define STRING_H

#include <cstddef>
#include <type_traits>

class String 
{
public:

    typedef char        value_type;
    typedef char&       reference;
    typedef const char& const_reference;
    typedef char*       pointer;
    typedef const char* const_pointer;
    typedef ptrdiff_t   difference_type;
    typedef size_t      size_type;

    /* Constructors */
    String() : _data(nullptr), _length(0), _capacity(0) {}

    /* Capacity */
    size_type length() { return _length; }

private:

    pointer _data;

    size_type _length;
    size_type _capacity;

};

#endif // STRING_H