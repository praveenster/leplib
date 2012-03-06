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

#include "CsvFile.h"

using std::vector;

namespace lepcpplib {
CsvFile::CsvFile(const String& filename)
  : filename_(filename), separator_(',')
{
}

CsvFile::CsvFile(const String& filename, char separator)
  : filename_(filename), separator_(separator)
{
}

CsvFile::~CsvFile()
{
}

bool CsvFile::Load()
{
  return false;
}

void CsvFile::Save()
{
}

void CsvFile::Add(const std::vector<String>& record)
{
}

void CsvFile::Remove(int row)
{
}

String CsvFile::ValueOf(int row, int column)
{
  return "";
}

const String& CsvFile::filename()
{
  return filename_;
}

void CsvFile::set_filename(const String& filename)
{
}

int CsvFile::RowCount()
{
  return 0;
}

int CsvFile::ColumnCount()
{
  return 0;
}
}
