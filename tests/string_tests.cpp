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
#include <vector>
#include "catch.hpp"
#include "sstring.h"

TEST_CASE("Constructing Strings", "[SString], [constructors]")
{
    SECTION("Default Construction")
    {
        SString str;

        REQUIRE(str.length() == 0);
        REQUIRE(str.size() == 1);
    }
    SECTION("Construction with a C-string")
    {
        const char* test = "Hello";
        SString str(test);

        REQUIRE(str == test);
        REQUIRE(str.length() == std::strlen(test));
        REQUIRE(str.size() == std::strlen(test) + 1);
    }
    SECTION("Construction with a nullptr, creates empty string")
    {
        SString str(nullptr);

        REQUIRE(str.length() == 0);
        REQUIRE(str.size() == 1);
    }
    SECTION("Copy construction")
    {
        SString origin("Hello");
        SString copy(origin);

        REQUIRE(copy == origin);
    }
    SECTION("Copy construction with empty string")
    {
        SString origin;
        SString copy(origin);

        REQUIRE(copy == origin);
    }
    SECTION("Fill construction")
    {
        SString string(5, '!');

        REQUIRE(string == "!!!!!");
        REQUIRE(string.length() == 5);
        REQUIRE(string.size() == 6);
    }
    SECTION("Buffer construction")
    {
        char buffer[100];
        for(unsigned i = 0; i < 10; ++i)
        {
            buffer[i] = 'A';
        }

        SString string(buffer, 10);

        REQUIRE(string == "AAAAAAAAAA");
        REQUIRE(string.length() == 10);
        REQUIRE(string.size() == 11);
    }
    /*
    SECTION("Range based construction")
    {
        std::vector<char> letters { 'a', 'b', 'c', 'd' };
        SString string(letters.begin(), letters.end());

        REQUIRE(string == "abcd");
    }
    SECTION("Range based construction with empty container")
    {
        std::vector<char> letters;
        SString string(letters.begin(), letters.end());

        REQUIRE(string.empty());
    }
    SECTION("Ranged based construciton with empty string")
    {
        SString empty;
        SString string(empty.begin(), empty.end());

        REQUIRE(string.empty());
    }
    SECTION("Initializer list construction")
    {
        SString string { 'a', 'b', 'c', 'd' };

        REQUIRE(string == "abcd");
        REQUIRE(string.length() == 4);
        REQUIRE(string.capacity() == 5);
    }
    SECTION("Initializer list with string literals")
    {
        SString string { "one", "two", "three", "four" };

        REQUIRE(string == "one two three four");
        REQUIRE(string.length() == 18);
        REQUIRE(string.capacity() == 31);
    }
    SECTION("Initializer list with comma seperated delimiter")
    {
        SString string({"one", "two", "three"}, ',');

        REQUIRE(string == "one,two,three");
    }
    */
}

TEST_CASE("Capacity functions", "[SString], [capacity]")
{
    SECTION("Size of an empty String")
    {
        SString str;

        REQUIRE(str.length() == 0);
    }
    SECTION("Capcacity of an empty String")
    {
        SString str;

        REQUIRE(str.size() == 1);
    }
    SECTION("Test if string is empty")
    {
        SString str;

        REQUIRE(str.empty());
    }
}

TEST_CASE("Substring and truncation", "[SString], [operations], [substring], [truncate]")
{
    SECTION("Valid substring")
    {
        SString str("Hello World");

        REQUIRE(str.substring(1, 4) == "ello");
    }
    SECTION("Invalid Substring")
    {
        SString str("Hello");

        try
        {
            str.substring(0, 10);
        }
        catch(const invalid_substring& err)
        {
            REQUIRE(err.what() == SString("Error, substring bounds do not exist"));
        }
    }
    SECTION("Truncating a string to a specific width")
    {
        SString str("Hello");

        REQUIRE(str.truncate(3) == "Hel");
        REQUIRE(str.truncate(8) == "Hello    ");
    }
}

