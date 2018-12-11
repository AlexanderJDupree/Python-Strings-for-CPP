/*
TODO File comments
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
    if (!catch_null_exception(str))
    {
        copy(str);
    }
    else
    {
        _data[0] = '\0';
    }
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
    validate_pointer(source);

    size_type index = 0;
    for(; index < length() && source[index] != '\0' ; ++index)
    {
        _data[index] = source[index];
    }

    // Ensures the last character is null-terminated. _length is not out of 
    // bounds because we allocated enough for len(str) + 1
    _data[length()] = '\0';

    return;
}

SString::size_type SString::length() const
{
    // TODO, this assumes the string was not a string of null characters
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

SString operator+(const SString& lhs, const char* rhs)
{
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

char SString::operator [] (unsigned index) const
{
    if (index >= length())
    {
        throw bad_index(index);
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
    return (rhs < lhs);
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
    return !(rhs < lhs);
}
bool operator> (const SString& lhs, const SString& rhs)
{
    return !(lhs < rhs._data);
}

