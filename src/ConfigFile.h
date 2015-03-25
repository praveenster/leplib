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

#ifndef LEP_CONFIGFILE_H_
#define	LEP_CONFIGFILE_H_

#include <map>
#include "String.h"

// Utility class for processing and storing config files that contain
// key value pairs in the form KEY=VALUE
// Sample Usage:
//   ConfigFile configfile("test.cfg");
//   bool loaded = configfile.Load();
//   if (loaded) {
//     String value;
//     bool b = configfile.ValueOf("DEFAULT_TIMEOUT", value);
//     if (b) {
//       .....

namespace lep {
class ConfigFile {
  public:
    ConfigFile(const String& filename);
    ~ConfigFile();

    // Loads and processes the key value pairs from filename.
    // If an error occurs during load, the function returns false.
    bool Load();

    void Save();

    void Add(const String& key, const String& value);
    void Remove(const String& key);

    bool ValueOf(const String& key, String& value);

    //vector<String> Keys();

    const String& filename();
    void set_filename(const String& filename);

  private:
    ConfigFile();
    ConfigFile(const ConfigFile& configfile);

    std::map<String, String> keyvalues_;
    String filename_;
};
} // namespace lep

#endif	// LEP_CONFIGFILE_H_

