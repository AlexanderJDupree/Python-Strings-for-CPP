/*
*/

#ifndef RC_MANAGER_H
#define RC_MANAGER_H

#include <cstddef> // NULL

template <typename T> 
class reference_manager
{
  public:
    
    typedef T                   value_type;
    typedef T&                  reference; 
    typedef T*                  pointer;
    typedef const T&            const_reference;
    typedef const T*            const_pointer;
    typedef reference_manager   self_type;
    typedef unsigned            size_type;

    // Allocates a T array of a defined size
    reference_manager(size_type size = 0);

    // Points this object to the origin data, increments reference count
    reference_manager(const self_type& origin);

    // Decrements the reference count, if the reference count is zero, releases
    // the data
    virtual ~reference_manager();

    // Returns the number of elements in the array
    size_type size() const;

    // Returns the number of references to the array
    size_type ref_count() const;

  protected:

    size_type* _size; // The shared size of the allocated data
    size_type* _ref_count; // The number of references to the data
    pointer   _data; // The shared data object

  private:

    // Releases the data. This will delete the data, ref count and size for ALL
    // referenced objects
    void release();

};

/*******
Implementation Section for the reference_manager.
*******/

#ifndef RC_MANAGER_CPP
#define RC_MANAGER_CPP

template <typename T>
reference_manager<T>::reference_manager(size_type size)
    : _size(new size_type(size)), 
      _ref_count(new unsigned(1)), 
      _data(new value_type[size]) {}

template <typename T>
reference_manager<T>::reference_manager(const self_type& origin)
    : _size(origin._size), _ref_count(origin._ref_count), _data(origin._data)
{
    ++(*_ref_count);
}

template <typename T>
reference_manager<T>::~reference_manager()
{
    if(--(*_ref_count) == 0)
    {
        release();
    }
}

template <typename T>
unsigned reference_manager<T>::size() const
{
    return *_size;
}

template <typename T>
unsigned reference_manager<T>::ref_count() const
{
    return *_ref_count;
}

template <typename T>
void reference_manager<T>::release()
{
    delete [] _data;
    delete _size;
    delete _ref_count;

    _size = NULL;
    _ref_count = NULL;
    _data = NULL;
}

#endif // RC_ARRAY_CPP

#endif // RC_MANAGER_H

/*
 TODO File comments
*/

#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include <stdexcept> 

// SString inherits the functionality of the reference manager to allow for 
// smart allocation, copy, and deallocation
class SString : public reference_manager<char>
{
  public:

    typedef SString     self_type;
    typedef char*       pointer;
    typedef const char& const_reference;
    typedef const char* const_pointer;
    typedef size_t      size_type;
    typedef const char* const_iterator;

    /****** CONSTRUCTORS ******/

    // Default construction
    SString();

    // c-string constructor
    SString(const_pointer str);

    // Sub-string constructor
    SString(pointer begin, pointer end);

    // Fill constructor
    SString(unsigned n, char fill);

    // Buffer construction
    SString(const_pointer buffer, size_type n);

    // Copy Constructor increments reference count
    SString(const self_type& origin);

    ~SString();

    /****** CAPACITY ******/

    // Returns the number of characters in the string
    size_type length() const;

    // Tests if the string is empty;
    bool empty() const;

    // len counts the number of characters in a cstring before null character
    static size_type len(const_pointer str);

    /****** OPERATIONS ******/
    
    // Returns a copy of the string from [begin:end]
    self_type substring(unsigned begin=0, unsigned end=0) const;

    // Returns a substring of the string from (0, width)
    self_type truncate(unsigned width = 8) const;

    /****** PYTHONIC METHODS ******/

    bool is_upper() const;

    //  Strip the SString in begining and end
    self_type& strip(char strip_c = '\n');

    // Returns true if the string is an integer
    // or a binary number with prefix 0b,
    // or a hexadecimal number with prefix 0x
    // or a octal number with prefic 0o
    bool isnumeric(void) const;

    /****** ITERATORS ******/

    // returns a random-access iterator to the beginning of the string
    const_iterator begin() const;

    // returns a random-access iterator to the null character of the string
    const_iterator end() const;

    /****** COPY AND SWAP ******/

    self_type& operator=(const self_type& str);
    self_type& operator=(const_pointer str);

    // Swaps ownership of resources
    static void swap(SString& new_string, SString& old_string);

    /****** CONCATENATION ******/

    friend self_type operator+(const self_type& lhs, const_pointer rhs);
    friend self_type operator+(const_pointer lhs, const self_type& rhs);
    friend self_type operator+(const self_type& lhs, const self_type& rhs);

    /****** STREAM OPERATORS ******/

    friend std::ostream& operator<<(std::ostream& os, const self_type& str);
    friend std::istream& operator>>(std::istream& is, self_type& str);

    /****** ACCESS OPERATORS ******/

    char operator [] (int index) const;

    /****** COMPARISON OPERATORS ******/

    // Comparison operators uses std::strcmp to compare for equality
    // Compares string length first, then compares the cstring
    bool compare_equal(const self_type& str) const;

    // Comparison operators are freestanding, allowing for comparison of
    // cstrings and SStrings on either side of the operator
    friend bool operator==(const self_type& lhs, const_pointer rhs);
    friend bool operator==(const_pointer lhs, const self_type& rhs);
    friend bool operator==(const self_type& lhs, const self_type& rhs);

    friend bool operator!=(const self_type& lhs, const_pointer rhs);
    friend bool operator!=(const_pointer lhs, const self_type& rhs);
    friend bool operator!=(const self_type& lhs, const self_type& rhs);

    friend bool operator< (const self_type& lhs, const_pointer rhs);
    friend bool operator< (const_pointer lhs, const self_type& rhs);
    friend bool operator< (const self_type& lhs, const self_type& rhs);

    friend bool operator> (const self_type& lhs, const_pointer rhs);
    friend bool operator> (const_pointer lhs, const self_type& rhs);
    friend bool operator> (const self_type& lhs, const self_type& rhs);

    /****** TYPE CASTS ******/
    operator const char*() const { return _data; }
    operator const unsigned long*() const { return (const unsigned long*)_data; }

  private:

    /****** SUBROUTINES ******/

    // Throws an exception if the pointer is NULL
    static void validate_pointer(const_pointer);
    
    // Returns true if a null exception was thrown
    static bool catch_null_exception(const_pointer);
    
    // copies each character from source including null character. Stops 
    // copying if the buffer is full
    void copy(const_pointer source);

    // helper functions for the isnumeric() function
    bool is_hex_num(void) const;
    bool is_bin_num(void) const;
    bool is_dec_num(void) const;
    bool is_oct_num(void) const;
};

struct invalid_substring : public std::exception
{
    const char * _error;

    invalid_substring(const char* err = "Error, substring bounds do not exist")
        : _error(err) {}

    const char* what() const throw()
    {
        return _error;
    }
};

struct bad_index : public std::exception
{
    const char* _error;

    unsigned _index;

    bad_index(unsigned index, const char* err = "Provided Index is out of bounds")
        : _error(err), _index(index) {}

    const char* what() const throw()
    {
        return _error;
    }

    // Returns the value of the bad index
    unsigned index() const throw()
    {
        return _index;
    }
};
#endif // STRING_H

