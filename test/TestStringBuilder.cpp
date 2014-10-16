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

#include <fstream>
#include <vector>
#include "TestStringBuilder.h"
#include "../src/StringBuilder.h"
#include "../src/String.h"
#include "../src/SmartPointer.h"

using lepcpplib::StringBuilder;
using lepcpplib::SmartPointer;
using lepcpplib::String;
using lepcpplib::TestCase;
using lepcpplib::TestModule;

class TestStringBuilderAppendCString : public TestCase
{
  public:
    TestStringBuilderAppendCString()
      : TestCase("TestStringBuilderAppendCString: test appending of strings.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This");
      sb.Append(" ");
      sb.Append("is");
      sb.Append(" ");
      sb.Append("a");
      sb.Append(" ");
      sb.Append("test.");

      String s("This is a test.");

      return ((*sb.ToString() == s));
    }
};

class TestStringBuilderAppendCStringOfLength : public TestCase
{
  public:
    TestStringBuilderAppendCStringOfLength()
      : TestCase("TestStringBuilderAppendCStringOfLength: test appending of cstrings of length.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      const char* s1 = "This asdfg";
      const char* s2 = "is qwert";
      const char* s3 = "a zxcv";
      const char* s4 = "test. poiuy";
      sb.Append(s1, 4);
      sb.Append(" ");
      sb.Append(s2, 2);
      sb.Append(" ");
      sb.Append(s3, 1);
      sb.Append(" ");
      sb.Append(s4, 5);

      String s("This is a test.");

      return ((*sb.ToString() == s));
    }
};

class TestStringBuilderAppendCStringWithResize : public TestCase
{
  public:
    TestStringBuilderAppendCStringWithResize()
      : TestCase("TestStringBuilderAppendCStringWithResize: test appending of strings with resize.")
    {
    }

    bool test()
    {
      StringBuilder sb(4);
      sb.Append("This");
      sb.Append(" ");
      sb.Append("is");
      sb.Append(" ");
      sb.Append("a");
      sb.Append(" ");
      sb.Append("test.");

      String s("This is a test.");

      return ((*sb.ToString() == s));
    }
};

class TestStringBuilderAppendCStringAndNumbers : public TestCase
{
  public:
    TestStringBuilderAppendCStringAndNumbers()
      : TestCase("TestStringBuilderAppendCStringAndNumbers: test appending of strings and numbers.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This");
      sb.Append(" ");
      sb.Append("is");
      sb.Append(" ");
      sb.Append("a");
      sb.Append(" ");
      sb.Append("test");
      sb.Append(" ");
      sb.Append(2);
      sb.Append(".");

      String s("This is a test 2.");

      return ((*sb.ToString() == s));
    }
};

class TestStringBuilderAppendString : public TestCase
{
  public:
    TestStringBuilderAppendString()
      : TestCase("TestStringBuilderAppendString: test appending of Strings.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      String s1("This is one part ");
      String s2("and this is the second part.");
      sb.Append(s1);
      sb.Append(s2);

      return ((*sb.ToString() == (s1 + s2)));
    }
};

class TestStringBuilderAppendStringWithEmptyString : public TestCase
{
  public:
    TestStringBuilderAppendStringWithEmptyString()
      : TestCase("TestStringBuilderAppendStringWithEmptyString: test appending of Strings with empty strings.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      String s1("I want to say something!");
      String s2("");
      sb.Append(s1);
      sb.Append(s2);

      return ((*sb.ToString() == (s1 + s2)));
    }
};

class TestStringBuilderIndexOf1 : public TestCase
{
  public:
    TestStringBuilderIndexOf1()
      : TestCase("TestStringBuilderIndexOf1: test IndexOf existent string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("That is a test");
      int result = sb.IndexOf("is");
      return (result == 5);
    }
};

class TestStringBuilderIndexOf2 : public TestCase
{
  public:
    TestStringBuilderIndexOf2()
      : TestCase("TestStringBuilderIndexOf2: test IndexOf non existent string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This is a test");
      int result = sb.IndexOf("has");
      return (result == -1);
    }
};

class TestStringBuilderIndexOf3 : public TestCase
{
  public:
    TestStringBuilderIndexOf3()
      : TestCase("TestStringBuilderIndexOf3: test IndexOf partial existent string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This is a test.");
      int result = sb.IndexOf("test..");
      return (result == -1);
    }
};

class TestStringBuilderIndexOf4 : public TestCase
{
  public:
    TestStringBuilderIndexOf4()
      : TestCase("TestStringBuilderIndexOf4: test IndexOf at beginning of string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This is a test.");
      int result = sb.IndexOf("This");
      return (result == 0);
    }
};

