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

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <cstdio>

extern int DEBUG_LEVEL;
#define DEBUG_LEVEL_D 0
#define DEBUG_LEVEL_I 1
#define DEBUG_LEVEL_W 2
#define DEBUG_LEVEL_E 3

/* 
  Reference:
  GNU: http://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
  WIN32: http://msdn.microsoft.com/en-us/library/ms177415(v=vs.80).aspx
*/

#ifdef __ENABLE_DEBUG_LOG__
#ifdef WIN32
#define DEBUG_LOG(debug_string, debug_level, format, ...)  \
do { \
  if (DEBUG_LEVEL <= debug_level) \
    printf("[%s:%s:%d] " format, debug_string, __FILE__, __LINE__, __VA_ARGS__); \
} while (0)
#define DEBUG_D(format, ...) DEBUG_LOG("DBG", DEBUG_LEVEL_D, format, __VA_ARGS__)
#define DEBUG_I(format, ...) DEBUG_LOG("INF", DEBUG_LEVEL_I, format, __VA_ARGS__)
#define DEBUG_W(format, ...) DEBUG_LOG("WRN", DEBUG_LEVEL_W, format, __VA_ARGS__)
#define DEBUG_E(format, ...) DEBUG_LOG("ERR", DEBUG_LEVEL_E, format, __VA_ARGS__)
#else
#define DEBUG_LOG(debug_string, debug_level, format, ...)  \
do { \
  if (DEBUG_LEVEL <= debug_level) \
    printf("[%s:%s:%d] "format, debug_string, __FILE__, __LINE__, ## __VA_ARGS__); \
} while (0)
#define DEBUG_D(...) DEBUG_LOG("DBG", DEBUG_LEVEL_D, ## __VA_ARGS__)
#define DEBUG_I(...) DEBUG_LOG("INF", DEBUG_LEVEL_I, ## __VA_ARGS__)
#define DEBUG_W(...) DEBUG_LOG("WRN", DEBUG_LEVEL_W, ## __VA_ARGS__)
#define DEBUG_E(...) DEBUG_LOG("ERR", DEBUG_LEVEL_E, ## __VA_ARGS__)
#endif
#else
#define DEBUG_D(...) 
#define DEBUG_I(...) 
#define DEBUG_W(...) 
#define DEBUG_E(...)
#endif

#endif // __DEBUG_H__
