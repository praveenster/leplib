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

using lepcpplib::StringBuilder;
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

TestStringBuilder::TestStringBuilder()
  : TestModule("StringBuilder class tester")
{
  add(new TestStringBuilderAppendCString());
  add(new TestStringBuilderAppendCStringWithResize());
  add(new TestStringBuilderAppendCStringAndNumbers());
  add(new TestStringBuilderAppendString());
  add(new TestStringBuilderAppendStringWithEmptyString());
}
