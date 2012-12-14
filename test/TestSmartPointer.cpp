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

#include <string>
#include "TestSmartPointer.h"
#include "../src/SmartPointer.h"

using std::string;
using lepcpplib::SmartPointer;
using lepcpplib::TestCase;
using lepcpplib::TestModule;

class TestSmartPointerReferenceCounting : public TestCase
{
  public:
    class TestFixture
    {
      public:
        TestFixture()
          : c(0), d(0)
        {
        }

        void run()
        {
          f1();
        }

      private:
        void f3(SmartPointer<string> a)
        {
          SmartPointer<string> b = a;
          b->append("in f3. ");
        }

        void f2(SmartPointer<string> a)
        {
          a->append("in f2. ");
        }

        void f1()
        {
          string* s = new string("Hello!");
          SmartPointer<string> s1(s);
          d = c = s1;
          f2(s1);
          f3(s1);
        }

      private:
        SmartPointer<string> c;
        SmartPointer<string> d;
    };

    TestSmartPointerReferenceCounting()
      : TestCase("TestSmartPointerReferenceCounting: test reference counting mechanishm.")
    {
    }

    bool test()
    {
      // create the test fixture and call its entry point. this will call 
      // f1 and it creates the string, thereby increasing its reference count.
      // but it does not delete the pointer, allowing it to get deleted 
      // automatically when the fixture is deleted.
      TestFixture* t = new TestFixture();
      t->run();
      delete t;

      // if there is no memory leak, everything should be ok!
      // if there is a double delete there will be a seg fault.
      return true;
    }
};

class TestSmartPointerDereference : public TestCase
{
  public:
    TestSmartPointerDereference()
      : TestCase("TestSmartPointerDereference: test dereferencing.")
    {
    }

    bool test()
    {
      string* s1 = new string("Hello!");
      string s2("Hello!");
      SmartPointer<string> s3(s1);

      return ((*s1).compare(s2) == 0);
    }
};

class TestSmartPointerEquality1 : public TestCase
{
  public:
    TestSmartPointerEquality1()
      : TestCase("TestSmartPointerEquality1: test same pointed values.")
    {
    }

    bool test()
    {
      string* s1 = new string("Hello!");
      SmartPointer<string> s2(s1);
      SmartPointer<string> s3(s2);

      return (s2 == s3);
    }
};

class TestSmartPointerEquality2 : public TestCase
{
  public:
    TestSmartPointerEquality2()
      : TestCase("TestSmartPointerEquality2: test different pointed values.")
    {
    }

    bool test()
    {
      string* s1 = new string("Hello!");
      string* s2 = new string("Hello!");
      SmartPointer<string> s3(s1);
      SmartPointer<string> s4(s2);

      return !(s3 == s4);
    }
};

class TestSmartPointerEquality3 : public TestCase
{
  public:
    TestSmartPointerEquality3()
      : TestCase("TestSmartPointerEquality3: test different pointed values.")
    {
    }

    bool test()
    {
      string* s1 = new string("Hello!");
      string* s2 = new string("Hello!");
      SmartPointer<string> s3(s1);
      SmartPointer<string> s4(s2);

      return (s3 != s4);
    }
};

class TestSmartPointerEquality4 : public TestCase
{
  public:
    TestSmartPointerEquality4()
      : TestCase("TestSmartPointerEquality4: test null pointer with null smartpointer.")
    {
    }

    bool test()
    {
      string* s1 = new string("Hello!");
      SmartPointer<string> s3(s1);
      SmartPointer<string> s4(0);

      return (s3 != s4);
    }
};

class TestSmartPointerEquality5 : public TestCase
{
  public:
    TestSmartPointerEquality5()
      : TestCase("TestSmartPointerEquality5: test null pointer.")
    {
    }

    bool test()
    {
      string* s1 = new string("Hello!");
      SmartPointer<string> s3(s1);

      return (s3 != 0);
    }
};

class TestSmartPointerEquality6 : public TestCase
{
  public:
    TestSmartPointerEquality6()
      : TestCase("TestSmartPointerEquality6: compare two null pointers.")
    {
    }

    bool test()
    {
      SmartPointer<string> s1(0);
      SmartPointer<string> s2(0);

      return (s1 == s2);
    }
};

class TestSmartPointerIsNull1 : public TestCase
{
  public:
    TestSmartPointerIsNull1()
      : TestCase("TestSmartPointerIsNull1: test if null pointer.")
    {
    }

    bool test()
    {
      SmartPointer<string> s1(0);

      return (s1.IsNull());
    }
};

class TestSmartPointerIsNull2 : public TestCase
{
  public:
    TestSmartPointerIsNull2()
      : TestCase("TestSmartPointerIsNull2: test if not null pointer.")
    {
    }

    bool test()
    {
      string* s1 = new string("Hello!");
      SmartPointer<string> s2(s1);

      return !(s2.IsNull());
    }
};
class TestSmartPointerAssignment : public TestCase
{
  public:
    TestSmartPointerAssignment()
      : TestCase("TestSmartPointerAssignment: test assignment operator.")
    {
    }

    bool test()
    {
      string* s = new string("Hello!");
      SmartPointer<string> s1(s);
      SmartPointer<string> a(0);
      SmartPointer<string> b(0);

      a = b = s1;
      return ((a->compare(b->c_str()) == 0) &&
        ((b->compare(s1->c_str()) == 0)));
    }
};

TestSmartPointer::TestSmartPointer()
  : TestModule("SmartPointer class tester")
{
  add(new TestSmartPointerAssignment());
  add(new TestSmartPointerReferenceCounting());
  add(new TestSmartPointerDereference());
  add(new TestSmartPointerEquality1());
  add(new TestSmartPointerEquality2());
  add(new TestSmartPointerEquality3());
  add(new TestSmartPointerEquality4());
  add(new TestSmartPointerEquality5());
  add(new TestSmartPointerEquality6());
  add(new TestSmartPointerIsNull1());
  add(new TestSmartPointerIsNull2());
}
