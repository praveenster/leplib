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

#ifndef LEP_LOGGER_H_
#define LEP_LOGGER_H_

#include <cstdio>

extern int LOGGER_LEVEL;
#define LOGGER_LEVEL_D 0
#define LOGGER_LEVEL_I 1
#define LOGGER_LEVEL_W 2
#define LOGGER_LEVEL_E 3

/*
  Reference:
  GNU: http://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
  WIN32: http://msdn.microsoft.com/en-us/library/ms177415(v=vs.80).aspx
*/

#ifdef __ENABLE_LOGGER__
#ifdef WIN32
#define LOGGER_LOG(logger_string, logger_level, format, ...)  \
do { \
  if (LOGGER_LEVEL <= logger_level) \
    printf("[%s:%s:%d] " format, logger_string, __FILE__, __LINE__, __VA_ARGS__); \
} while (0)
#define LOG_D(format, ...) LOGGER_LOG("DBG", LOGGER_LEVEL_D, format, __VA_ARGS__)
#define LOG_I(format, ...) LOGGER_LOG("INF", LOGGER_LEVEL_I, format, __VA_ARGS__)
#define LOG_W(format, ...) LOGGER_LOG("WRN", LOGGER_LEVEL_W, format, __VA_ARGS__)
#define LOG_E(format, ...) LOGGER_LOG("ERR", LOGGER_LEVEL_E, format, __VA_ARGS__)
#else
#define LOGGER_LOG(logger_string, logger_level, format, ...)  \
do { \
  if (LOGGER_LEVEL <= logger_level) \
    printf("[%s:%s:%d] "format, logger_string, __LEPFILE__, __LINE__, ## __VA_ARGS__); \
} while (0)
#define LOG_D(...) LOGGER_LOG("DBG", LOGGER_LEVEL_D, ## __VA_ARGS__)
#define LOG_I(...) LOGGER_LOG("INF", LOGGER_LEVEL_I, ## __VA_ARGS__)
#define LOG_W(...) LOGGER_LOG("WRN", LOGGER_LEVEL_W, ## __VA_ARGS__)
#define LOG_E(...) LOGGER_LOG("ERR", LOGGER_LEVEL_E, ## __VA_ARGS__)
#endif
#else
#define LOG_D(...)
#define LOG_I(...)
#define LOG_W(...)
#define LOG_E(...)
#endif

#endif // LEP_LOGGER_H_

