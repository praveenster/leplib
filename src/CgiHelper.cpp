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

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "CgiHelper.h"

using std::vector;
using std::map;

namespace lep {
const String CgiHelper::kHttpHost = "HTTP_HOST";
const String CgiHelper::kHttpUserAgent = "HTTP_USER_AGENT";
const String CgiHelper::kRemoteAddress = "REMOTE_ADDR";
const String CgiHelper::kPathInfo = "PATH_INFO";
const String CgiHelper::kQueryString = "QUERY_STRING";
const int CgiHelper::kHttpOk = 200;
const int kOutputFileBufferSize = 1024;

CgiHelper::CgiHelper()
  : environment_variables_(),
    url_parameters_(),
    path_elements_()
{
}

CgiHelper::~CgiHelper()
{
}

void CgiHelper::OutputHeader(int http_status, int content_length, const String& server_name,
  const String& mime_type)
{
  String status;

  switch (http_status) {
    default:
    case kHttpOk:
      status = "200 OK";
      break;
  }

  time_t timestamp = time(NULL);
  tm* gmt = gmtime(&timestamp);
  char current_time[1024];
  strftime(current_time, sizeof(current_time), "%a, %d %b %Y %H:%M:%S %Z", gmt);

  printf("Status: %s\r\n", status.toCharArray());
  printf("Date: %s\r\n", current_time);
  printf("Server: %s\r\n", server_name.toCharArray());
  printf("Content-Type: %s\r\n", mime_type.toCharArray());
  printf("Content-Length: %d\r\n", content_length);
  printf("Connection: close\r\n");
  printf("\r\n");
}

void CgiHelper::OutputBodyText(const String& body)
{
  printf("%s", body.toCharArray());
}

void CgiHelper::OutputBodyFile(const String& file_name)
{
  FILE* file = fopen(file_name.toCharArray(), "r");

  if (file != NULL) {
    char buffer[kOutputFileBufferSize];
    int bytes_read = 0;

    while (!feof(file)) {
      bytes_read = fread(buffer, 1, kOutputFileBufferSize, file);
      if (bytes_read > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
      }
    }
  }
}

void CgiHelper::ParseEnvironmentVariables()
{
  environment_variables_[kPathInfo] = new String(getenv(kPathInfo.toCharArray()));
  environment_variables_[kHttpHost] = new String(getenv(kHttpHost.toCharArray()));
  environment_variables_[kHttpUserAgent] = new String(getenv(kHttpUserAgent.toCharArray()));
  environment_variables_[kRemoteAddress] = new String(getenv(kRemoteAddress.toCharArray()));
  environment_variables_[kQueryString] = new String(getenv(kQueryString.toCharArray()));

  // first parse parameters passed through key-value pairs in the QUERY_STRING
  // these are typically passed in as key=value with an & separating them.
  vector<String> parameters;
  environment_variables_[kQueryString]->tokenize('&', parameters);

  for (int i = 0; i < (int)parameters.size(); i++) {
    vector<String> key_values;

    parameters[i].tokenize('=', key_values);
    if (key_values.size() == 2) {
      url_parameters_[key_values[0]] = new String(key_values[1]);
    }
    else {
      break;
    }
  }

  // next parse the path elements in the url. these are separated by a /.
  // PATH_INFO starts with a / as a separator, which will make the tokenizer add an empty
  // string as the first token (expected behavior). but CGI applications aren't necessarily
  // interested in the empty string. so the loop below starts from 1 instead of  0.
  parameters.clear();
  environment_variables_[kPathInfo]->tokenize('/', parameters);
  for (int i = 1; i < parameters.size(); ++i) {
    path_elements_.push_back(new String(parameters[i]));
  }
}
} // namespace lep

