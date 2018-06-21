/*
File: string_tests.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree

https://github.com/AlexanderJDupree/Python-Strings-for-CPP

*/

#include <stdexcept>
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include "string.hpp"

TEST_CASE("Constructing Strings", "[String], [constructors]")
{
    SECTION("Default Construction")
    {
        String str;

        REQUIRE(str.length() == 0);
        REQUIRE(str.capacity() == 1);
    }
    SECTION("Construction with a C-string")
    {
        const char* test = "Hello";
        String str(test);

        REQUIRE(str == test);
        REQUIRE(str.length() == std::strlen(test));
        REQUIRE(str.capacity() == std::strlen(test) + 1);
    }
    SECTION("Reserve Construction")
    {
        String str(10);

        REQUIRE(str.length() == 0);
        REQUIRE(str.capacity() == 10);
    }
    SECTION("Construction with a nullptr")
    {
        REQUIRE_THROWS_AS(String(nullptr), std::invalid_argument);
    }
    SECTION("Copy construction")
    {
        String origin("Hello");
        String copy(origin);

        REQUIRE(copy == origin);
    }
    SECTION("Copy construction with empty string")
    {
        String origin;
        String copy(origin);

        REQUIRE(copy == origin);
    }
}

TEST_CASE("Capacity functions", "[String], [capacity]")
{
    SECTION("Size of an empty String")
    {
        String str;

        REQUIRE(str.size() == 0);
    }
    SECTION("Capcacity of an empty String")
    {
        String str;

        REQUIRE(str.capacity() == 1);
    }
    SECTION("Test if string is empty")
    {
        String str;

        REQUIRE(str.empty());
    }
}

TEST_CASE("Relational Operators", "[String], [relational], [operators], [overloads]")
{
    SECTION("Equality operators on two identical strings")
    {
        String lhs("Hello");
        String rhs("Hello");

        REQUIRE(lhs == rhs);
    }
    SECTION("Inequality operators")
    {
        String lhs("Hello");
        String rhs;

        REQUIRE(lhs != rhs);
    }
    SECTION("Equality comparison with c-strings")
    {
        String lhs("Hello");
        const char* rhs = "Hello";

        REQUIRE(lhs == rhs);
        REQUIRE(rhs == lhs);
    }
    SECTION("Equality comparison with nullptr")
    {
        String lhs("Hello");

        REQUIRE(lhs != nullptr);
    }
    SECTION("Two default strings")
    {
        String lhs;
        String rhs;

        REQUIRE(lhs == rhs);
    }
    SECTION("An unitialized string and a c-string")
    {
        String lhs;
        const char* rhs = "Hello";

        REQUIRE(lhs != rhs);
    }
}

TEST_CASE("Copy Functions", "[String], [operations], [copy]")
{
    SECTION("An empty string and a populated c-string")
    {
        String string;
        const char* str = "Hello";

        string.copy(str, String::len(str));

        REQUIRE(string == str);
        REQUIRE(string.length() == 5);
        REQUIRE(string.capacity() == 6);
    }
    SECTION("An empty string and a nullptr")
    {
        String string;
        
        REQUIRE_THROWS_AS(string.copy(nullptr, 10), std::invalid_argument);
    }
    SECTION("Copy a substring into a c-string")
    {
        String string("Hello World");
        String substring("World");
        char* str = new char[6];

        unsigned length = String::copy(string, str, 5, 6);
        str[length] = '\0';

        REQUIRE(str == substring);

        delete [] str;
    }
    SECTION("Copy an uninitiazlied string into a c-string")
    {
        String string;
        char* str;

        REQUIRE_THROWS_AS(String::copy(string, str, 5, 5), std::invalid_argument);
    }
    SECTION("Copy a string into a nullptr")
    {
        String string("Budweiser");

        REQUIRE_THROWS_AS(String::copy(string, nullptr, 5, 5), std::invalid_argument);
    }
}

