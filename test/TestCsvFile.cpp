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
#include <vector>
#include "TestCsvFile.h"
#include "../src/CsvFile.h"
#include "../src/String.h"

using std::ofstream;
using std::ifstream;
using std::endl;
using std::vector;
using lepcpplib::CsvFile;
using lepcpplib::String;
using lepcpplib::TestCase;
using lepcpplib::TestModule;

class TestCsvFile1 : public TestCase
{
  public:
    TestCsvFile1()
      : TestCase("TestCsvFile1: verify load, row count and column count.")
    {
    }

    bool test()
    {
      String filename("test.csv");
      String r0c0("100");
      String r0c1("200");
      String r0c2("300");
      String r1c0("400");
      String r1c1("500");
      String r1c2("600");
      String separator(",");
      String value1read;
      String value2read;

      ofstream file(filename.toCharArray());
      file << r0c0.toCharArray()
           << separator.toCharArray()
           << r0c1.toCharArray()
           << separator.toCharArray()
           << r0c2.toCharArray()
           << endl;

      file << r1c0.toCharArray()
           << separator.toCharArray()
           << r1c1.toCharArray()
           << separator.toCharArray()
           << r1c2.toCharArray()
           << endl;

      file.close();

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();
      
      bool found = (csvfile.ValueOf(0, 0) == r0c0) && (csvfile.ValueOf(0, 1) == r0c1) && 
        (csvfile.ValueOf(0, 2) == r0c2) && 
        (csvfile.ValueOf(1, 0) == r1c0) && (csvfile.ValueOf(1, 1) == r1c1) &&
        (csvfile.ValueOf(1, 2) == r1c2);

      return ((loaded) && (found) && (csvfile.RowCount() == 2) &&
        (csvfile.ColumnCount() == 3));
    }
};

class TestCsvFile2 : public TestCase
{
  public:
    TestCsvFile2()
      : TestCase("TestCsvFile2: verify insert record at end")
    {
    }

    bool test()
    {
      String filename("test.csv");
      String r0c0("100");
      String r0c1("200");
      String r0c2("300");
      String r1c0("400");
      String r1c1("500");
      String r1c2("600");
      String r2c0("700");
      String r2c1("701");
      String r2c2("702");
      String separator(",");
      String value1read;
      String value2read;

      ofstream file(filename.toCharArray());
      file << r0c0.toCharArray()
           << separator.toCharArray()
           << r0c1.toCharArray()
           << separator.toCharArray()
           << r0c2.toCharArray()
           << endl;

      file << r1c0.toCharArray()
           << separator.toCharArray()
           << r1c1.toCharArray()
           << separator.toCharArray()
           << r1c2.toCharArray()
           << endl;

      file.close();

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();
      vector<String> row;
      row.push_back(r2c0);
      row.push_back(r2c1);
      row.push_back(r2c2);

      csvfile.Insert(row, 2);

      bool found = (csvfile.ValueOf(2, 0) == r2c0) && (csvfile.ValueOf(2, 1) == r2c1) && 
        (csvfile.ValueOf(2, 2) == r2c2);

      return ((loaded) && (found) && (csvfile.RowCount() == 3) &&
        (csvfile.ColumnCount() == 3));
    }
};

class TestCsvFile3 : public TestCase
{
  public:
    TestCsvFile3()
      : TestCase("TestCsvFile3: verify insert record past end")
    {
    }

    bool test()
    {
      String filename("test.csv");
      String r0c0("100");
      String r0c1("200");
      String r0c2("300");
      String r1c0("400");
      String r1c1("500");
      String r1c2("600");
      String r5c0("800");
      String r5c1("901");
      String r5c2("302");
      String separator(",");
      String value1read;
      String value2read;

      ofstream file(filename.toCharArray());
      file << r0c0.toCharArray()
           << separator.toCharArray()
           << r0c1.toCharArray()
           << separator.toCharArray()
           << r0c2.toCharArray()
           << endl;

      file << r1c0.toCharArray()
           << separator.toCharArray()
           << r1c1.toCharArray()
           << separator.toCharArray()
           << r1c2.toCharArray()
           << endl;

      file.close();

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();
      vector<String> row;
      row.push_back(r5c0);
      row.push_back(r5c1);
      row.push_back(r5c2);

      csvfile.Insert(row, 5);

      bool found = (csvfile.ValueOf(5, 0) == r5c0) && (csvfile.ValueOf(5, 1) == r5c1) && 
        (csvfile.ValueOf(5, 2) == r5c2);

      return ((loaded) && (found) && (csvfile.RowCount() == 6) &&
        (csvfile.ColumnCount() == 3));
    }
};

