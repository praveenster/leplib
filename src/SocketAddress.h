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

#ifndef LEPCPPLIB_SOCKETADDRESS_H_
#define LEPCPPLIB_SOCKETADDRESS_H_

#include "String.h"
#include "SmartPointer.h"

namespace lepcpplib {
class SocketAddress {
  public:
    SocketAddress(const String& address, int port);
    SocketAddress(int address, int port);
    virtual ~SocketAddress();

    SmartPointer<String> ToString();
    static SmartPointer<SocketAddress> ForAny(int port);
    static SmartPointer<SocketAddress> ForLoopback(int port);
    static SmartPointer<SocketAddress> ForHostName(int port);

  private:
    void Initialize(int address, int port);
    SocketAddress(const SocketAddress& that);
    SocketAddress& operator=(const SocketAddress& that);

  private:
    void* opaque_;
};
} // namespace lepcpplib

#endif // LEPCPPLIB_SOCKETADDRESS_H_
