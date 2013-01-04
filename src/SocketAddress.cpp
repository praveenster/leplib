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

#include "SocketAddress.h"

#ifdef WIN32
#include "winsock2.h"
#include "Ws2tcpip.h"
#define socklen_t int
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#endif


namespace lepcpplib {
  SocketAddress::SocketAddress(const String& address, int port)
    : opaque_(0)
  {
    if (address.length() == 0) {
      Initialize(INADDR_ANY, port);
    }
    else {
      Initialize(inet_addr(address.toCharArray()), port);
    }
  }

  SocketAddress::SocketAddress(int address, int port)
    : opaque_(0)
  {
    Initialize(address, port);
  }

  SocketAddress::~SocketAddress()
  {
    delete (sockaddr_in*)opaque_;
  }

  void SocketAddress::Initialize(int address, int port)
  {
    sockaddr_in* p = new sockaddr_in;
    memset(p, 0, sizeof(sockaddr_in));
    opaque_ = p;
    p->sin_family = AF_INET;
    p->sin_port = htons(port);
    p->sin_addr.s_addr = address;
  }

  SmartPointer<SocketAddress> SocketAddress::ForAny(int port)
  {
    SmartPointer<SocketAddress> s = new SocketAddress(INADDR_ANY, port);
    return s;
  }

  SmartPointer<SocketAddress> SocketAddress::ForLoopback(int port)
  {
    SmartPointer<SocketAddress> s = new SocketAddress("127.0.0.1", port);
    return s;
  }

  SmartPointer<String> SocketAddress::ToString()
  {
    String* s = new String(inet_ntoa(((sockaddr_in*)opaque_)->sin_addr));
    SmartPointer<String> sp(s);
    return sp;
  }
} // namespace lepcpplib
