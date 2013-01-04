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


#include "StringBuilder.h"

#include <cstdlib>
#include <cstring>

namespace lepcpplib {
const int StringBuilder::kDefaultBufferSize = 1024;

StringBuilder::StringBuilder()
  : buffer_(0), buffer_size_(0), used_size_(0)
{
  Initialize(kDefaultBufferSize);
}

StringBuilder::StringBuilder(int buffer_size)
  : buffer_(0), buffer_size_(0), used_size_(0)
{
  Initialize(buffer_size);
}

StringBuilder::~StringBuilder()
{
  if (buffer_) {
    free(buffer_);
  }

  buffer_ = 0;
  buffer_size_ = 0;
  used_size_ = 0;
}

void StringBuilder::Initialize(int buffer_size)
{
  buffer_size_ = buffer_size;
  buffer_ = (char*)malloc(buffer_size_);

  // check if malloc returned null.
  if (buffer_ != NULL) {
    memset(buffer_, 0, buffer_size_);
  }
  else {
    buffer_size_ = 0;
  }
}

void StringBuilder::Resize(int buffer_size)
{
  char* buffer = (char*)realloc(buffer_, buffer_size);

  // assign only if realloc was successful.
  if (buffer != NULL) {
    buffer_ = buffer;
    buffer_size_ = buffer_size;
  }
}

void StringBuilder::Append(const char* s)
{
  if (s != NULL) {
    int size = strlen(s);
    if (buffer_size_ - used_size_ <= size) {
        int new_size = (size > buffer_size_) ? size : buffer_size_;
        new_size *= 2;
        Resize(new_size);
    }

    memcpy(buffer_ + used_size_, s, size);
    used_size_ += size;
  }
}

void StringBuilder::Append(int i)
{
  Append(String::fromInt(i).toCharArray());
}

void StringBuilder::Append(const String& s)
{
  Append(s.toCharArray());
}

SmartPointer<String> StringBuilder::ToString()
{
  SmartPointer<String> s = new String(buffer_, used_size_);
  return s;
}
} // namespace lepcpplib
