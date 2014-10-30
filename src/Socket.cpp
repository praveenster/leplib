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
#include "Socket.h"

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
#include <pthread.h>
#include <errno.h>
#include <cstring>
#endif // WIN32

namespace lepcpplib {

// internal function to convert to struct format used by socket functions.
// not made as part of class to reduce pollution of native types.
static void SocketAddressObjectToStruct(SocketAddress& address, sockaddr_in& socket_address)
{
  memset(&socket_address, 0, sizeof(socket_address));
  socket_address.sin_family = AF_INET;
  socket_address.sin_addr.s_addr = inet_addr(address.address().toCharArray());
  socket_address.sin_port = htons(address.port());
}

static void SocketAddressStructToObject(sockaddr_in& socket_address, SocketAddress& address)
{
  address.set_address(inet_ntoa(socket_address.sin_addr));
  address.set_port(socket_address.sin_port);
}

Socket::Socket(AddressFamily address_family, Type type, Protocol protocol)
  : socket_(0)
{
#ifdef WIN32
  // win32 needs special initialization for using sockets.
  // documentation indicates that this can be called multiple times
  // (without any performance hit in calls after first one), as long
  // as the cleanup is called the same number of times during
  // the unwind process.
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2,2), &wsaData);
#endif

  int f = (address_family == kInternet) ? AF_INET : AF_INET;
  int t = (type == kStream) ? SOCK_STREAM : SOCK_DGRAM;
  int p = (protocol == kTcp) ? IPPROTO_TCP : IPPROTO_UDP;
  socket_ = socket(f, t, p);
}

Socket::~Socket()
{
  this->Close();

#ifdef WIN32
  // win32 needs special initialization for using sockets.
  WSACleanup();
#endif
}

void Socket::Close()
{
#ifdef WIN32
  closesocket(socket_);
#else
  close(socket_);
#endif
}

int Socket::Connect(SocketAddress& destination_address)
{
  sockaddr_in socket_address;
  SocketAddressObjectToStruct(destination_address, socket_address);
  return connect(socket_, (sockaddr*)&socket_address, sizeof(socket_address));
}

int Socket::Bind(SocketAddress& server_address)
{
  local_address_ = server_address;
  sockaddr_in socket_address;
  SocketAddressObjectToStruct(server_address, socket_address);
  return bind(socket_, (struct sockaddr*) &socket_address, sizeof(socket_address));
}

int Socket::Listen(int backlog)
{
  return listen(socket_, backlog);
}

SmartPointer<Socket> Socket::Accept(int backlog)
{
  sockaddr_in client_socket_address;
  int address_length = sizeof(client_socket_address);
  int client_socket = accept(socket_, (struct sockaddr *)&client_socket_address, (socklen_t*)&address_length);
  SmartPointer<Socket> rs = new Socket(kInternet, kStream, kTcp);
  SocketAddressStructToObject(client_socket_address, (*rs).remote_address_);
  (*rs).local_address_ = local_address_;
  return rs;
}

int Socket::Receive(char* buffer, int length, int flags)
{
  return recv(socket_, buffer, length, flags);
}

int Socket::Send(const char* buffer, int length, int flags)
{
  return send(socket_, buffer, length, flags);
}

int Socket::Send(const String& buffer, int flags)
{
  return send(socket_, buffer.toCharArray(), buffer.length(), flags);
}

int Socket::SetOptionReuse()
{
  int value = 1;
  return setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value));
}

int Socket::GetLastError()
{
#ifdef WIN32
  return WSAGetLastError();
#else
  return errno;
#endif //WIN32
}

const SocketAddress& Socket::local_address() const
{
  return local_address_;
}

const SocketAddress& Socket::remote_address() const
{
  return remote_address_;
}
} // namespace lepcpplib
