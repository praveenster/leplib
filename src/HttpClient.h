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
#ifndef LEPCPPLIB_HTTPCLIENT_H_
#define LEPCPPLIB_HTTPCLIENT_H_

#include <vector>
#include "String.h"
#include "StringBuilder.h"
#include "SmartPointer.h"

namespace lepcpplib {
class HttpClient {
  public:
    class DownloadProgressObserver {
      virtual void OnHeaderParsed() = 0;
      virtual void OnContentDownloaded() = 0;
      virtual void OnContentSegmentDownloaded() = 0;
    };

    HttpClient();
    void AddDownloadProgressObserver(DownloadProgressObserver* observer);
    bool Execute(String address, String command);
    bool Get(String url);
    std::vector< SmartPointer<String> > headers();
    SmartPointer<String> content();

private:
    bool ParseResponse(char* buffer, int length);
    void Clear();

  private:
    std::vector< SmartPointer<String> > headers_;
    int content_length_;
    StringBuilder residue_;
    bool header_parsed_;
    int port_;
    int response_buffer_size_;
    char* response_buffer_;
};
} // namespace lepcpplib

#endif // LEPCPPLIB_HTTPCLIENT_H_
