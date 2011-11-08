/*
   Copyright 2011 Neevarp Yhtroom

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
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
