/*

File: string_tests.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree

https://github.com/AlexanderJDupree/Python-Strings-for-CPP

*/

#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <cstddef>
#include <type_traits>

/* Helper Functions */

class String 
{
public:

    typedef String      self_type;
    typedef char        value_type;
    typedef char&       reference;
    typedef const char& const_reference;
    typedef char*       pointer;
    typedef const char* const_pointer;
    typedef ptrdiff_t   difference_type;
    typedef size_t      size_type;

    /* Constructors */
    String() : _data(nullptr), _length(0), _capacity(0) {}

    explicit String(const_pointer str);

    explicit String(size_type n);

    /* Capacity */
    size_type size();
    size_type length();
    size_type capacity();
    
    bool empty();

    /* Operations */
    size_type len(const_pointer str);
    size_type copy(const_pointer str, size_type len);
    bool compare_equal(const_pointer str) const;
    bool compare_equal(const self_type& str) const;

    /* Operator Overloads */
    friend bool operator==(const self_type& lhs, const_pointer rhs);
    friend bool operator==(const_pointer lhs, const self_type& rhs);
    friend bool operator==(const self_type& lhs, const self_type& rhs);
    friend bool operator!=(const self_type& lhs, const_pointer rhs);
    friend bool operator!=(const_pointer lhs, const self_type& rhs);
    friend bool operator!=(const self_type& lhs, const self_type& rhs);


private:

    pointer _data;

    size_type _length;
    size_type _capacity;

    void validate_pointer(const_pointer) const;

};

#endif // STRING_H
