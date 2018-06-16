/*
File: string_tests.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree

https://github.com/AlexanderJDupree/Python-Strings-for-CPP

*/

#include <stdexcept>
#include "catch.hpp"
#include "string.hpp"

TEST_CASE("Constructing Strings", "[String], [constructors]")
{
    SECTION("Default Construction")
    {
        String str;

        REQUIRE(str.length() == 0);
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