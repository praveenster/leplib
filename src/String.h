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
#ifndef __STRING_H__
#define __STRING_H__

namespace lepcpplib {
  class String
  {
    public:
      String();
      String(const String& s);
      String(const char* c);

      ~String();

      const String& operator=(const String& s);
      const String& operator=(const char* c);
      friend bool operator==(const String& s1, const String& s2);

      static String valueOf(int i);
      static String valueOf(int i, int width, char pad);

      int extractInt();

      char* toCharArray();

      int compare(const String& s);
      int compare(const char* c);

      unsigned int length() const;

    private:
      void clone(const char* c, unsigned int l);
      char* mBuffer;
  };
}

#endif // __STRING_H__