TEST_CASE("Relational Operators", "[SString], [relational], [operators], [overloads]")
{
    SECTION("Equality operators on two identical strings")
    {
        SString lhs("Hello");
        SString rhs("Hello");

        REQUIRE(lhs == rhs);
    }
    SECTION("Inequality operators")
    {
        SString lhs("Hello");
        SString rhs;

        REQUIRE(lhs != rhs);
    }
    SECTION("Equality comparison with c-strings")
    {
        SString lhs("Hello");
        const char* rhs = "Hello";

        REQUIRE(lhs == rhs);
        REQUIRE(rhs == lhs);
    }
    SECTION("Equality comparison with nullptr")
    {
        SString lhs("Hello");

        REQUIRE(lhs != nullptr);
    }
    SECTION("Two default strings")
    {
        SString lhs;
        SString rhs;

        REQUIRE(lhs == rhs);
    }
    SECTION("An unitialized string and a c-string")
    {
        SString lhs;
        const char* rhs = "Hello";

        REQUIRE(lhs != rhs);
    }
    SECTION("Two differing strings")
    {
        SString lhs("Hello");
        SString rhs("Hello World");

        REQUIRE(lhs != rhs);
    }
    SECTION("Freestanding equality")
    {
        SString rhs("Test");
        REQUIRE("not test" != rhs);
    }
}

TEST_CASE("Comparison operators with strings", "[SString], [comparison], [operators]")
{
    SECTION("Freestanding comparisons")
    {
        SString str1("aaa");
        SString str2("bbbb");
        const char* cstring("ccc");

        REQUIRE(cstring > str1);
        REQUIRE_FALSE(str1 > cstring);
        REQUIRE_FALSE(cstring < str1);
        REQUIRE(str2 > str1);
        REQUIRE_FALSE(str2 < str1);
    }
}

TEST_CASE("Element access with [] operator", "[SString], [operator]")
{
    SECTION("A populated SString")
    {
        const char* test = "Hello!";
        SString string(test);

        for (unsigned i = 0; i < string.length(); ++i)
        {
            REQUIRE(string[i] == test[i]);
        }
    }
    SECTION("Accessing out of bounds element")
    {
        SString string("Hello");

        try 
        {
            string[10];
        } 
        catch (const bad_index& err) 
        {
            REQUIRE(err.index() == 10);
            REQUIRE(err.what() == SString("Provided Index is out of bounds"));
        }
    }
    SECTION("Accessing elements with reverse index")
    {
        const char* test = "!olleH";
        const char* reverse = "Hello!";

        SString string(test);

        unsigned n = 0;
        for (int i = -1; i >= (int)string.length() * -1; --i)
        {
            REQUIRE(string[i] == reverse[n++]);
        }
    }
    SECTION("Accessing out of bounds element with reverse index")
    {
        SString string("Hello!");

        REQUIRE_THROWS_AS(string[-100], bad_index);
    }
}

TEST_CASE("Stream operator overlaods", "[SString], [operators]")
{
    SECTION("<< operator")
    {
        std::stringstream ss;
        const char* test = "Hello!\t";
        SString string(test);

        ss << string;

        REQUIRE(ss.str() == test);
    }
}


TEST_CASE("Iterators for element access and string traversal", "[SString], [iterators]")
{
    SECTION("A populated string")
    {
        const char* test = "Hello!";
        SString string(test);

        unsigned i = 0;
        for(SString::const_iterator it = string.begin(); it != string.end(); ++it)
        {
            REQUIRE(*it == test[i++]);
        }
    }
    SECTION("end() returns a null terminating character")
    {
        SString string("Hi");

        REQUIRE(*string.end() == '\0');
    }
    SECTION("Ranged based for loop on const string")
    {
        const char* test = "Hello!";
        const SString string(test);

        unsigned i = 0;
        for (const char& letter : string)
        {
            REQUIRE(letter == test[i++]);
        }
    }
}

