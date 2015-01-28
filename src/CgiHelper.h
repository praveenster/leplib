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

#ifndef LEP_CGI_HELPER_H_
#define LEP_CGI_HELPER_H_

#include <map>
#include <vector>
#include "String.h"
#include "SmartPointer.h"

namespace lep {
class CgiHelper {
  public:
    const static String kHttpHost;
    const static String kHttpUserAgent;
    const static String kRemoteAddress;
    const static String kPathInfo;
    const static String kQueryString;
    const static int kHttpOk;

    CgiHelper();
    ~CgiHelper();

    void OutputHeader(int http_status, int content_length, const String& server_name, const String& mime_type);
    void OutputBodyText(const String& body);
    void OutputBodyFile(const String& file_name);

    void ParseEnvironmentVariables();

  public:
    std::map< String, SmartPointer<String> > environment_variables_;
    std::map< String, SmartPointer<String> > url_parameters_;
    std::vector< SmartPointer<String> > path_elements_;
};
} // namespace lep

#endif // LEP_CGI_HELPER_H_

