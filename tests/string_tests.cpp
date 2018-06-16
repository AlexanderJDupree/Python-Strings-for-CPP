/*
File: string_tests.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree

https://github.com/AlexanderJDupree/Python-Strings-for-CPP

*/

#include <iostream>
#include "catch.hpp"
#include "string.hpp"

TEST_CASE("Constructing Strings", "[String], [constructors]")
{
    SECTION("Default Construction")
    {
        String str;

        REQUIRE(str.length() == 0);
    }
}