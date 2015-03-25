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

#include "TestJson.h"
#include "../src/JsonValue.h"
#include "../src/JsonObject.h"
#include "../src/JsonString.h"
#include "../src/JsonNumber.h"
#include "../src/JsonArray.h"
#include "../src/JsonBool.h"
#include "../src/JsonNull.h"
#include "../src/String.h"
#include "../src/SmartPointer.h"

using lep::JsonValue;
using lep::JsonObject;
using lep::JsonString;
using lep::JsonNumber;
using lep::JsonArray;
using lep::JsonBool;
using lep::JsonNull;
using lep::SmartPointer;
using lep::String;
using lep::TestCase;
using lep::TestModule;

class TestJsonObjects : public TestCase
{
  public:
    TestJsonObjects()
      : TestCase("TestJsonObjects: test json output generation.")
    {
    }

    bool test()
    {
      JsonObject j;
      j.Add(new JsonString("first_name"), new JsonString("john"));
      j.Add(new JsonString("last_name"), new JsonString("doe"));
      j.Add(new JsonString("age"), new JsonNumber(22));
      j.Add(new JsonString("full_time"), new JsonBool(true));
      j.Add(new JsonString("work_phone"), new JsonString("123-456-7890"));
      j.Add(new JsonString("mobile_phone"), new JsonNull());

      JsonArray* ja1 = new JsonArray();
      ja1->Add(new JsonString("orange"));
      ja1->Add(new JsonString("banana"));
      ja1->Add(new JsonString("apple"));

      SmartPointer<JsonValue> sp1(ja1);
      j.Add(new JsonString("fruits"), sp1);

      JsonObject* j2 = new JsonObject();
      JsonArray* ja2 = new JsonArray();

      ja2->Add(new JsonString("blue"));
      ja2->Add(new JsonString("red"));
      ja2->Add(new JsonString("orange"));

      SmartPointer<JsonValue> sp2(ja2);
      j2->Add(new JsonString("colors"), sp2);

      SmartPointer<JsonValue> sp3(j2);
      j.Add(new JsonString("shirts"), sp3);

      String result = "{\"first_name\":\"john\",\"last_name\":\"doe\","
        "\"age\":22,\"full_time\":true,\"work_phone\":\"123-456-7890\","
        "\"mobile_phone\":null,\"fruits\":[\"orange\",\"banana\",\"apple"
        "\"],\"shirts\":{\"colors\":[\"blue\",\"red\",\"orange\"]}}";
      return (result == *j.ToString());
    }
};

TestJson::TestJson()
  : TestModule("Json class tester")
{
  add(new TestJsonObjects());
}

