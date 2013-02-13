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

#ifndef LEPCPPLIB_SOCKET_H_
#define LEPCPPLIB_SOCKET_H_

#include "SocketAddress.h"

namespace lepcpplib {
class Socket {
  public:
    enum AddressFamily {
      kInternet
    };

    enum Type {
      kStream,
      kDatagram
    };

    enum Protocol {
      kTcp,
      kUdp
    };

    enum Direction {
      kBoth,
      kReceive,
      kSend
    };

    enum Flags {
      kPeek,
      kOutOfBand,
      kWaitAll
    };

    Socket(AddressFamily address_family, Type type, Protocol protocol);
    ~Socket();

    void Close();
    int Connect(SocketAddress& destination_address);
    int Bind(SocketAddress& server_address);
    int Listen(int backlog);
    SmartPointer<Socket> Accept(int backlog);
    int Receive(char* buffer, int length, int flags);
    int Send(const char* buffer, int length, int flags);

    int SetOptionReuse();
    int GetLastError();

    const SocketAddress& local_address();
    const SocketAddress& remote_address();

    void SendTo();
    void Shutdown();
    void Receive();
    void ReceiveFrom();
    //static void Select(vector<SmartPointer<Socket>>& check_read, 
    //  vector<SmartPointer<Socket>>& check_write, 
    //  vector<SmartPointer<Socket>>& check_error,
    //  int timeout);

  private:
    int socket_;
    SocketAddress local_address_;
    SocketAddress remote_address_;
};
} // namespace lepcpplib

#endif // LEPCPPLIB_SOCKET_H_