class TestStringBuilderIndexOf5 : public TestCase
{
  public:
    TestStringBuilderIndexOf5()
      : TestCase("TestStringBuilderIndexOf5: test IndexOf at end of string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This is a test.");
      int result = sb.IndexOf("test.");
      return (result == 10);
    }
};

class TestStringBuilderIndexOf6 : public TestCase
{
  public:
    TestStringBuilderIndexOf6()
      : TestCase("TestStringBuilderIndexOf6: test IndexOf char at beginning of string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This is a test.");
      int result = sb.IndexOf("T");
      return (result == 0);
    }
};

class TestStringBuilderIndexOf7 : public TestCase
{
  public:
    TestStringBuilderIndexOf7()
      : TestCase("TestStringBuilderIndexOf7: test IndexOf char at end of string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This is a test.");
      int result = sb.IndexOf(".");
      return (result == 14);
    }
};

class TestStringBuilderIndexOf8 : public TestCase
{
  public:
    TestStringBuilderIndexOf8()
      : TestCase("TestStringBuilderIndexOf8: test IndexOf identical string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This is a test.");
      int result = sb.IndexOf("This is a test.");
      return (result == 0);
    }
};

class TestStringBuilderClear1 : public TestCase
{
  public:
    TestStringBuilderClear1()
      : TestCase("TestStringBuilderClear1: test Clear when empty.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Clear();
      String s = *sb.ToString();
      return (s.length() == 0);
    }
};

class TestStringBuilderClear2 : public TestCase
{
  public:
    TestStringBuilderClear2()
      : TestCase("TestStringBuilderClear2: test Clear when non empty.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This is a test.");
      sb.Clear();
      String s = *sb.ToString();
      return (s.length() == 0);
    }
};

class TestStringBuilderClear3 : public TestCase
{
  public:
    TestStringBuilderClear3()
      : TestCase("TestStringBuilderClear3: test Clear when non empty and write new string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("This is a test.");
      sb.Clear();
      sb.Append("That");
      String s = *sb.ToString();
      return (s == "That");
    }
};

class TestStringBuilderSubstring1 : public TestCase
{
  public:
    TestStringBuilderSubstring1()
      : TestCase("TestStringBuilderSubstring1: test Substring of empty string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      SmartPointer<String> s = sb.Substring(1);
      return (s.IsNull());
    }
};

class TestStringBuilderSubstring2 : public TestCase
{
  public:
    TestStringBuilderSubstring2()
      : TestCase("TestStringBuilderSubstring2: test Substring of valid string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(7);
      return (*s == "asdfgh");
    }
};

class TestStringBuilderSubstring3 : public TestCase
{
  public:
    TestStringBuilderSubstring3()
      : TestCase("TestStringBuilderSubstring3: test Substring with start > string length.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(14);
      return (s.IsNull());
    }
};

class TestStringBuilderSubstring4 : public TestCase
{
  public:
    TestStringBuilderSubstring4()
      : TestCase("TestStringBuilderSubstring4: test Substring with start > end.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(7, 2);
      return (s.IsNull());
    }
};

class TestStringBuilderSubstring5 : public TestCase
{
  public:
    TestStringBuilderSubstring5()
      : TestCase("TestStringBuilderSubstring5: test Substring with invalid end.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(7, 21);
      return (s.IsNull());
    }
};

class TestStringBuilderSubstring6 : public TestCase
{
  public:
    TestStringBuilderSubstring6()
      : TestCase("TestStringBuilderSubstring6: test Substring with negative start.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(-1);
      return (s.IsNull());
    }
};

class TestStringBuilderSubstring7 : public TestCase
{
  public:
    TestStringBuilderSubstring7()
      : TestCase("TestStringBuilderSubstring7: test Substring with negative start valid end.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(-1, 10);
      return (s.IsNull());
    }
};

class TestStringBuilderSubstring8 : public TestCase
{
  public:
    TestStringBuilderSubstring8()
      : TestCase("TestStringBuilderSubstring8: test Substring with valid start negative end.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(1, -1);
      return (s.IsNull());
    }
};

class TestStringBuilderSubstring9 : public TestCase
{
  public:
    TestStringBuilderSubstring9()
      : TestCase("TestStringBuilderSubstring9: test Substring with negative start negative end.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(-2, -1);
      return (s.IsNull());
    }
};

class TestStringBuilderSubstring10 : public TestCase
{
  public:
    TestStringBuilderSubstring10()
      : TestCase("TestStringBuilderSubstring10: test Substring to get entire string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(0);
      return (*s == "qwerty asdfgh");
    }
};

class TestStringBuilderSubstring11 : public TestCase
{
  public:
    TestStringBuilderSubstring11()
      : TestCase("TestStringBuilderSubstring11: test Substring to get entire string with end.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(0, 13);
      return (*s == "qwerty asdfgh");
    }
};

