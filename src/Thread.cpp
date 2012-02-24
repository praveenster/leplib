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

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "Logger.h"
#include "Thread.h"

namespace lepcpplib {
struct ThreadParameters
{
  Thread* this_;
  void* parameter_;
};

void* Thread::runner(void* parameter)
{
  if (parameter != NULL) {
    ThreadParameters* temp = (ThreadParameters*)parameter;

    if (temp->this_ != NULL) {
      temp->this_->Run(temp->parameter_);
    }

    delete temp;
  }
}

void Thread::Start(void* parameter)
{
  ThreadParameters* temp = new ThreadParameters;
  temp->this_ = this;
  temp->parameter_ = parameter;

#ifdef WIN32
  DWORD threadId;
  HANDLE hThread = CreateThread(
    NULL,                                 // default security attributes
    0,                                    // use default stack size
    (LPTHREAD_START_ROUTINE)startAddress, // thread function
    parameter,                            // argument to thread function
    0,                                    // use default creation flags
    &threadId);                           // returns the thread identifier
#else
  pthread_t thread;
  int result;
  result = pthread_create(&thread, NULL, &Thread::runner, (void*)temp);
  if (result != 0)
  {
    LOG_D("Thread creation error = %d\n", result);
  }

  pthread_detach(thread);

  if (result != 0)
  {
    LOG_D("Thread detach error = %d\n", result);
  }
#endif
}

Thread::Thread()
{
}

Thread::~Thread()
{
}

} // namespace lepcpplib
