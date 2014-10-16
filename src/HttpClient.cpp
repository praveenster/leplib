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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HttpClient.h"
#include "Socket.h"
#include "String.h"

using std::vector;

namespace lepcpplib {
const int RESPONSE_BUFFER_SIZE = 1024;
const int DEFAULT_HTTP_PORT = 80;
const String CRLF = "\r\n";
const String CONTENT_LENGTH = "Content-Length: ";

HttpClient::HttpClient()
  : headers_(), content_length_(0), residue_(), header_parsed_(false)
{
}

bool HttpClient::ParseResponse(char* buffer, int length)
{
  bool all_done = false;

  if (length <= 0) {
    return all_done;
  }

  residue_.Append(buffer, length);

  if (!header_parsed_) {
    while (true) {
      int p = residue_.IndexOf(CRLF);

      if (p == -1) {
        // if no CRLF, then this is a partial line.
        // leave it in the residue. it will get parsed
        // when there is more data.
        break;
      }
      else if (p == 0) {
        // if the CRLF is at the beginning, then it is the end of all headers.
        header_parsed_ = true;

        // remove the CRLF from the residue.
        residue_.Remove(0, CRLF.length()); // remove the CRLF from the residue.
        break;
      }
      else {
        // if there is a CRLF somewhere in the middle, parse upto the CRLF as a header
        // and search for more.
        SmartPointer<String> header = residue_.Substring(0, p);
        residue_.Remove(0, p + CRLF.length());

        // check if this header is Content-Length:
        int q = (*header).indexOf(CONTENT_LENGTH);
        if (q == 0) {
          content_length_ = (*header).substring(CONTENT_LENGTH.length()).toInt();
        }

        headers_.push_back(header);
      }
    }
  }

  // if the headers have been parsed, then the residue is part of
  // the content.
  if (header_parsed_) {
    all_done = (residue_.Length() == content_length_);
  }

  return all_done;
}

void HttpClient::Clear()
{
  headers_.clear();
  content_length_ = 0;
  residue_.Clear();
  header_parsed_ = false;
}

bool HttpClient::Execute(String address, String command)
{
  int result;
  bool parsing_done = false;

  Socket http_socket(Socket::kInternet, Socket::kStream, Socket::kTcp);
  SocketAddress server_address(address, DEFAULT_HTTP_PORT);

  // reset previous state.
  this->Clear();

  char response_buffer[RESPONSE_BUFFER_SIZE];
  memset(response_buffer, 0, RESPONSE_BUFFER_SIZE);

  result = http_socket.Connect(server_address);

  if (result == 0) {
    StringBuilder message;
    message.Append(command);
    message.Append(" HTTP/1.1");
    message.Append(CRLF);
    message.Append("Accept: */*");
    message.Append(CRLF);
    message.Append("Accept-Language: en-us");
    message.Append(CRLF);
    message.Append("Accept-Encoding: ");
    message.Append(CRLF);
    message.Append("User-Agent: leplib HttpClient/1.0");
    message.Append(CRLF);
    message.Append("Host: ");
    message.Append(CRLF);
    message.Append("Connection: close");
    message.Append(CRLF);
    message.Append(CRLF);

    http_socket.Send(*message.ToString(), 0);

    while(!parsing_done) {
      result = http_socket.Receive(response_buffer, sizeof(response_buffer), 0);

      // some http servers don't seem to send content-length.
      // if no more bytes are received, then parse whatever was received.
      if (!header_parsed_) {
        header_parsed_ = (result == 0);
      }

      parsing_done = (ParseResponse(response_buffer, result)) || (result == 0);
    }

    http_socket.Close();
  }

  return parsing_done;
}

vector<SmartPointer<String> > HttpClient::headers()
{
  return headers_;
}

SmartPointer<String> HttpClient::content()
{
  return residue_.ToString();
}

} // namespace lepcpplib
