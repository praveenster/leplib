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

#include "Logger.h"
#include "TestModule.h"

using std::vector;
using lepcpplib::TestCase;
using lepcpplib::TestModule;
using lepcpplib::String;

TestModule::TestModule(String name)
  :mName(name)
{
}

TestModule::~TestModule()
{
  for (unsigned int i = 0; i < tests.size(); i++) {
    delete tests[i];
  }
}

void TestModule::run(unsigned int& passCount, unsigned int& failCount)
{
  for (unsigned int i = 0; i < tests.size(); i++) {
    LOG_D("TestCase: %s started\n", tests[i]->name().toCharArray());
    unsigned int p = 0;
    unsigned int f = 0;
    String result;
    if (tests[i]->test()) {
      passCount++;
      result = "PASS";
    }
    else {
      failCount++;
      result = "FAIL";
    }

    LOG_D("TestCase: %s complete. Result = %s\n",
      tests[i]->name().toCharArray(), result.toCharArray());
  }
}

void TestModule::add(TestCase* testCase)
{
  tests.push_back(testCase);
}

const String& TestModule::name()
{
  return mName;
}
