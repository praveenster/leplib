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
  // prevent accidental leak!
  if (buffer_ != NULL) {
    free(buffer_);
    buffer_ = NULL;
    buffer_size_ = 0;
  }

  buffer_size_ = buffer_size;
  buffer_ = (char*)malloc(buffer_size_);

  // check if malloc returned null.
  if (buffer_ != NULL) {
    memset(buffer_, 0, buffer_size_);
  }
  else {
    buffer_size_ = 0;
  }

  used_size_ = 0;
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
    Append(s, strlen(s));
  }
}

void StringBuilder::Append(const char* s, int length)
{
  if ((s != NULL) && (length > 0)) {
    if (buffer_size_ - used_size_ <= length) {
        int new_size = (length > buffer_size_) ? length : buffer_size_;
        new_size *= 2;
        Resize(new_size);
    }

    memcpy(buffer_ + used_size_, s, length);
    used_size_ += length;
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

int StringBuilder::IndexOf(const String& s)
{
  int result = -1;
  int rhs_size = s.length();
  if ((used_size_ > 0) && (rhs_size > 0)) {
    int i = 0;
    int j = 0;

    // i = pointer to stringbuilder chars, 
    // j = pointer to string chars.
    // make sure both i and j don't go beyond bounds
    // and if the number of chars to compare in strinbuilder
    // is less than the length of the string, there is no
    // need to keep checking.
    bool match = false;
    while ((i < used_size_) && (j < rhs_size) && ((used_size_ - i) >= (rhs_size - j))) {
      if (buffer_[i] == s.charAt(j)) {
        match = true;
        j++;
      }
      else {
        match = false;
        j = 0;
      }

      i++;
    }

    // check if there was a match and also that
    // all the characters in the string were checked.
    if ((match) && (j >= rhs_size)) {
      result = i - rhs_size;
    }
  }

  return result;
}

SmartPointer<String> StringBuilder::Substring(int start)
{
  return Substring(start, used_size_);
}

SmartPointer<String> StringBuilder::Substring(int start, int end)
{
  SmartPointer<String> result;
  if ((start >= 0) && (end >= 0) && 
      (used_size_ > 0) && 
      (start < used_size_) && (end <= used_size_) && 
      (start < end)) {
    result = new String(buffer_ + start, end - start);
  }

  return result;
}

void StringBuilder::Remove(int start, int end)
{
  if ((start >= 0) && (end >= 0) && 
      (used_size_ > 0) && 
      (start < used_size_) && (end <= used_size_) && 
      (start < end)) {

    // special case: if the end is the end of the stringbuilder then
    // there is no need to copy into a new buffer. just reduce the
    // used size.
    if (end == Length()) {
      used_size_ = start;
    }
    else {
      // first keep the current buffer aside and create a new internal buffer.
      // then copy over the parts that need to be retained.
      char* temp = buffer_;
      int temp_size = buffer_size_;
      int temp_used_size = used_size_;

      buffer_ = NULL;
      buffer_size_ = 0;
      Initialize(temp_size);

      // if the cut point is in the beginning, nothing from the beginning needs
      // to be copied. if it is beyond the first character, then the characters
      // from the beginning upto the cut point need to be copied over.
      if (start != 0) {
        memcpy(buffer_, temp, start);
      }

      // now copy over the characters past the cut point.
      memcpy(buffer_ + start, temp + end, temp_used_size - end);

      // update the new used size to be the old size minus the count of bytes removed.
      used_size_ = temp_used_size - (end - start);
      free(temp);
    }
  }
}

void StringBuilder::Clear()
{
  used_size_ = 0;
}

int StringBuilder::Length()
{
  return used_size_;
}

SmartPointer<String> StringBuilder::ToString()
{
  SmartPointer<String> s = new String(buffer_, used_size_);
  return s;
}
} // namespace lepcpplib
