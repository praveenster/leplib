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

#ifndef LEPCPPLIB_CSVFILE_H_
#define LEPCPPLIB_CSVFILE_H_

#include <vector>
#include "String.h"

// Utility class for processing and storing csv files that contain
// rows and columns of data

namespace lepcpplib {
class CsvFile {
  public:
    CsvFile(const String& filename);
    CsvFile(const String& filename, char separator);
    ~CsvFile();

    // Loads and processes the rows and columns from filename,
    // using separator (usually space or comma or tab) as the separator.
    // If an error occurs during load, the function returns false.
    bool Load();

    void Save();

    void Append(const std::vector<String>& record);
    void Insert(const std::vector<String>& record, int row);
    void Remove(int row);

    String ValueOf(int row, int column);

    int RowCount();
    int ColumnCount();

    const String& filename();
    void set_filename(const String& filename);

  private:
    CsvFile();
    CsvFile(const CsvFile& csvfile);

    std::vector<std::vector<String>> records_;
    String filename_;
    char separator_;
};
} // namespace lepcpplib

#endif  // LEPCPPLIB_CSVFILE_H_
