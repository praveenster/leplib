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
#ifndef __TESTMODULE_H__
#define __TESTMODULE_H__

#include <string>
#include <vector>
#include "TestCase.h"

namespace lepcpplib {
  class TestModule
  {
    public:
      virtual ~TestModule();
      virtual void run(unsigned int& passCount, unsigned int& failCount);
      void add(TestCase* testCase);
      std::string getName();

    protected:
      TestModule(std::string name);

    private:
      std::string mName;
      std::vector<TestCase*> tests;
  };
}

#endif // __TESTCASE_H__
