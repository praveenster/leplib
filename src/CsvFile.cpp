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
#include "CsvFile.h"

using std::vector;
using std::ifstream;

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
  bool parsable = false;
  char buffer[10];
  String line;
  ifstream file(filename_.toCharArray(), ifstream::binary);

  while((!file.eof()) && (file.good())) {
    file.read(buffer, sizeof(buffer));
    int pend = file.gcount();
    parsable = true;
    int pbegin = 0;
    int pcurrent = 0;

    while (pcurrent < pend) {
      if (buffer[pcurrent] == '\n') {

        String part(buffer + pbegin, (pcurrent - pbegin + 1));
        line += part;
        int l = line.length();

        if ((l == 1) && (line.charAt(0) == '\n')) {
          // empty line. ignore.
          line = "";
        }
        else if ((l == 2) && (line.charAt(0) == '\r') && (line.charAt(1) == '\n')) {
          // empty line. ignore.
          line = "";
        }
        else if ((l > 2) && 
            (line.charAt(l - 2) == '\r') &&
            (line.charAt(l - 1) == '\n')) {
              line = line.substring(0, l - 3);
        }
        else if ((l > 1) && 
            (line.charAt(l - 1) == '\n')) {
              line = line.substring(0, l - 2);
        }

        if (line.length() > 0) {
          vector<String> row;
          line.tokenize(separator_, row);
          records_.push_back(row);
        }

        pbegin = pcurrent + 1;
      }

      pcurrent++;
    }

    if (pbegin < pcurrent) {
      String part(buffer + pbegin, pend - pbegin);
      line = part;
    }
  }

  return parsable;
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
  if ((row < records_.size()) && (column < records_[row].size())) {
    return (records_[row][column]);
  }
  else {
    return "";
  }
}

const String& CsvFile::filename()
{
  return filename_;
}

void CsvFile::set_filename(const String& filename)
{
  filename_ = filename;
}

int CsvFile::RowCount()
{
  return records_.size();
}

int CsvFile::ColumnCount()
{
  int result = 0;

  if (records_.size() > 0) {
    // csv files should have identical column count for all rows.
    result = records_[0].size();
  }

  return result;
}
}
