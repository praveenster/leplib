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
#include <fstream>
#include "Logger.h"
#include "ConfigFile.h"

using std::ifstream;

namespace lepcpplib {
const int kConfigFileMaxLineLength = 256;

ConfigFile::ConfigFile(const String& filename)
  : filename_(filename)
{
}

ConfigFile::~ConfigFile()
{
}

bool ConfigFile::Load()
{
  bool result = false;

  if (filename_ != "") {
    ifstream file(filename_.toCharArray());
    char buffer[kConfigFileMaxLineLength];

    //LOG_D("Processing config file: %s\n", filename_.toCharArray());
    while ((!file.eof()) && (!file.fail())) {
      file.getline(buffer, sizeof(buffer));

      if (file.gcount()) {
        String line(buffer);
        int q = line.indexOf('=');

        if (q != -1)
        {
          KeyValue kv;
          kv.key = line.substring(0, q - 1);
          kv.value = line.substring(q + 1);
          keyvalues_.push_back(kv);
        }
      }
    }
  }

  result = true;
  //LOG_D("Done processing config file: %s\n", filename_.toCharArray());
  return result;
}

bool ConfigFile::ValueOf(const String& key, String& value)
{
  bool result = false;

  //TODO: use map instead of vector.
  for (int i = 0; i < keyvalues_.size(); i++) {
    //LOG_D("[%d] key = %s, value = %s\n", i,
    //      keyvalues_[i].key.toCharArray(),
    //      keyvalues_[i].value.toCharArray());
    if (keyvalues_[i].key == key) {
      value = keyvalues_[i].value;
      result = true;
      break;
    }
  }

  return result;
}
} // namespace lepcpplib
