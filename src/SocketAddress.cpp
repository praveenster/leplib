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
#include "StringBuilder.h"

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

namespace lep {
SocketAddress::SocketAddress()
  : address_(""), port_(0)
{
}

SocketAddress::SocketAddress(const char* address, int port)
  : address_(address), port_(port)
{
}

SocketAddress::SocketAddress(const String& address, int port)
  : address_(address), port_(port)
{
}

SocketAddress::SocketAddress(int address, int port)
  : address_(""), port_(port)
{
  in_addr a;
#ifdef WIN32
  a.S_un.S_addr = address;
#else
  a.s_addr = address;
#endif
  inet_ntoa(a);
}

SocketAddress::SocketAddress(const SocketAddress& that)
  : address_(""), port_()
{
  *this = that;
}

SocketAddress::~SocketAddress()
{
}

SocketAddress& SocketAddress::operator=(const SocketAddress& that)
{
  if (this != &that) {
    address_ = that.address_;
    port_ = that.port_;
  }

  return *this;
}

SmartPointer<SocketAddress> SocketAddress::ForAny(int port)
{
  SmartPointer<SocketAddress> s = new SocketAddress(0, port);
  return s;
}

SmartPointer<SocketAddress> SocketAddress::ForLoopback(int port)
{
  SmartPointer<SocketAddress> s = new SocketAddress("127.0.0.1", port);
  return s;
}

SmartPointer<String> SocketAddress::ToString()
{
  StringBuilder sb;
  sb.Append(address_);
  sb.Append(":");
  sb.Append(port_);
  return sb.ToString();
}

const String& SocketAddress::address() const
{
  return address_;
}

const int SocketAddress::port() const
{
  return port_;
}

void SocketAddress::set_address(const char* address)
{
  address_ = address;
}

void SocketAddress::set_port(int port)
{
  port_ = port;
}
} // namespace lep

