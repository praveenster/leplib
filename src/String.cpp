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

#include <cstring>
#include "String.h"

using lepcpplib::String;
using namespace std;

String::String()
  : mBuffer(0)
{
}

String::String(const String& s)
  : mBuffer(0)
{
  *this = s;
}

String::String(const char* c)
  : mBuffer(0)
{
  *this = c;
}

String& String::operator=(const String& s)
{
  if (this != &s) {
    clone(s.mBuffer, strlen(s.mBuffer));
  }

  return *this;
}

String& String::operator=(const char* c)
{
  clone(c, strlen(c));
  return *this;
}

bool lepcpplib::operator==(const String& s1, const String& s2)
{
  return (strcmp(s1.mBuffer, s2.mBuffer) == 0);
}

String::~String()
{
  delete[] mBuffer;
}

char* String::toCharArray()
{
  return mBuffer;
}

unsigned int String::length()
{
  return (mBuffer == 0) ? 0 : strlen(mBuffer);
}

void String::clone(const char* c, unsigned int l)
{
  delete[] mBuffer;
  mBuffer = 0;
  mBuffer = new char[l + 1];
  memcpy(mBuffer, c, l);
  mBuffer[l] = 0;
}
