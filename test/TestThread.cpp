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
#include "TestThread.h"
#include "../src/Thread.h"
#include "../src/Logger.h"

using lepcpplib::Thread;
using lepcpplib::TestCase;
using lepcpplib::TestModule;

class Thread1 : public Thread
{
  public:
    void* Run(void* parameter)
    {
      int i = (long)parameter;
      LOG_D("Parameter = %d\n", i);

      return 0;
    }
};

class TestThreadRun : public TestCase
{
  public:
    TestThreadRun()
      : TestCase("TestThreadRun")
    {
    }

    bool test()
    {
      Thread1 t1;
      t1.Start((void*)1);

      Thread1 t2;
      t2.Start((void*)2);

      t1.Join();
      t2.Join();
      return true;
    }
};

TestThread::TestThread()
  : TestModule("Thread class tester")
{
  add(new TestThreadRun());
}
