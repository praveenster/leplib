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

#ifndef __STRING_H__
#define __STRING_H__

#include <vector>

namespace lepcpplib {
  class String
  {
    public:
      String();
      String(const String& s);
      String(const char* c);
      String(const char* c, int count);
      String(const char c);

      ~String();

      String& operator=(const String& s);
      String& operator=(const char* c);
      String& operator=(const char c);

      String& operator+=(const String& s1);
      String& operator+=(const char* s1);
      String& operator+=(const char c1);

      friend bool operator==(const String& s1, const String& s2);
      friend bool operator!=(const String& s1, const String& s2);

      friend String operator+(const String& s1, const String& s2);
      friend String operator+(const String& s1, const char* s2);
      friend String operator+(const char* s1, const String& s2);
      friend String operator+(const String& s1, const char c2);
      friend String operator+(const char c1, const String& s2);

      bool operator<(const String& s1) const;
      bool operator>(const String& s1) const;

      static String fromInt(int i);
      static String fromInt(int i, int width, char pad);

      int toInt() const;
      static int toInt(const char* c);

      const char* toCharArray() const;

      int compare(const String& s) const;
      int compare(const char* c) const;

      int indexOf(char c, unsigned int fromIndex = 0);
      char charAt(int index);

      String substring(unsigned int beginIndex);
      String substring(unsigned int beginIndex, unsigned int endIndex);

      String trim();

      void replace(unsigned int beginIndex, unsigned int count, const String& replacement);

      void tokenize(const char delimiter, std::vector<String>& tokens) const;
      static void tokenize(const char* input, const char delimiter, std::vector<String>& tokens);
      static void tokenize(const String& input, const char delimiter, std::vector<String>& tokens);

      unsigned int length() const;

    private:
      void clone(const char* c, unsigned int l);
      void append(const char* c, unsigned int l);

      char* buffer_;
  };

  bool operator==(const String& s1, const String& s2);
  bool operator!=(const String& s1, const String& s2);
  String operator+(const String& s1, const String& s2);
  String operator+(const String& s1, const char* s2);
  String operator+(const char* s1, const String& s2);
  String operator+(const String& s1, const char c2);
  String operator+(const char c1, const String& s2);
}

#endif // __STRING_H__
