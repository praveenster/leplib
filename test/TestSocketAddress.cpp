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

#include "TestSocketAddress.h"
#include "../src/SocketAddress.h"
#include "../src/String.h"

using lepcpplib::String;
using lepcpplib::SocketAddress;
using lepcpplib::TestCase;
using lepcpplib::TestModule;

class TestSocketAddressAny : public TestCase
{
  public:
    TestSocketAddressAny()
      : TestCase("TestSocketAddressAny: test ANY address")
    {
    }

    bool test()
    {
      int port = 5678;
      SocketAddress sa(0, port);
      return (*sa.ToString() == *(*SocketAddress::ForAny(port)).ToString());
    }
};

class TestSocketAddressLoopback : public TestCase
{
  public:
    TestSocketAddressLoopback()
      : TestCase("TestSocketAddressLoopback: test loopback address")
    {
    }

    bool test()
    {
      int port = 65532;
      SocketAddress sa("127.0.0.1", port);
      return (*sa.ToString() == *(*SocketAddress::ForLoopback(port)).ToString());
    }
};

class TestSocketAddressNullString : public TestCase
{
  public:
    TestSocketAddressNullString()
      : TestCase("TestSocketAddressNullString: test null string address")
    {
    }

    bool test()
    {
      int port = 4444;
      SocketAddress sa("", port);
      return (*sa.ToString() == *(*SocketAddress::ForAny(port)).ToString());
    }
};
TestSocketAddress::TestSocketAddress()
  : TestModule("SocketAddress class tester")
{
  add(new TestSocketAddressAny());
  add(new TestSocketAddressLoopback());
  add(new TestSocketAddressNullString());
}
