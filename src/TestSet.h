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
#ifndef __TESTSET_H__
#define __TESTSET_H__

#include <vector>
#include "TestModule.h"

namespace lepcpplib {
  class TestSet
  {
    public:
      virtual ~TestSet();
      virtual void run(unsigned int& passCount, unsigned int& failCount);
      void add(TestModule* testModule);

    protected:

    private:
      std::vector<TestModule*> testModules;
  };
}

#endif // __TESTSET_H__
