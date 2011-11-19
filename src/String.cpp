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
#include <sstream>
#include <iomanip>
#include "String.h"

using lepcpplib::String;
using std::memcpy;
using std::strcmp;
using std::strlen;

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

String::String(const char c)
  : mBuffer(0)
{
  *this = c;
}

String& String::operator=(const String& s)
{
  if (this != &s) {
    clone(s.mBuffer, s.length());
  }

  return *this;
}

String& String::operator=(const char* c)
{
  int l = 0;
  if (c != 0) {
    l = strlen(c);
  }

  clone(c, l);
  return *this;
}

String& String::operator=(const char c)
{
  char temp[2];
  temp[0] = c;
  temp[1] = '\0';

  clone(temp, sizeof(temp));
  return *this;
}

bool lepcpplib::operator==(const String& s1, const String& s2)
{
  bool result = false;

  if ((s1.length() == 0) && (s2.length() == 0)) {
    result = true;
  }
  else if ((s1.length() > 0) && (s2.length() > 0)) {
    result = (strcmp(s1.mBuffer, s2.mBuffer) == 0);
  }

  return result;
}

bool lepcpplib::operator!=(const String& s1, const String& s2)
{
  return !(operator==(s1, s2));
}

String::~String()
{
  delete[] mBuffer;
}

const char* String::toCharArray() const
{
  return mBuffer;
}

unsigned int String::length() const
{
  return (mBuffer == 0) ? 0 : strlen(mBuffer);
}

void String::clone(const char* c, unsigned int l)
{
  delete[] mBuffer;
  mBuffer = 0;

  if ((l > 0) && (c != NULL)) {
    mBuffer = new char[l + 1];
    memcpy(mBuffer, c, l);
    mBuffer[l] = 0;
  }
}

void String::append(const char* c, unsigned int l)
{
  if ((l > 0) && (c != NULL)) {
    int lold = length();
    int lnew = lold + l;
    char* temp = new char[lnew + 1];
    std::memcpy(temp, mBuffer, lold);
    std::memcpy(temp + lold, c, l);
    temp[lnew] = '\0';
    delete[] mBuffer;
    mBuffer = temp;
  }
}

String String::fromInt(int value)
{
  std::stringstream ss;
  ss << value;
  return String(ss.str().c_str());
}

String String::fromInt(int value, int width, char pad)
{
   std::stringstream ss;
   ss << std::setw(width) << std::setfill(pad) << value;
   return String(ss.str().c_str());
}

int String::toInt() const
{
  std::stringstream ss;
  ss << toCharArray();
  int value;
  ss >> value;
  return value;
}

int String::toInt(const char* c)
{
  std::stringstream ss;
  ss << c;
  int value;
  ss >> value;
  return value;
}

String lepcpplib::operator+(const String& s1, const String& s2)
{
  String s3;
  s3 += s1;
  s3 += s2;

  return s3;
}

String lepcpplib::operator+(const char* s1, const String& s2)
{
  String s3;
  s3 += s1;
  s3 += s2;

  return s3;
}

String lepcpplib::operator+(const String& s1, const char* s2)
{
  String s3;
  s3 += s1;
  s3 += s2;

  return s3;
}

String lepcpplib::operator+(const char c1, const String& s2)
{
  String s3;
  s3 += c1;
  s3 += s2;

  return s3;
}

String lepcpplib::operator+(const String& s1, const char c2)
{
  String s3;
  s3 += s1;
  s3 += c2;

  return s3;
}

String& String::operator+=(const String& s1)
{
  this->append(s1.mBuffer, s1.length());
  return *this;
}

String& String::operator+=(const char* s1)
{
  if (s1 != NULL) {
    int l = strlen(s1);
    if (l != 0) {
      this->append(s1, l);
    }
  }

  return *this;
}

String& String::operator+=(const char c1)
{
  char temp[2];
  temp[0] = c1;
  temp[2] = '\0';
  this->append(temp, sizeof(temp));

  return *this;
}
