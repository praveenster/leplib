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

#include "../src/TestSet.h"
#include "TestConfigFile.h"
#include "TestCsvFile.h"
#include "TestHttpClient.h"
#include "TestJson.h"
#include "TestSmartPointer.h"
#include "TestSocket.h"
#include "TestSocketAddress.h"
#include "TestString.h"
#include "TestStringBuilder.h"
#include "TestThread.h"

using lep::TestSet;

class TestMain : public TestSet
{
  public:
    TestMain()
    {
      add(new TestConfigFile());
      add(new TestCsvFile());
      add(new TestHttpClient());
      add(new TestJson());
      add(new TestSmartPointer());
      add(new TestSocket());
      add(new TestSocketAddress());
      add(new TestString());
      add(new TestStringBuilder());
      add(new TestThread());
    };
};

int main(int argc, char** argv)
{
#ifdef WIN32
  // enable debug heap allocations and perform automatic leak
  // checking 
  _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

  TestMain* pTest = new TestMain();
  unsigned int passCount = 0;
  unsigned int failCount = 0;
  pTest->run(passCount, failCount);
  delete pTest;
}