class TestCsvFile4 : public TestCase
{
  public:
    TestCsvFile4()
      : TestCase("TestCsvFile4: verify remove valid record")
    {
    }

    bool test()
    {
      String filename("test.csv");
      String r0c0("100");
      String r0c1("200");
      String r0c2("300");
      String r1c0("400");
      String r1c1("500");
      String r1c2("600");
      String separator(",");
      String value1read;
      String value2read;

      ofstream file(filename.toCharArray());
      file << r0c0.toCharArray()
           << separator.toCharArray()
           << r0c1.toCharArray()
           << separator.toCharArray()
           << r0c2.toCharArray()
           << endl;

      file << r1c0.toCharArray()
           << separator.toCharArray()
           << r1c1.toCharArray()
           << separator.toCharArray()
           << r1c2.toCharArray()
           << endl;

      file.close();

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();

      csvfile.Remove(0);

      bool found = (csvfile.ValueOf(0, 0) == r1c0) && (csvfile.ValueOf(0, 1) == r1c1) && 
        (csvfile.ValueOf(0, 2) == r1c2);

      return ((loaded) && (found) && (csvfile.RowCount() == 1) &&
        (csvfile.ColumnCount() == 3));
    }
};

class TestCsvFile5 : public TestCase
{
  public:
    TestCsvFile5()
      : TestCase("TestCsvFile5: verify remove invalid record")
    {
    }

    bool test()
    {
      String filename("test.csv");
      String r0c0("100");
      String r0c1("200");
      String r0c2("300");
      String r1c0("400");
      String r1c1("500");
      String r1c2("600");
      String separator(",");
      String value1read;
      String value2read;

      ofstream file(filename.toCharArray());
      file << r0c0.toCharArray()
           << separator.toCharArray()
           << r0c1.toCharArray()
           << separator.toCharArray()
           << r0c2.toCharArray()
           << endl;

      file << r1c0.toCharArray()
           << separator.toCharArray()
           << r1c1.toCharArray()
           << separator.toCharArray()
           << r1c2.toCharArray()
           << endl;

      file.close();

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();

      csvfile.Remove(5);

      bool found = (csvfile.ValueOf(0, 0) == r0c0) && (csvfile.ValueOf(0, 1) == r0c1) && 
        (csvfile.ValueOf(0, 2) == r0c2);

      return ((loaded) && (found) && (csvfile.RowCount() == 2) &&
        (csvfile.ColumnCount() == 3));
    }
};

class TestCsvFile6 : public TestCase
{
  public:
    TestCsvFile6()
      : TestCase("TestCsvFile6: verify append record")
    {
    }

    bool test()
    {
      String filename("test.csv");
      String r0c0("100");
      String r0c1("200");
      String r0c2("300");
      String r1c0("400");
      String r1c1("500");
      String r1c2("600");
      String r2c0("700");
      String r2c1("701");
      String r2c2("702");
      String separator(",");
      String value1read;
      String value2read;

      ofstream file(filename.toCharArray());
      file << r0c0.toCharArray()
           << separator.toCharArray()
           << r0c1.toCharArray()
           << separator.toCharArray()
           << r0c2.toCharArray()
           << endl;

      file << r1c0.toCharArray()
           << separator.toCharArray()
           << r1c1.toCharArray()
           << separator.toCharArray()
           << r1c2.toCharArray()
           << endl;

      file.close();

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();
      vector<String> row;
      row.push_back(r2c0);
      row.push_back(r2c1);
      row.push_back(r2c2);

      csvfile.Append(row);

      bool found = (csvfile.ValueOf(2, 0) == r2c0) && (csvfile.ValueOf(2, 1) == r2c1) && 
        (csvfile.ValueOf(2, 2) == r2c2);

      return ((loaded) && (found) && (csvfile.RowCount() == 3) &&
        (csvfile.ColumnCount() == 3));
    }
};

class TestCsvFile7 : public TestCase
{
  public:
    TestCsvFile7()
      : TestCase("TestCsvFile7: verify save record")
    {
    }

