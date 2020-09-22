/*
File: sstring.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree

https://github.com/AlexanderJDupree/Python-Strings-for-CPP

*/


#include "sstring.h"

/****** CONSTRUCTORS ******/

SString::SString()
    : reference_manager(1)
{
    _data[0] = '\0';
}

SString::SString(const_pointer str) 
    : reference_manager(len(str) + 1)
{
    copy(str);
}

SString::SString(pointer begin, pointer end)
    : reference_manager(end - begin)
{
    for(unsigned i = 0; begin != end; ++begin)
    {
        _data[i++] = *begin;
    }

    _data[*_size] = '\0';
}

SString::SString(unsigned n, char fill)
    : reference_manager(n + 1)
{
    for (unsigned i = 0; i < n; ++i)
    {
        _data[i] = fill;
    }

    _data[*_size - 1] = '\0';
}

SString::SString(const_pointer buffer, size_type n) 
    : reference_manager(n + 1)
{
    validate_pointer(buffer);

    for(unsigned i = 0; i < n; ++i)
    {
        _data[i] = buffer[i];
    }

    _data[*_size - 1] = '\0';
}

SString::SString(const self_type& origin)
    : reference_manager(origin) {}

// Inherited virtual destructor handles deallocation
SString::~SString() {}

SString::size_type SString::len(const_pointer str)
{
    if (catch_null_exception(str))
    {
        return 0;
    }

    size_type length;

    // Counts the number of characters before null terminator
    for(length = 0; str[length] != '\0'; ++length);

    return length;
}

void SString::copy(const_pointer source)
{
    if(source)
    {
        size_type index = 0;
        for(;index < length() && source[index] != '\0' ; ++index)
        {
            _data[index] = source[index];
        }
    }

    // Ensures the last character is null-terminated. _length is not out of 
    // bounds because we allocated enough for len(str) + 1
    _data[length()] = '\0';

    return;
}

SString::size_type SString::length() const
{
    return *_size - 1;
}

bool SString::empty() const
{
    return length() == 0;
}

bool SString::compare_equal(const self_type& str) const
{
    // Strings are different sizes, they are not the same
    if (length() != str.length())
    {
        return false;
    }
    // Strings are both empty, or they share the same data
    if ((length() == 0 && str.length() == 0) || _data == str._data)
    {
        return true;
    }

    // Iterate through each string and compare characters
    return *this == str._data;
}

/****** OPERATIONS ******/

SString SString::substring(unsigned begin, unsigned end) const
{
    if (begin > end || begin > length() || end > length())
    {
        throw invalid_substring();
    }

    return SString(_data + begin, _data + end + 1);
}

SString SString::truncate(unsigned width) const
{
    if (width > length())
    {
        return *this + SString(width - length() + 1, ' ');
    }
    
    return substring(0, width - 1);
}

/****** PYTHONIC METHODS ******/

bool SString::is_upper() const 
{
    for(unsigned i = 0; i < length(); ++i)
    {
        if(std::isalpha(_data[i]) && std::islower(_data[i])) 
        {
            return false;
        }
    }
    return true;
}

SString& SString::strip(char strip_c){
    // null terminator cannot be used as strip seed
    if(strip_c == '\0')
        throw std::invalid_argument("null terminator cannot be used as strip seed!");
	
	// double pointer
    const_pointer it_begin = begin();
    const_pointer it_end = end();
    
    while(*it_begin == strip_c)
        it_begin++;
    while(*it_end == strip_c || *it_end == '\0')
        it_end--;
    
    if (it_end < it_begin)
        *this = SString();
    else{
        SString result((pointer)it_begin, (pointer)it_end + 1);
        *this = result;
    }

    return *this;

}

bool SString::isnumeric(void) const {
    return (is_dec_num() || is_bin_num() || is_hex_num() || is_oct_num());
}

bool SString::is_bin_num(void) const {

    /* checking for the prefix 0b and if passed, checking for
     * characters to be either '0' or '1' */
    if ((size() > 2) && (_data[0] == '0') && (_data[1] == 'b')) {
        for (unsigned int i = 2; i < size() - 1; ++i) {
            if ((_data[i] != '0') && (_data[i] != '1'))
                return false;
        }
        return true;
    }

    return false;
}

bool SString::is_oct_num(void) const {

    /* checking for the prefix 0o and if passed, checking for
     * character to be in between '0' and '7' for octal based numbers */
    if ((size() > 2) && (_data[0] == '0') && (_data[1] == 'o')) {
        for (unsigned int i = 2; i < size() - 1; ++i) {
            if (!(std::isdigit(_data[i]) && (_data[i] >= 48)  && (_data[i] <= 55)))
                return false;
        }
        return true;
    }

    return false;
}

