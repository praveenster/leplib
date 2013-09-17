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

#ifndef LEPCPPLIB_STRINGBUILDER_H_
#define LEPCPPLIB_STRINGBUILDER_H_

#include "SmartPointer.h"
#include "String.h"

namespace lepcpplib {
class StringBuilder {
  public:
    StringBuilder();
    StringBuilder(int buffer_size);
    virtual ~StringBuilder();
    SmartPointer<String> ToString();
    void Append(const char* s);
    void Append(const char* s, int length);
    void Append(int i);
    void Append(const String& s);

    int IndexOf(char c);
    int IndexOf(char c, int from_index);
    int IndexOf(const String& s);
    int IndexOf(const String& s, int from_index);

    SmartPointer<String> Substring(int start);
    SmartPointer<String> Substring(int start, int end);

    void Remove(int start, int end);

    void Clear();
    int Length();

  private:
    void Initialize(int buffer_size);
    void Resize(int buffer_size);
    StringBuilder(const StringBuilder& that);
    StringBuilder& operator=(const StringBuilder& that);

  public:
    static const int kDefaultBufferSize;

  private:
    char* buffer_;
    int buffer_size_;
    int used_size_;
};
} // namespace lepcpplib

#endif // LEPCPPLIB_STRINGBUILDER_H_
