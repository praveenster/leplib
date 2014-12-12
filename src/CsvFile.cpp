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
#include <string>
#include "CsvFile.h"

using std::vector;
using std::ifstream;
using std::ofstream;
using std::endl;

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
  std::string buffer;
  ifstream file(filename_.toCharArray(), ifstream::binary);

  while((!file.eof()) && (file.good())) {
    parsable = true;
    getline(file, buffer);
    String line(buffer.c_str());
    unsigned int length = line.length();

    // getline reads up to \n. if the terminator is \r\n
    // then "line" will contain an extra \r in the end.
    // we can't use String::trim here because it might remove
    // valid trailing whitespace. we just need to handle
    // this unexpected behavior of getline.
    if ((length >= 1) && (line.charAt(length - 1) == '\r')) {
      // if the line was just \r\n, then getline would return a string
      // with just \r. in that case, there is nothing on that line
      // to include as it is an empty line.
      if (length == 1) {
        line = "";
      }
      else {
        line = line.substring(0, length - 2);
      }

      // update the new length as we removed a \r
      length -= 1;
    }

    if (length > 0) {
      vector<String> row;
      line.tokenize(separator_, row);
      records_.push_back(row);
    }
  }

  return parsable;
}

void CsvFile::Save()
{
  ofstream file(filename_.toCharArray());
  for (int i = 0; i < records_.size(); i++) {
    vector<String>& row = records_[i];
    for (int j = 0; j < row.size(); j++) {
      if (row[j].length()) {
        file << row[j].toCharArray();
      }
      else {
        file << "";
      }

      // no separator for last column.
      if (j != row.size() - 1) {
        file << separator_;
      }
    }

    file << endl;
  }

  file << endl;
}

void CsvFile::Append(const std::vector<String>& record)
{
  records_.push_back(record);
}

void CsvFile::Insert(const std::vector<String>& record, int row)
{
  if (row > 0) {
    if (row > records_.size()) {
      int new_entries = row - records_.size();
      vector<String> blank;
      blank.insert(blank.begin(), record.size(), "");

      for (int i = 0; i < new_entries; i++) {
        records_.push_back(blank);
      }
    }

    records_.insert(records_.begin() + row, record);
  }
}

void CsvFile::Remove(int row)
{
  if ((row < records_.size()) && (row >= 0)) {
    vector< vector<String> >::iterator it = records_.begin();
    records_.erase(it + row);
  }
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
} // namespace lepcpplib