bool SString::is_dec_num(void) const {

    /* Checking the characters to be digits in case of decimal number,
     */
    for (unsigned int i = 0; i < size() - 1; ++i) {
        if (!(std::isdigit(_data[i]))) {
            return false;
        }
    }

    return true;
}

bool SString::is_hex_num(void) const {

    /* checking for prefic 0x and if passed, checking the hexadecimal digits
     * '0' to '9', 'A', 'B', 'C', 'D', 'E', 'F' both uppercase and lower case
     * based on ASCII values */
    if ((size() > 2) && (_data[0] == '0') && (_data[1] == 'x')) {
        for (unsigned int i = 2; i < size() - 1; ++i) {
            if (!((std::isdigit(_data[i])) || (_data[i] >= 65  && _data[i] <= 70)
                    || (_data[i] >= 97 && _data[i] <= 102)))
                return false;
        }
        return true;
    }

    return false;
}

/****** ITERATORS ******/

SString::const_iterator SString::begin() const
{
    return _data;
}

SString::const_iterator SString::end() const
{
    return &_data[length()];
}

/****** SUBROUTINES ******/

void SString::validate_pointer(const_pointer str)
{
    if (str) 
    {
        return;
    }

    throw std::invalid_argument("char pointer points to null");
}

bool SString::catch_null_exception(const_pointer str)
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

/****** COPY AND SWAP ******/
SString::self_type& SString::operator=(const SString& str)
{
    // Utilize the copy constructor to create a copy of the string
    SString copy(str);

    // Swap ownership of resources with the copy
    swap(*this, copy);

    // As the copy goes out of scope it destructs with the old data
    return *this;
}

// TODO Review if there is a faster way to perform reassignment with a c-string
SString::self_type& SString::operator=(const_pointer str)
{
    validate_pointer(str);

    *this = SString(str);

    return *this;
}

void SString::swap(SString& new_string, SString& old_string)
{
    using std::swap;

    swap(new_string._data, old_string._data);
    swap(new_string._size, old_string._size);
    swap(new_string._ref_count, old_string._ref_count);
    return;
}

/****** CONCATENATION ******/

// TODO Review and establish a faster way to perform string concatenation
SString operator+(const SString& lhs, const char* rhs)
{
    // TODO create an append function that this operator will call
    char* buffer = new char[lhs.length() + std::strlen(rhs)];
    std::strcpy(buffer, lhs._data);
    std::strcat(buffer, rhs);

    SString result(buffer);
    delete [] buffer;
    return result;
}

SString operator+(const char* lhs, const SString& rhs)
{
    return SString(lhs) + rhs;
}

SString operator+(const SString& lhs, const SString& rhs)
{
    return lhs + rhs._data;
}

/****** STREAM OPERATORS ******/
std::ostream& operator << (std::ostream& os, const SString& str)
{
    os << str._data;
    return os;
}

std::istream& operator >> (std::istream& is, SString& str)
{
    char* buffer = new char[100];

    is.get(buffer, 100);

    // TODO look into writing string builder class to prevent this extra copy
    // We use the assignment operator to handle the buffer copy
    str = buffer;

    delete [] buffer;

    return is;
}

/****** ACCESS OEPRATORS ******/

char SString::operator [] (int index) const
{
    int len = length();
    if (index >= len || index < len * -1)
    {
        throw bad_index(index);
    }
    if(index < 0) 
    {
        index += len;
    }

    return *(_data + index);
}

/****** COMPARISON OPERATORS ******/
bool operator==(const SString& lhs, const char* rhs)
{
    if(SString::catch_null_exception(rhs))
    {
        return false;
    }

    return std::strcmp(lhs._data, rhs) == 0;
}
bool operator==(const char* lhs, const SString& rhs)
{
    return rhs == lhs;
}
bool operator==(const SString& lhs, const SString& rhs)
{
    return lhs.compare_equal(rhs);
}
bool operator!=(const SString& lhs, const char* rhs)
{
    return !(lhs == rhs);
}
bool operator!=(const char* lhs, const SString& rhs)
{
    return !(rhs == lhs);
}
bool operator!=(const SString& lhs, const SString& rhs)
{
    return !(lhs == rhs._data);
}
bool operator< (const SString& lhs, const char* rhs)
{
    return std::strcmp(lhs._data, rhs) < 0;
}
bool operator< (const char* lhs, const SString& rhs)
{
    return (rhs > lhs);
}
bool operator< (const SString& lhs, const SString& rhs)
{
    return lhs < rhs._data;
}
bool operator> (const SString& lhs, const char* rhs)
{
    return !(lhs < rhs);
}
bool operator> (const char* lhs, const SString& rhs)
{
    return rhs < lhs;
}
bool operator> (const SString& lhs, const SString& rhs)
{
    return !(lhs < rhs._data);
}

