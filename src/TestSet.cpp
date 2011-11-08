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

#include "Debug.h"
#include "TestSet.h"

using std::string;
using std::vector;
using lepcpplib::TestSet;
using lepcpplib::TestModule;

TestSet::~TestSet()
{
  for (unsigned int i = 0; i < testModules.size(); i++) {
    delete testModules[i];
  }
}

void TestSet::run(unsigned int& passCount, unsigned int& failCount)
{
  DEBUG_D("Starting tests ...\n");
  for (unsigned int i = 0; i < testModules.size(); i++) {
    DEBUG_D("TestModule: %s started\n", testModules[i]->getName().c_str());
    unsigned int p = 0;
    unsigned int f = 0;
    testModules[i]->run(p, f);
    DEBUG_D("TestModule: %s complete. Pass = %d, Fail = %d\n", 
      testModules[i]->getName().c_str(), p, f);
    passCount += p;
    failCount += f;
  }

  DEBUG_D("Tests complete. Total PassCount = %d, Total FailCount = %d\n", 
    passCount, failCount);
}

void TestSet::add(TestModule* testModule)
{
  testModules.push_back(testModule);
}
