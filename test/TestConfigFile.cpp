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
#include "TestConfigFile.h"
#include "../src/ConfigFile.h"
#include "../src/String.h"

using std::ofstream;
using std::endl;
using lepcpplib::ConfigFile;
using lepcpplib::String;
using lepcpplib::TestCase;
using lepcpplib::TestModule;

class TestConfigFileKeyRetrieve1 : public TestCase
{
  public:
    TestConfigFileKeyRetrieve1()
      : TestCase("TestConfigFileKeyRetrieve1: with key present")
    {
    }

    bool test()
    {
      String filename("test.cfg");
      String key1("DEFAULT_TIMEOUT");
      String key2("DEFAULT_COLOR");
      String value1("100");
      String value2("RED");
      String separator("=");
      String value1read;
      String value2read;

      ofstream file(filename.toCharArray());
      file << key1.toCharArray()
           << separator.toCharArray()
           << value1.toCharArray() << endl;

      file << key2.toCharArray()
           << separator.toCharArray()
           << value2.toCharArray() << endl;

      file.close();

      ConfigFile configfile(filename);
      bool loaded = configfile.Load();
      bool found1 = configfile.ValueOf(key1, value1read);
      bool found2 = configfile.ValueOf(key2, value2read);

      return ((loaded) && (found1) && (found2) &&
              (value1read == value1) &&
              (value2read == value2));
    }
};

TestConfigFile::TestConfigFile()
  : TestModule("ConfigFile class tester")
{
  add(new TestConfigFileKeyRetrieve1());
}
