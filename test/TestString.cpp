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
      char* c = NULL;
      String s1(c);
      String s2 = c;

      return ((s1 == s2) && (s1.length() == 0) && (s2.length() == 0));
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

class TestStringConstructorFromChar : public TestCase
{
  public:
    TestStringConstructorFromChar()
      : TestCase("TestStringConstructorFromChar")
    {
    }

    bool test()
    {
      String s1("a");
      String s2('a');

      return (s1 == s2);
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
      s1 = (char*) NULL;

      return ((s1.length() == 0) && (s1 == ""));
    }
};

class TestStringAssignment6 : public TestCase
{
  public:
    TestStringAssignment6()
      : TestCase("TestStringAssignment6: from char")
    {
    }

    bool test()
    {
      String s1("");
      s1 = 'z';

      return ((s1.length() == 1) && (s1 == "z"));
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
      : TestCase("TestStringConcatenation6: of cstring to a string")
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

class TestStringConcatenation7 : public TestCase
{
  public:
    TestStringConcatenation7()
      : TestCase("TestStringConcatenation7: of char to a string")
    {
    }

    bool test()
    {
      const char c1 = '1';
      String s2 = "abcd";
      String s3 = c1 + s2;

      return (s3 == "1abcd");
    }
};

class TestStringConcatenation8 : public TestCase
{
  public:
    TestStringConcatenation8()
      : TestCase("TestStringConcatenation8: of null char to a string")
    {
    }

    bool test()
    {
      const char c1 = '\0';
      String s2 = "abcd";
      String s3 = c1 + s2;

      return ((s3 == "abcd") && (s3.length() == 4));
    }
};

class TestStringConcatenation9 : public TestCase
{
  public:
    TestStringConcatenation9()
      : TestCase("TestStringConcatenation9: of string to itself")
    {
    }

    bool test()
    {
      String s1 = "qwer";
      s1 = s1 + s1;

      return ((s1 == "qwerqwer"));
    }
};

class TestStringConcatenation10 : public TestCase
{
  public:
    TestStringConcatenation10()
      : TestCase("TestStringConcatenation10: of string to string")
    {
    }

    bool test()
    {
      String s1 = "qwer";
      String s2 = "asdf";
      s1 += s2;

      return ((s1 == "qwerasdf"));
    }
};

class TestStringConcatenation11 : public TestCase
{
  public:
    TestStringConcatenation11()
      : TestCase("TestStringConcatenation11: of cstring to string")
    {
    }

    bool test()
    {
      String s1 = "zxcv";
      const char* s2 = "poiut";
      s1 += s2;

      return ((s1 == "zxcvpoiut"));
    }
};

class TestStringConcatenation12 : public TestCase
{
  public:
    TestStringConcatenation12()
      : TestCase("TestStringConcatenation12: of char to string")
    {
    }

    bool test()
    {
      String s1 = "zxcv";
      const char c2 = 'p';
      s1 += c2;

      return ((s1 == "zxcvp"));
    }
};

class TestStringConcatenation13 : public TestCase
{
  public:
    TestStringConcatenation13()
      : TestCase("TestStringConcatenation13: of string to itself")
    {
    }

    bool test()
    {
      String s1 = "zxcv";
      s1 += s1;

      return (s1 == "zxcvzxcv");
    }
};

class TestStringMegaMix : public TestCase
{
  public:
    TestStringMegaMix()
      : TestCase("TestStringMegaMix: create, copy, assign strings")
    {
    }

    void test1(String& s) {
      s = "12345";
    }

    String test2(String s) {
      String s1 = "qaz";
      return s + s1;
    }

    bool test()
    {
      String s1 = "zxcv";
      test1(s1);
      bool b1 = (s1 == "12345");
      bool b2 = (test2(s1) == "12345qaz");
      String s3 = "hjkl";
      s1 = s3 + "poiuyt";
      bool b3 = (s1 == "hjklpoiuyt");

      return (b1 && b2 && b3);
    }
};

class TestStringIndexOf1 : public TestCase
{
  public:
    TestStringIndexOf1()
      : TestCase("TestStringIndexOf1: of char present")
    {
    }

    bool test()
    {
      String s1 = "zxcv";

      return (s1.indexOf('x') == 1);
    }
};

class TestStringIndexOf2 : public TestCase
{
  public:
    TestStringIndexOf2()
      : TestCase("TestStringIndexOf2: of char absent")
    {
    }

    bool test()
    {
      String s1 = "zxcv";

      return (s1.indexOf('d') == -1);
    }
};

class TestStringIndexOfFromIndex1 : public TestCase
{
  public:
    TestStringIndexOfFromIndex1()
      : TestCase("TestStringIndexOfFromIndex1: of char present")
    {
    }

    bool test()
    {
      String s1 = "zxcvx";

      return (s1.indexOf('x', 2) == 4);
    }
};

class TestStringIndexOfFromIndex2 : public TestCase
{
  public:
    TestStringIndexOfFromIndex2()
      : TestCase("TestStringIndexOfFromIndex2: of char absent")
    {
    }

    bool test()
    {
      String s1 = "zxcv";

      return (s1.indexOf('c', 3) == -1);
    }
};

class TestStringIndexOfFromIndex3 : public TestCase
{
  public:
    TestStringIndexOfFromIndex3()
      : TestCase("TestStringIndexOfFromIndex3: of invalid index")
    {
    }

    bool test()
    {
      String s1 = "zxcv";

      return (s1.indexOf('c', 4) == -1);
    }
};

class TestStringSubstring1 : public TestCase
{
  public:
    TestStringSubstring1()
      : TestCase("TestStringSubstring1: with zero begin index")
    {
    }

    bool test()
    {
      String s1 = "zxcv";

      return (s1.substring(0) == "zxcv");
    }
};

class TestStringSubstring2 : public TestCase
{
  public:
    TestStringSubstring2()
      : TestCase("TestStringSubstring2: with valid begin index")
    {
    }

    bool test()
    {
      String s1 = "zxcvfgthyrew";

      return (s1.substring(4) == "fgthyrew");
    }
};

class TestStringSubstring3 : public TestCase
{
  public:
    TestStringSubstring3()
      : TestCase("TestStringSubstring3: with invalid begin index")
    {
    }

    bool test()
    {
      String s1 = "zxcvfgthyrew";

      return (s1.substring(14) == "");
    }
};

class TestStringSubstring4 : public TestCase
{
  public:
    TestStringSubstring4()
      : TestCase("TestStringSubstring4: with valid begin and end index")
    {
    }

    bool test()
    {
      String s1 = "zxcvfgthyrew";

      return (s1.substring(2, 4) == "cvf");
    }
};

class TestStringSubstring5 : public TestCase
{
  public:
    TestStringSubstring5()
      : TestCase("TestStringSubstring5: with valid begin but invalid end index")
    {
    }

    bool test()
    {
      String s1 = "zxcvfgthyrew";

      return (s1.substring(2, 24) == "cvfgthyrew");
    }
};

class TestStringSubstring6 : public TestCase
{
  public:
    TestStringSubstring6()
      : TestCase("TestStringSubstring6: with begin > end index")
    {
    }

    bool test()
    {
      String s1 = "zxcvfgthyrew";

      return (s1.substring(5, 2) == "");
    }
};

class TestStringSubstring7 : public TestCase
{
  public:
    TestStringSubstring7()
      : TestCase("TestStringSubstring7: of empty string")
    {
    }

    bool test()
    {
      String s1 = "";

      return ((s1.substring(5, 2) == "") && (s1.substring(2) == ""));
    }
};

class TestStringSubstring8 : public TestCase
{
  public:
    TestStringSubstring8()
      : TestCase("TestStringSubstring8: with negative beginIndex")
    {
    }

    bool test()
    {
      String s1 = "987654321`";

      return ((s1.substring(-2) == "") && (s1.substring(-2, -1) == ""));
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
  add(new TestStringConstructorFromChar());
  add(new TestStringCopyConstructor1());
  add(new TestStringCopyConstructor2());
  add(new TestStringAssignment1());
  add(new TestStringAssignment2());
  add(new TestStringAssignment3());
  add(new TestStringAssignment4());
  add(new TestStringAssignment5());
  add(new TestStringAssignment6());
  add(new TestStringAssignment6());
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
  add(new TestStringConcatenation7());
  add(new TestStringConcatenation8());
  add(new TestStringConcatenation9());
  add(new TestStringConcatenation10());
  add(new TestStringConcatenation11());
  add(new TestStringConcatenation12());
  add(new TestStringConcatenation13());
  add(new TestStringMegaMix());
  add(new TestStringIndexOf1());
  add(new TestStringIndexOf2());
  add(new TestStringIndexOfFromIndex1());
  add(new TestStringIndexOfFromIndex2());
  add(new TestStringIndexOfFromIndex3());
  add(new TestStringSubstring1());
  add(new TestStringSubstring2());
  add(new TestStringSubstring3());
  add(new TestStringSubstring4());
  add(new TestStringSubstring5());
  add(new TestStringSubstring6());
  add(new TestStringSubstring7());
  add(new TestStringSubstring8());
}