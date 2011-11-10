/*
  Copyright (c) 2011 Neevarp Yhtroom

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "TestString.h"

using lepcpplib::String;
using lepcpplib::TestCase;
using lepcpplib::TestModule;

class TestStringEquality : public TestCase
{
  public:
    TestStringEquality()
      : TestCase("Test string equality")
    {
    }

    bool test()
    {
      String s1 = "asdfghjkl";
      String s2 = "asdfghjkl";

      return (s1 == s2);
    }
};

class TestStringInequality : public TestCase
{
  public:
    TestStringInequality()
      : TestCase("Test string inequality")
    {
    }

    bool test()
    {
      String s1 = "asdfghjkl";
      String s2 = "bsdfghjkl";

      return (s1 != s2);
    }
};

class TestStringLength : public TestCase
{
  public:
    TestStringLength()
      : TestCase("Test string length")
    {
    }

    bool test()
    {
      String s1 = "qwerty";

      return (s1.length() == 6);
    }
};

class TestStringNullLength : public TestCase
{
  public:
    TestStringNullLength()
      : TestCase("Test null string length")
    {
    }

    bool test()
    {
      String s1 = "";

      return (s1.length() == 0);
    }
};

class TestStringConstructorFromCString : public TestCase
{
  public:
    TestStringConstructorFromCString()
      : TestCase("Test string ctor from cstring")
    {
    }

    bool test()
    {
      String s1("asdfghjkl");
      String s2 = "asdfghjkl";

      return (s1 == s2);
    }
};

class TestStringCopyConstructor : public TestCase
{
  public:
    TestStringCopyConstructor()
      : TestCase("Test string copy ctor")
    {
    }

    bool test()
    {
      String s1("asdfghjkl");
      String s2 = "asdfghjkl";

      return (s1 == s2);
    }
};

class TestStringAssignment1 : public TestCase
{
  public:
    TestStringAssignment1()
      : TestCase("Test string assignment to null string")
    {
    }

    bool test()
    {
      String s1;
      String s2 = "asdfghjkl";
      s1 = s2;

      return (s1 == s2);
    }
};

class TestStringAssignment2 : public TestCase
{
  public:
    TestStringAssignment2()
      : TestCase("Test string assignment to another string")
    {
    }

    bool test()
    {
      String s1("qwerty");
      String s2 = "asdfghjkl";
      s1 = s2;

      return (s1 == s2);
    }
};

TestString::TestString()
  : TestModule("String class tester")
{
  add(new TestStringEquality());
  add(new TestStringInequality());
  add(new TestStringLength());
  add(new TestStringNullLength());
  add(new TestStringConstructorFromCString());
  add(new TestStringCopyConstructor());
  add(new TestStringAssignment1());
  add(new TestStringAssignment2());
}