class TestStringBuilderSubstring12 : public TestCase
{
  public:
    TestStringBuilderSubstring12()
      : TestCase("TestStringBuilderSubstring11: test Substring with valid start and end.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("qwerty asdfgh");
      SmartPointer<String> s = sb.Substring(1, 5);
      return (*s == "wert");
    }
};

class TestStringBuilderLength1 : public TestCase
{
  public:
    TestStringBuilderLength1()
      : TestCase("TestStringBuilderLength1: test Length when empty.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      return (sb.Length() == 0);
    }
};

class TestStringBuilderLength2 : public TestCase
{
  public:
    TestStringBuilderLength2()
      : TestCase("TestStringBuilderLength2: test Length after Clear.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("asdfg zxcvb");
      bool t1 = sb.Length() == 11;
      sb.Clear();
      bool t2 = sb.Length() == 0;
      return (t1 && t2);
    }
};

class TestStringBuilderLength3 : public TestCase
{
  public:
    TestStringBuilderLength3()
      : TestCase("TestStringBuilderLength3: test Length with continuous append.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("asdfg");
      bool t1 = sb.Length() == 5;
      sb.Append("qwert");
      bool t2 = sb.Length() == 10;
      return (t1 && t2);
    }
};

class TestStringBuilderRemove1 : public TestCase
{
  public:
    TestStringBuilderRemove1()
      : TestCase("TestStringBuilderRemove1: test Remove from beginning.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("asdfgqwert");
      sb.Remove(0, 3);
      return (*sb.ToString() == "fgqwert");
    }
};

class TestStringBuilderRemove2 : public TestCase
{
  public:
    TestStringBuilderRemove2()
      : TestCase("TestStringBuilderRemove2: test Remove from middle.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("asdfgqwert");
      sb.Remove(1, 4);
      return (*sb.ToString() == "agqwert");
    }
};

class TestStringBuilderRemove3 : public TestCase
{
  public:
    TestStringBuilderRemove3()
      : TestCase("TestStringBuilderRemove3: test Remove from single character string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("a");
      sb.Remove(0, 1);
      return (*sb.ToString() == "");
    }
};

class TestStringBuilderRemove4 : public TestCase
{
  public:
    TestStringBuilderRemove4()
      : TestCase("TestStringBuilderRemove4: test Remove entire string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("asdfgqwert");
      sb.Remove(0, 10);
      return (*sb.ToString() == "");
    }
};

class TestStringBuilderRemove5 : public TestCase
{
  public:
    TestStringBuilderRemove5()
      : TestCase("TestStringBuilderRemove5: test Remove from end of string.")
    {
    }

    bool test()
    {
      StringBuilder sb;
      sb.Append("asdfgqwert");
      sb.Remove(5, 10);
      return (*sb.ToString() == "asdfg");
    }
};

TestStringBuilder::TestStringBuilder()
  : TestModule("StringBuilder class tester")
{
  add(new TestStringBuilderAppendCString());
  add(new TestStringBuilderAppendCStringOfLength());
  add(new TestStringBuilderAppendCStringWithResize());
  add(new TestStringBuilderAppendCStringAndNumbers());
  add(new TestStringBuilderAppendString());
  add(new TestStringBuilderAppendStringWithEmptyString());
  add(new TestStringBuilderIndexOf1());
  add(new TestStringBuilderIndexOf2());
  add(new TestStringBuilderIndexOf3());
  add(new TestStringBuilderIndexOf4());
  add(new TestStringBuilderIndexOf5());
  add(new TestStringBuilderIndexOf6());
  add(new TestStringBuilderIndexOf7());
  add(new TestStringBuilderIndexOf8());
  add(new TestStringBuilderClear1());
  add(new TestStringBuilderClear2());
  add(new TestStringBuilderClear3());
  add(new TestStringBuilderSubstring1());
  add(new TestStringBuilderSubstring2());
  add(new TestStringBuilderSubstring3());
  add(new TestStringBuilderSubstring4());
  add(new TestStringBuilderSubstring5());
  add(new TestStringBuilderSubstring6());
  add(new TestStringBuilderSubstring7());
  add(new TestStringBuilderSubstring8());
  add(new TestStringBuilderSubstring9());
  add(new TestStringBuilderSubstring10());
  add(new TestStringBuilderSubstring11());
  add(new TestStringBuilderSubstring12());
  add(new TestStringBuilderLength1());
  add(new TestStringBuilderLength2());
  add(new TestStringBuilderLength3());
  add(new TestStringBuilderRemove1());
  add(new TestStringBuilderRemove2());
  add(new TestStringBuilderRemove3());
  add(new TestStringBuilderRemove4());
  add(new TestStringBuilderRemove5());
}