TEST_CASE("is_upper() to determine string state", "[SString], [bool], [python]")
{
    SECTION("A uppercased string")
    {
        SString string("HELLO");

        REQUIRE(string.is_upper());
    }
    SECTION("A lowercased string")
    {
        SString string("hello");

        REQUIRE_FALSE(string.is_upper());
    }
    SECTION("A mixed case string")
    {
        SString string("HELlO");
        REQUIRE(!(string.is_upper()));
    }
    SECTION("A string with symbols and one uppercased character")
    {
        SString string("!@#$%^T");

        REQUIRE(string.is_upper());
    }
}
TEST_CASE("strip() to strip certain char in the begining and end of SString")
{
	SECTION("full of strip seed")
	{
		SString string("\n\n\n\n");
		REQUIRE(string.strip('\n') == "\0");
	}
	SECTION("only at left side")
	{
		SString string("  Hello");
		REQUIRE(string.strip(' ') == "Hello");
	}
	SECTION("only at the end")
	{
		SString string("Hello   ");
		REQUIRE(string.strip(' ') == "Hello");
	}
	SECTION("at both sides")
	{
		SString string("  H  ");
		REQUIRE(string.strip(' ') == "H");
	}
	SECTION("null terminator used as strip seed")
	{
		SString string("hello");
		REQUIRE_THROWS_WITH(string.strip('\0'), "null terminator cannot be used as strip seed!");
	}
}
/*
TEST_CASE("islower() to determine string state", "[SString], [bool], [python]")
{
    SECTION("A uppercased string")
    {
        SString string("HELLO");

        REQUIRE(!string.islower());
    }
    SECTION("A lowercased string")
    {
        SString string("hello");

        REQUIRE(string.islower());
    }
    SECTION("A mixed case string")
    {
        SString string("helLo");
        REQUIRE(!(string.islower()));
    }
    SECTION("A string with symbols and one lowercased character")
    {
        SString string("!@#$%^t");

        REQUIRE(string.islower());
    }
}

TEST_CASE("isnumeric() to determine string state", "[SString], [python], [isnumeric]")
{
    SECTION("A numeric string")
    {
        SString string("12345");

        REQUIRE(string.isnumeric());
    }
    SECTION("A non-numeric string")
    {
        SString string("1234f");

        REQUIRE(!string.isnumeric());
    }
}

TEST_CASE("upper() to change casing of string", "[SString], [python], [upper]")
{
    SECTION("A lower cased string")
    {
        SString string("hello");

        REQUIRE(string.upper().is_upper());
    }
    SECTION("A mixed cased string")
    {
        SString string("hE!!o");

        REQUIRE(string.upper().is_upper());
    }
}

TEST_CASE("lower() to change casing of string", "[SString], [python], [lower]")
{
    SECTION("A upper cased string")
    {
        SString string("HELLO");

        REQUIRE(string.lower().islower());
    }
    SECTION("A mixed cased string")
    {
        SString string("hE!!O");
        
        REQUIRE(string.lower().islower());
    }
    SECTION("An empty string")
    {
        SString string;

        REQUIRE(!(string.lower().islower()));
    }
}

TEST_CASE("swapcase() to change casing of a string", "[SString], [python], [swapcase]")
{
    SECTION("An uppercased string")
    {
        SString string("HELLO");

        REQUIRE(string.swapcase().islower());
    }
    SECTION("A lower cased string")
    {
        SString string("hello");

        REQUIRE(string.swapcase().is_upper());
    }
    SECTION("A mixed cased string")
    {
        SString string("He!Lo");

        REQUIRE(string.swapcase() == "hE!lO");
    } 
}

TEST_CASE("Appending to the end of a string", "[SString], [modifiers], [append]")
{
    SECTION("A populated string and a c-string")
    {
        SString string("Hello, ");
        const char* str = "World!";

        REQUIRE(string.append(str) == "Hello, World!");
    }
    SECTION("Two populated strings")
    {
        SString fname("Alex ");
        SString lname("DuPree");

        REQUIRE(fname.append(lname) == "Alex DuPree");
    }
    SECTION("A populated string and an empty one")
    {
        SString string("Hello");
        SString empty;

        REQUIRE(string.append(empty) == "Hello");
    }
    SECTION("Appending to the end of a empty string")
    {
        SString empty;
        SString string("Hello");

        REQUIRE(empty.append(string) == "Hello");
    }
    SECTION("Appending fill characters")
    {
        SString string("Hey");

        REQUIRE(string.append(4, 'y') == "Heyyyyy");
    }
    SECTION("Appending with iterators")
    {
        std::vector<char> letters {'A', 'B', 'C', 'D' };

        SString string;

        string.append(letters.begin(), letters.end());

        REQUIRE(string == "ABCD");
    }
    SECTION("Appending with an initializer list")
    {
        SString string;

        REQUIRE(string.append({ 'A', 'B', 'C', 'D' }) == "ABCD");
    }
    SECTION("Appending a substring")
    {
        SString string;
        const char* str = "Hello World";

        REQUIRE(string.append(str, 5) == "Hello");
    }
    SECTION("Appending a substring larger than the origin")
    {
        SString string;
        const char* str = "Hello World";

        REQUIRE(string.append(str, 500) == str);
    }
    SECTION("Appending a character")
    {
        SString string;

        REQUIRE(string.append('A') == "A");
    }
}

TEST_CASE("splitting string into a list", "[SString], [python], [split]")
{
    SECTION("A space delimited string")
    {
        SString string("one two three");
        SString::list words { SString("one"), SString("two"), SString("three") };

        REQUIRE(string.split() == words);
    }
    SECTION("A comma delimited string")
    {
        SString string ("one, two, three");
        SString::list words { SString("one"), SString("two"), SString("three") };

        REQUIRE(string.split(',') == words);
    }
    SECTION("Too many commas")
    {
        SString string("one, two, three,");
        SString::list words { SString("one"), SString("two"), SString("three"), SString() };

        REQUIRE(string.split(',') == words);
    }
}

TEST_CASE("stripping trailing characters off string", "[SString], [python], [strip]")
{
    SECTION("strip trailing whitespace")
    {
        SString string("  stuff  ");
        
        REQUIRE(string.strip() == "stuff");
    }
    SECTION("Strip trailing characters")
    {
        SString string("---  stuff  -");

        REQUIRE(string.strip('-') == "  stuff  ");
    }
}
*/

