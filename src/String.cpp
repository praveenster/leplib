/*
   Copyright 2011 Neevarp Yhtroom

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
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

const String& String::operator=(const String& s)
{
  if (this != &s) {
    unsigned int l = s.length();
    delete[] mBuffer;
    mBuffer = 0;
    mBuffer = new char[l + 1];
    memcpy(mBuffer, s.mBuffer, l);
    mBuffer[l] = 0;
  }

  return *this;
}

const String& String::operator=(const char* c)
{
  unsigned int l = strlen(c);
  delete[] mBuffer;
  mBuffer = 0;
  mBuffer = new char[l + 1];
  memcpy(mBuffer, c, l);
  mBuffer[l] = 0;

  return *this;
}

bool lepcpplib::operator==(const String& s1, const String& s2)
{
  return (strcmp(s1.mBuffer, s2.mBuffer) == 0);
}

String::~String()
{
  delete mBuffer;
}

char* String::toCharArray()
{
  return mBuffer;
}

unsigned int String::length() const
{
  return (mBuffer == 0) ? 0 : strlen(mBuffer);
}

void String::clone(const char* c, unsigned int l)
{
}