TEST_CASE("Resize function", "[String], [operations], [resize]")
{
    SECTION("An empty string")
    {
        String string;

        string.resize(100);

        REQUIRE(string.capacity() == 101);
        REQUIRE(string.length() == 0);
    }
    SECTION("A populated string")
    {
        const char* test = "Hello World";
        String string(test);

        string.resize(1000);

        REQUIRE(string.capacity() == 1001);
        REQUIRE(string.length() == String::len(test));
        REQUIRE(string == test);
    }
    SECTION("Resizing to smaller capacity")
    {
        const char* test = "Hello World";
        String string(test);

        string.resize(5);
        
        REQUIRE(string.capacity() == 6);
        REQUIRE(string.length() == 5);
        REQUIRE(string == "Hello");
    }
    SECTION("Resizing to smaller capacity from a reserved string")
    {
        String string(100);

        string.resize(0);

        REQUIRE(string.capacity() == 1);
        REQUIRE(string.length() == 0);
    }
}

TEST_CASE("Reserve function", "[String], [operations], [reserve]")
{
    SECTION("An empty string")
    {
        String string;

        string.reserve(100);

        REQUIRE(string.capacity() == 100);
        REQUIRE(string.length() == 0);
    }
    SECTION("A populated string")
    {
        const char* test = "Hello World";
        String string(test);

        string.reserve(1000);

        REQUIRE(string.capacity() == 1000);
        REQUIRE(string.length() == String::len(test));
        REQUIRE(string == test);
    }
    SECTION("Reserving to a smaller capacity does nothing")
    {
        const char* test = "Hello World";
        String string(test);

        string.reserve(0);

        REQUIRE(string.capacity() == String::len(test) + 1);
        REQUIRE(string.length() == String::len(test));
        REQUIRE(string == test);
    }
}

TEST_CASE("Element access with [] operator", "[String], [operator]")
{
    SECTION("A populated String")
    {
        const char* test = "Hello!";
        String string(test);

        for (unsigned i = 0; i < string.length(); ++i)
        {
            REQUIRE(string[i] == test[i]);
        }
    }
    SECTION("Accessing out of bounds element")
    {
        String string("Hello");

        REQUIRE_THROWS_AS(string[10], out_of_range);
    }
    SECTION("Accessing elements with reverse index")
    {
        const char* test = "!olleH";
        const char* reverse = "Hello!";

        String string(test);

        unsigned int n = 0;
        for (int i = -1; i >= static_cast<int>(string.length() * -1); --i)
        {
            REQUIRE(string[i] == reverse[n]);
            ++n;
        }
    }
    SECTION("Accessing out of bounds element with reverse index")
    {
        String string("Hello!");

        REQUIRE_THROWS_AS(string[-100], out_of_range);
    }
    SECTION("Accessing elements in a const string")
    {
        const char* test = "Hello!";
        const String string(test);

        for (unsigned i = 0; i < string.length(); ++i)
        {
            REQUIRE(string[i] == test[i]);
        }
    }
}

TEST_CASE("Stream operator overlaods", "[String], [operators]")
{
    SECTION("<< operator")
    {
        std::stringstream ss;
        const char* test = "Hello!\t";
        String string(test);

        ss << string;

        REQUIRE(ss.str() == test);
    }
}

TEST_CASE("Custom exceptions", "[String], [exceptions]")
{
    SECTION("Out of range exception")
    {
        String string("Test");
        String message("error, index pos is out of bounds");

        try
        {
            string[1000];
        } 
        catch (const out_of_range& err)
        {
            REQUIRE(err.what() == message);
            REQUIRE(err.index() == 1000);
        }
    }
}

