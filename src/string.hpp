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
#include <stdexcept>
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
    typedef int         index_type;

    /* Constructors */
    String() : _data(nullptr), _length(0), _capacity(0) {}

    explicit String(const_pointer str);

    explicit String(size_type n);

    /* Capacity */
    size_type size() const;
    size_type length() const;
    size_type capacity() const;

    void reserve(size_type n);
    void resize(size_type n);
    bool empty() const;

    /* Operations */
    static size_type len(const_pointer str);
    static size_type copy(const self_type& in_str, pointer out_str, size_type len, size_type pos=0);
    size_type copy(const_pointer str, size_type len); // TODO add positional argument
    bool compare_equal(const_pointer str) const;
    bool compare_equal(const self_type& str) const;

    /* Operator Overloads */
    friend bool operator==(const self_type& lhs, const_pointer rhs);
    friend bool operator==(const_pointer lhs, const self_type& rhs);
    friend bool operator==(const self_type& lhs, const self_type& rhs);
    friend bool operator!=(const self_type& lhs, const_pointer rhs);
    friend bool operator!=(const_pointer lhs, const self_type& rhs);
    friend bool operator!=(const self_type& lhs, const self_type& rhs);

    reference operator[](index_type pos);
    const_reference operator[](index_type pos) const;

private:

    pointer _data;

    size_type _length;
    size_type _capacity;

    static void validate_pointer(const_pointer);
    void validate_position(index_type& pos) const;
    static bool catch_null_exception(const_pointer);
};

#endif // STRING_H
