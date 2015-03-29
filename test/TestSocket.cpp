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

#include "TestSocket.h"
#include "../src/Socket.h"
#include "../src/SocketAddress.h"
#include "../src/String.h"

using lep::Socket;
using lep::SmartPointer;
using lep::String;
using lep::SocketAddress;
using lep::TestCase;
using lep::TestModule;

class TestSocketAcceptFailWithoutRootAccess : public TestCase
{
  public:
    TestSocketAcceptFailWithoutRootAccess()
      : TestCase("TestSocketAcceptFailWithoutRootAccess: test socket accept on port needing root")
    {
    }

    bool test()
    {
      int port = 80;
      const char* address = "127.0.0.1";
      SocketAddress sa1(address, port);
      SocketAddress sa2;
      Socket s(Socket::kInternet, Socket::kStream, Socket::kTcp);
      s.Bind(sa1);
      
      SmartPointer<Socket> sp = s.Accept(1);
      return (sp == NULL);
    }
};

TestSocket::TestSocket()
  : TestModule("Socket class tester")
{
  add(new TestSocketAcceptFailWithoutRootAccess());
}