    bool test()
    {
      String filename("test.csv");
      String r0c0("100");
      String r0c1("200");
      String r0c2("300");
      String r1c0("400");
      String r1c1("500");
      String r1c2("600");
      String r5c0("800");
      String r5c1("901");
      String r5c2("302");
      String separator(",");
      String value1read;
      String value2read;

      ofstream file(filename.toCharArray());
      file << r0c0.toCharArray()
           << separator.toCharArray()
           << r0c1.toCharArray()
           << separator.toCharArray()
           << r0c2.toCharArray()
           << endl;

      file << r1c0.toCharArray()
           << separator.toCharArray()
           << r1c1.toCharArray()
           << separator.toCharArray()
           << r1c2.toCharArray()
           << endl;

      file.close();

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();
      vector<String> row;
      row.push_back(r5c0);
      row.push_back(r5c1);
      row.push_back(r5c2);

      csvfile.Insert(row, 5);
      csvfile.Save();

      String s = r0c0 + separator + " " + r0c1 + separator + " " + r0c2 + "\n" +
                 r1c0 + separator + " " + r1c1 + separator + " " + r1c2 + "\n" +
                 ",," + "\n" +
                 ",," + "\n" +
                 ",," + "\n" +
                 r5c0 + separator + " " + r5c1 + separator + " " + r5c2 + "\n" +
                 "\n";

      ifstream file2("test.csv");
      char buffer2[1024];
      file2.read(buffer2, sizeof(buffer2));
      int count = file2.gcount();

      bool valid = (memcmp(buffer2, s.toCharArray(), count) == 0);

      return ((loaded) && (valid));
    }
};

class TestCsvFile8 : public TestCase
{
  public:
    TestCsvFile8()
      : TestCase("TestCsvFile8: empty csv file load")
    {
    }

    bool test()
    {
      String filename("test.csv");

      ofstream file(filename.toCharArray());
      file.close();

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();

      return ((loaded) && (csvfile.RowCount() == 0) && (csvfile.ColumnCount() == 0));
    }
};

class TestCsvFile9 : public TestCase
{
  public:
    TestCsvFile9()
      : TestCase("TestCsvFile9: invalid csv file load")
    {
    }

    bool test()
    {
      String filename("test1.csv");

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();

      return ((!loaded) && (csvfile.RowCount() == 0) && (csvfile.ColumnCount() == 0));
    }
};

class TestCsvFile10 : public TestCase
{
  public:
    TestCsvFile10()
      : TestCase("TestCsvFile10: empty row csv file load")
    {
    }

    bool test()
    {
      String filename("test.csv");
      String separator(",");
      String value1read;
      String value2read;

      ofstream file(filename.toCharArray());
      file << separator.toCharArray()
           << separator.toCharArray()
           << endl;
      file.close();

      CsvFile csvfile(filename);
      bool loaded = csvfile.Load();

      bool found = (csvfile.ValueOf(0, 0) == "") && (csvfile.ValueOf(0, 1) == "") && 
        (csvfile.ValueOf(0, 2) == "");

      return ((loaded) && (found) && (csvfile.RowCount() == 1) && (csvfile.ColumnCount() == 3));
    }
};

class TestCsvFile11 : public TestCase
{
  public:
    TestCsvFile11()
      : TestCase("TestCsvFile11: load and save round trip.")
    {
    }

    bool test()
    {
      String filename("test2.csv");

      String r0c0("100");
      String r0c1("200");
      String r0c2("300");

      CsvFile csvfile(filename);
      vector<String> row0;
      row0.push_back(r0c0);
      row0.push_back(r0c1);
      row0.push_back(r0c2);

      csvfile.Append(row0);
      csvfile.Save();

      CsvFile csvfile2(filename);
      bool loaded = csvfile2.Load();

      bool found = (csvfile2.ValueOf(0, 0) == r0c0) && (csvfile2.ValueOf(0, 1) == r0c1) && 
        (csvfile2.ValueOf(0, 2) == r0c2);

      return ((loaded) && (found) && (csvfile2.RowCount() == 1) && (csvfile2.ColumnCount() == 3));
    }
};

TestCsvFile::TestCsvFile()
  : TestModule("CsvFile class tester")
{
  add(new TestCsvFile1());
  add(new TestCsvFile2());
  add(new TestCsvFile3());
  add(new TestCsvFile4());
  add(new TestCsvFile5());
  add(new TestCsvFile6());
  add(new TestCsvFile7());
  add(new TestCsvFile8());
  add(new TestCsvFile9());
  add(new TestCsvFile10());
  add(new TestCsvFile11());
}
