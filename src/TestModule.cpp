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
#include "TestModule.h"

using std::string;
using std::vector;
using lepcpplib::TestCase;
using lepcpplib::TestModule;

TestModule::TestModule(string name)
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
    DEBUG_D("TestCase: %s started\n", tests[i]->getName().c_str());
    unsigned int p = 0;
    unsigned int f = 0;
    string result;
    if (tests[i]->test()) {
      passCount++;
      result = "PASS";
    }
    else {
      failCount++;
      result = "FAIL";
    }

    DEBUG_D("TestCase: %s complete. Result = %s\n", 
      tests[i]->getName().c_str(), result.c_str());
  }
}

void TestModule::add(TestCase* testCase)
{
  tests.push_back(testCase);
}

string TestModule::getName()
{
  return mName;
}
