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
#include "TestSet.h"

using std::vector;

namespace lep {
TestSet::~TestSet()
{
  for (unsigned int i = 0; i < testModules.size(); i++) {
    delete testModules[i];
  }
}

void TestSet::run(unsigned int& passCount, unsigned int& failCount)
{
  LOG_D("Starting tests ...\n");
  for (unsigned int i = 0; i < testModules.size(); i++) {
    LOG_D("TestModule: %s started\n", testModules[i]->name().toCharArray());
    unsigned int p = 0;
    unsigned int f = 0;
    testModules[i]->run(p, f);
    LOG_D("TestModule: %s complete. Pass = %d, Fail = %d\n",
      testModules[i]->name().toCharArray(), p, f);
    passCount += p;
    failCount += f;
  }

  LOG_D("Tests complete. Total PassCount = %d, Total FailCount = %d\n",
    passCount, failCount);
}

void TestSet::add(TestModule* testModule)
{
  testModules.push_back(testModule);
}
} // namespace lep