TEST_CASE("Using the copy-assignment operator" , "[SString], [operator], [copy]")
{
    SECTION("A populated string")
    {
        SString string("Hello!");

        SString str("junk");

        str = string;

        REQUIRE(str == string);
    }
    SECTION("An empty string")
    {
        SString string;

        SString str("Junk");

        str = string;

        REQUIRE(str == string);
    }
    SECTION("Reassign to a c-string")
    {
        SString str("junk");

        str = "Hello World";

        REQUIRE(str == "Hello World");
    }
}

TEST_CASE("String concatenation", "[SString], [operator], [concatenation]")
{
    SECTION("Concatenate c-strings with SString")
    {
        const char* cstring = "World";
        SString str = "Hello ";

        REQUIRE(str + cstring == "Hello World");
        REQUIRE(cstring + str == "WorldHello ");
    }
    SECTION("Concatenate two SStrings")
    {
        SString str1 = "Hello ";
        SString str2 = "World";

        REQUIRE(str1 + str2 == "Hello World");
    }
}

TEST_CASE("String construction with >> operator", "[SString], [operator], [read_input]")
{
    SECTION("Using istringstream to simulate input") 
    {
        SString str;
        std::istringstream in;

        in.str("test");
        in >> str;

        REQUIRE(str == "test");
    }
}

TEST_CASE("Testing whether the string is numeric", "[SString], [python], [isnumeric]") {
    SECTION("Integer number") {
        SString str("1234");

        REQUIRE(str.isnumeric());
    }
    SECTION("Binary number") {
        SString str("0b01010");

        REQUIRE(str.isnumeric());
    }
    SECTION("Octal number") {
        SString str("0o1276");

        REQUIRE(str.isnumeric());
    }
    SECTION("Hexadecimal number") {
        SString str("0xaef");

        REQUIRE(str.isnumeric());
    }
    SECTION("Not a number") {
        SString str("ab123");

        REQUIRE(!(str.isnumeric()));
    }
}
