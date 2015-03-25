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

using lep::String;
using lep::SocketAddress;
using lep::TestCase;
using lep::TestModule;

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

class TestSocketAddressAccessors : public TestCase
{
  public:
    TestSocketAddressAccessors()
      : TestCase("TestSocketAddressAccessors: test accessors for address and port")
    {
    }

    bool test()
    {
      int port = 4444;
      const char* address = "255.255.255.255";
      SocketAddress sa(address, port);
      return ((sa.address() == address) &&
        (sa.port() == port));
    }
};

class TestSocketAddressSetters : public TestCase
{
  public:
    TestSocketAddressSetters()
      : TestCase("TestSocketAddressSetters: test setters for address and port")
    {
    }

    bool test()
    {
      int port1 = 4444;
      const char* address1 = "123.456.789.012";
      int port2 = 5555;
      const char* address2 = "987.654.321.000";
      SocketAddress sa(address1, port1);
      sa.set_address(address2);
      sa.set_port(port2);
      return ((sa.address() == address2) &&
        (sa.port() == port2));
    }
};

class TestSocketAddressCopyConstructor : public TestCase
{
  public:
    TestSocketAddressCopyConstructor()
      : TestCase("TestSocketAddressCopyConstructor: test copy constructor")
    {
    }

    bool test()
    {
      int port = 4444;
      const char* address = "255.255.255.255";
      SocketAddress sa1(address, port);
      SocketAddress sa2(sa1);
      return ((sa1.address() == sa2.address()) &&
        (sa1.port() == sa2.port()));
    }
};

class TestSocketAddressAssignmentOperator : public TestCase
{
  public:
    TestSocketAddressAssignmentOperator()
      : TestCase("TestSocketAddressAssignmentOperator: test operator=")
    {
    }

    bool test()
    {
      int port = 4444;
      const char* address = "255.255.255.255";
      SocketAddress sa1(address, port);
      SocketAddress sa2;
      sa2 = sa1;
      return ((sa1.address() == sa2.address()) &&
        (sa1.port() == sa2.port()));
    }
};

TestSocketAddress::TestSocketAddress()
  : TestModule("SocketAddress class tester")
{
  add(new TestSocketAddressAny());
  add(new TestSocketAddressLoopback());
  add(new TestSocketAddressNullString());
  add(new TestSocketAddressAccessors());
  add(new TestSocketAddressSetters());
  add(new TestSocketAddressCopyConstructor());
  add(new TestSocketAddressAssignmentOperator());
}

