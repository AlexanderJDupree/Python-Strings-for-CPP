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
        REQUIRE(str.capacity() == 0);
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

        REQUIRE(str.capacity() == 0);
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
        String string("Y'all");

        try
        {
            string[1000];
        } 
        catch (const out_of_range& err)
        {
            REQUIRE(err.index() == 1000);
        }
    }
}