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
      : TestCase("TestStringEquality")
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
      : TestCase("TestStringInequality")
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
      : TestCase("TestStringLength")
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
      : TestCase("TestStringNullLength")
    {
    }

    bool test()
    {
      String s1 = "";

      return (s1.length() == 0);
    }
};

class TestStringConstructorFromCString1 : public TestCase
{
  public:
    TestStringConstructorFromCString1()
      : TestCase("TestStringConstructorFromCString1: valid cstring")
    {
    }

    bool test()
    {
      String s1("asdfghjkl");
      String s2 = "asdfghjkl";

      return (s1 == s2);
    }
};

class TestStringConstructorFromCString2 : public TestCase
{
  public:
    TestStringConstructorFromCString2()
      : TestCase("TestStringConstructorFromCString2: null cstring")
    {
    }

    bool test()
    {
      String s1(NULL);
      String s2 = NULL;

      return (s1 == s2);
    }
};

class TestStringConstructorFromCString3 : public TestCase
{
  public:
    TestStringConstructorFromCString3()
      : TestCase("TestStringConstructorFromCString2: empty cstring")
    {
    }

    bool test()
    {
      String s1("");
      String s2 = "";

      return ((s1 == s2) && (s1.length() == 0) && (s2.length() == 0));
    }
};

class TestStringCopyConstructor1 : public TestCase
{
  public:
    TestStringCopyConstructor1()
      : TestCase("TestStringCopyConstructor1: valid string")
    {
    }

    bool test()
    {
      String s1("asdfghjkl");
      String s2(s1);

      return (s1 == s2);
    }
};

class TestStringCopyConstructor2 : public TestCase
{
  public:
    TestStringCopyConstructor2()
      : TestCase("TestStringCopyConstructor2: empty string")
    {
    }

    bool test()
    {
      String s1("");
      String s2(s1);

      return (s1 == s2);
    }
};

class TestStringAssignment1 : public TestCase
{
  public:
    TestStringAssignment1()
      : TestCase("TestStringAssignment1: to null string")
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
      : TestCase("TestStringAssignment2: to another string")
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

class TestStringAssignment3 : public TestCase
{
  public:
    TestStringAssignment3()
      : TestCase("TestStringAssignment3: from empty string")
    {
    }

    bool test()
    {
      String s1;
      String s2 = "asdfghjkl";
      s2 = s1;

      return (s2 == s1);
    }
};

class TestStringAssignment4 : public TestCase
{
  public:
    TestStringAssignment4()
      : TestCase("TestStringAssignment4: from empty cstring")
    {
    }

    bool test()
    {
      String s1("asdfghjkl");
      s1 = "";

      return ((s1.length() == 0) && (s1 == ""));
    }
};

class TestStringAssignment5 : public TestCase
{
  public:
    TestStringAssignment5()
      : TestCase("TestStringAssignment5: from null cstring")
    {
    }

    bool test()
    {
      String s1("asdfghjkl");
      s1 = NULL;

      return ((s1.length() == 0) && (s1 == ""));
    }
};

class TestStringFromInt : public TestCase
{
  public:
    TestStringFromInt()
      : TestCase("TestStringFromInt")
    {
    }

    bool test()
    {
      String s1("12345");
      String s2 = String::fromInt(12345);

      return (s1 == s2);
    }
};

class TestStringFromIntWithPad : public TestCase
{
  public:
    TestStringFromIntWithPad()
      : TestCase("TestStringFromIntWithPad")
    {
    }

    bool test()
    {
      String s1("00005");
      String s2 = String::fromInt(5, 5, '0');

      return (s1 == s2);
    }
};

class TestStringToInt : public TestCase
{
  public:
    TestStringToInt()
      : TestCase("TestStringToInt")
    {
    }

    bool test()
    {
      String s1("12345");
      int i1 = s1.toInt();

      return (i1 == 12345);
    }
};

class TestStringToIntStatic : public TestCase
{
  public:
    TestStringToIntStatic()
      : TestCase("TestStringToIntStatic: cstring to int")
    {
    }

    bool test()
    {
      const char* s1 = "12345";
      int i1 = String::toInt(s1);

      return (i1 == 12345);
    }
};

class TestStringConcatenation1 : public TestCase
{
  public:
    TestStringConcatenation1()
      : TestCase("TestStringConcatenation1: of two strings")
    {
    }

    bool test()
    {
      String s1 = "abcd";
      String s2 = "efgh";
      String s3 = s1 + s2;

      return (s3 == "abcdefgh");
    }
};

class TestStringConcatenation2 : public TestCase
{
  public:
    TestStringConcatenation2()
      : TestCase("TestStringConcatenation2: of string with empty string")
    {
    }

    bool test()
    {
      String s1 = "abcd";
      String s2 = "";
      String s3 = s1 + s2;

      return (s3 == "abcd");
    }
};

class TestStringConcatenation3 : public TestCase
{
  public:
    TestStringConcatenation3()
      : TestCase("TestStringConcatenation3: of three strings")
    {
    }

    bool test()
    {
      String s1 = "abcd";
      String s2 = "def";
      String s3 = "123";
      String s4 = s1 + s2 + s3;

      return (s4 == "abcddef123");
    }
};

class TestStringConcatenation4 : public TestCase
{
  public:
    TestStringConcatenation4()
      : TestCase("TestStringConcatenation4: of two strings and one cstring")
    {
    }

    bool test()
    {
      String s1 = "abcd";
      String s2 = "def";
      const char* s3 = "123";
      String s4 = s1 + s2 + s3;

      return (s4 == "abcddef123");
    }
};

class TestStringConcatenation5 : public TestCase
{
  public:
    TestStringConcatenation5()
      : TestCase("TestStringConcatenation5: of string to a cstring")
    {
    }

    bool test()
    {
      String s1 = "abcd";
      const char* s2 = "def";
      String s3 = s1 + s2;

      return (s3 == "abcddef");
    }
};

class TestStringConcatenation6 : public TestCase
{
  public:
    TestStringConcatenation6()
      : TestCase("TestStringConcatenation6: of cstring to a strings")
    {
    }

    bool test()
    {
      const char* s1 = "123";
      String s2 = "abcd";
      String s3 = s1 + s2;

      return (s3 == "123abcd");
    }
};

TestString::TestString()
  : TestModule("String class tester")
{
  add(new TestStringEquality());
  add(new TestStringInequality());
  add(new TestStringLength());
  add(new TestStringNullLength());
  add(new TestStringConstructorFromCString1());
  add(new TestStringConstructorFromCString2());
  add(new TestStringConstructorFromCString3());
  add(new TestStringCopyConstructor1());
  add(new TestStringCopyConstructor2());
  add(new TestStringAssignment1());
  add(new TestStringAssignment2());
  add(new TestStringAssignment3());
  add(new TestStringAssignment4());
  add(new TestStringAssignment5());
  add(new TestStringFromInt());
  add(new TestStringFromIntWithPad());
  add(new TestStringToInt());
  add(new TestStringToIntStatic());
  add(new TestStringConcatenation1());
  add(new TestStringConcatenation2());
  add(new TestStringConcatenation3());
  add(new TestStringConcatenation4());
  add(new TestStringConcatenation5());
  add(new TestStringConcatenation6());
}