TEST_CASE("Push_back modifier", "[String], [modifiers], [push_back]")
{
    SECTION("A populated list")
    {
        String string("Hell");

        string.push_back('o');
        string.push_back('!');

        REQUIRE(string == "Hello!");
        REQUIRE(string.capacity() == 11);
        REQUIRE(string.length() == 6);
    }
    SECTION("An empty list")
    {
        String string;

        string.push_back('O');
        string.push_back('K');
        string.push_back('!');
        string.push_back('!');


        REQUIRE(string == "OK!!");
        REQUIRE(string.capacity() == 7);
        REQUIRE(string.length() == 4);
    }
}

TEST_CASE("Iterators for element access and string traversal", "[String], [iterators]")
{
    SECTION("A populated string")
    {
        const char* test = "Hello!";
        String string(test);

        unsigned i = 0;
        for(String::iterator it = string.begin(); it != string.end(); ++it)
        {
            REQUIRE(*it == test[i++]);
        }
    }
    SECTION("end() returns a null terminating character")
    {
        String string("Hi");

        REQUIRE(*string.end() == '\0');
    }
    SECTION("Ranged based for loop")
    {
        const char* test = "Hello!";
        String string(test);

        unsigned i = 0;
        for (char& letter : string)
        {
            REQUIRE(letter == test[i++]);
        }
    }
    SECTION("Ranged based for loop on const string")
    {
        const char* test = "Hello!";
        const String string(test);

        unsigned i = 0;
        for (const char& letter : string)
        {
            REQUIRE(letter == test[i++]);
        }
    }
    SECTION("A const qualified populated string")
    {
        const char* test = "Hello!";
        const String string(test);

        unsigned i = 0;
        for(String::const_iterator it = string.cbegin(); it != string.cend(); ++it)
        {
            REQUIRE(*it == test[i++]);
        }
    }
}

TEST_CASE("isupper() to determine string state", "[String], [bool], [python]")
{
    SECTION("A uppercased string")
    {
        String string("HELLO");

        REQUIRE(string.isupper());
    }
    SECTION("A lowercased string")
    {
        String string("hello");

        REQUIRE(!(string.isupper()));
    }
    SECTION("A mixed case string")
    {
        String string("HELlO");
        REQUIRE(!(string.isupper()));
    }
    SECTION("A string with symbols and one uppercased character")
    {
        String string("!@#$%^T");

        REQUIRE(string.isupper());
    }
}
TEST_CASE("islower() to determine string state", "[String], [bool], [python]")
{
    SECTION("A uppercased string")
    {
        String string("HELLO");

        REQUIRE(!string.islower());
    }
    SECTION("A lowercased string")
    {
        String string("hello");

        REQUIRE(string.islower());
    }
    SECTION("A mixed case string")
    {
        String string("helLo");
        REQUIRE(!(string.islower()));
    }
    SECTION("A string with symbols and one lowercased character")
    {
        String string("!@#$%^t");

        REQUIRE(string.islower());
    }
}

TEST_CASE("isnumeric() to determine string state", "[String], [python], [isnumeric]")
{
    SECTION("A numeric string")
    {
        String string("12345");

        REQUIRE(string.isnumeric());
    }
    SECTION("A non-numeric string")
    {
        String string("1234f");

        REQUIRE(!string.isnumeric());
    }
}

TEST_CASE("upper() to change casing of string", "[String], [python], [upper]")
{
    SECTION("A lower cased string")
    {
        String string("hello");

        REQUIRE(string.upper().isupper());
    }
    SECTION("A mixed cased string")
    {
        String string("hE!!o");

        REQUIRE(string.upper().isupper());
    }
}

TEST_CASE("lower() to change casing of string", "[String], [python], [lower]")
{
    SECTION("A upper cased string")
    {
        String string("HELLO");

        REQUIRE(string.lower().islower());
    }
    SECTION("A mixed cased string")
    {
        String string("hE!!O");
        
        REQUIRE(string.lower().islower());
    }
    SECTION("An empty string")
    {
        String string;

        REQUIRE(!(string.lower().islower()));
    }
}