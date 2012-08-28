/*
 * Copyright (c) 2012 ASMlover. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list ofconditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materialsprovided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <string.h>
#include <limits.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"
#include "../inc/format.h"

#include "../inc/string.h"



#define INDEX(i, len)   ((i) <= 0 ? (i) + (len) : (i) - 1)
#define CONVERT(s, i, j)\
  do {\
    int len;\
    assert(NULL != s);\
    len = strlen(s);\
    i = INDEX(i, len);\
    j = INDEX(j, len);\
    if (i > j) {\
      int t = i;\
      i = j;\
      j = t;\
    }\
  } while (0)



/**!< create strings */
char* 
string_sub(const char* s, int i, int j)
{
  char* str;
  char* iter;

  CONVERT(s, i, j);
  iter = str = ALLOC(j - i + 1);
  while (i < j)
    *iter++ = s[i++];
  *iter = '\0';

  return str;
}

char* 
string_dup(const char* s, int i, int j, int n)
{
  char* str;
  char* iter;

  assert(n >= 0);
  CONVERT(s, i, j);
  iter = str = ALLOC(n * (j - i) + 1);
  if (j - i > 0) {
    int idx;
    while (n-- > 0) {
      for (idx = i; idx < j; ++idx)
        *iter++ = s[idx];
    }
  }
  *iter = '\0';

  return str;
}

char* 
string_cat(const char* s1, int i1, int j1, const char* s2, int i2, int j2)
{
  char* str;
  char* iter;

  CONVERT(s1, i1, j1);
  CONVERT(s2, i2, j2);
  iter = str = ALLOC(j1 - i1 + j2 - i2 + 1);
  while (i1 < j1)
    *iter++ = s1[i1++];
  while (i2 < j2)
    *iter++ = s2[i2++];
  *iter = '\0';

  return str;
}

char* 
string_vcat(const char* fmt, ...)
{
  char* str;
  char* iter;
  va_list ap;
  int i, j, len = 0;
  const char* fmt_copy = fmt;

  va_start(ap, fmt);
  while (NULL != fmt) {
    i = va_arg(ap, int);
    j = va_arg(ap, int);
    CONVERT(fmt, i, j);
    len += j - i;
    fmt = va_arg(ap, const char*);
  }
  va_end(ap);
  iter = str = ALLOC(len + 1);

  fmt = fmt_copy;
  va_start(ap, fmt);
  while (NULL != fmt) {
    i = va_arg(ap, int);
    j = va_arg(ap, int);
    CONVERT(fmt, i, j);
    while (i < j)
      *iter++ = fmt[i++];
    fmt = va_arg(ap, const char*);
  }
  va_end(ap);
  *iter = '\0';

  return str;
}

char* 
string_reverse(const char* s, int i, int j)
{
  char* str;
  char* iter;

  CONVERT(s, i, j);
  iter = str = ALLOC(j - i + 1);
  while (j > i)
    *iter++ = s[--j];
  *iter = '\0';

  return str;
}

char* 
string_map(const char* s, int i, int j, const char* from, const char* to)
{
  static char map[256] = {0};

  if (NULL != from && NULL != to) {
    unsigned int c;
    for (c = 0; c < sizeof(map); ++c)
      map[c] = c;
    while (0 != *from && 0 != *to)
      map[(unsigned char)*from++] = *to++;
    assert(0 == *from && 0 == *to);
  } else {
    assert(NULL == from && NULL == to && NULL != s);
    assert(0 != map['a']);
  }

  if (NULL != s) {
    char* str;
    char* iter;

    CONVERT(s, i, j);
    iter = str = ALLOC(j - i + 1);
    while (i < j)
      *iter++ = map[(unsigned char)s[i++]];
    *iter = '\0';

    return str;
  }

  return NULL;
}


/**!< posistion */
int 
string_pos(const char* s, int i)
{
  int len;

  assert(NULL != s);
  len = strlen(s);
  i = INDEX(i, len);
  assert(i >= 0 && i <= len);

  return i + 1;
}

int 
string_len(const char* s, int i, int j)
{
  CONVERT(s, i, j);
  return (j - i);
}

int 
string_cmp(const char* s1, int i1, int j1, const char* s2, int i2, int j2)
{
  CONVERT(s1, i1, j1);
  CONVERT(s2, i2, j2);
  s1 += i1;
  s2 += i2;

  if (j1 - i1 < j2 - i2) {
    int cond = strncmp(s1, s2, j1 - i1);
    return (0 == cond ? -1 : cond);
  } else if (j1 - i1 > j2 - i2) {
    int cond = strncmp(s1, s2, j2 - i2);
    return (0 == cond ? 1 : cond);
  } else 
    return strncmp(s1, s2, j1 - i1);
}

int 
string_chr(const char* s, int i, int j, int c)
{
  CONVERT(s, i, j);
  for ( ; i < j; ++i) {
    if (c == s[i])
      return (i + 1);
  }

  return 0;
}

int 
string_rchr(const char* s, int i, int j, int c)
{
  CONVERT(s, i, j);
  while (j > i) {
    if (c == s[--j])
      return (j + 1);
  }

  return 0;
}

int 
string_upto(const char* s, int i, int j, const char* set)
{
  assert(NULL != set);
  CONVERT(s, i, j);
  for ( ; i < j; ++i) {
    if (NULL != strchr(set, s[i]))
      return (i + 1);
  }

  return 0;
}

int 
string_rupto(const char* s, int i, int j, const char* set)
{
  assert(NULL != set);
  CONVERT(s, i, j);
  while (j > i) {
    if (NULL != strchr(set, s[--j]))
      return (j + 1);
  }

  return 0;
}

int 
string_find(const char* s, int i, int j, const char* search)
{
  int len;

  assert(NULL != search);
  CONVERT(s, i, j);
  len = strlen(search);
  if (0 == len)
    return (i + 1);
  else if (1 == len) {
    for ( ; i < j; ++i) {
      if (s[i] == *search)
        return (i + 1);
    }
  } else {
    for ( ; i + len <= j; ++i) {
      if (0 == strncmp(&s[i], search, len))
        return (i + 1);
    }
  }

  return 0;
}

int 
string_rfind(const char* s, int i, int j, const char* search)
{
  int len;

  assert(NULL != search);
  CONVERT(s, i, j);
  len = strlen(search);
  if (0 == len)
    return (j + 1);
  else if (1 == len) {
    while (j > i) {
      if (s[--j] == *search)
        return (j + 1);
    }
  } else {
    for ( ; j - len >= i; --j) {
      if (0 == strncmp(&s[j - len], search, len))
        return (j - len + 1);
    }
  }

  return 0;
}

int 
string_any(const char* s, int i, const char* set)
{
  int len;
  
  assert(NULL != s && NULL != set);
  len = strlen(set);
  i = INDEX(i, len);
  assert(i >= 0 && i <= len);
  if (i < len && NULL != strchr(set, s[i]))
    return (i + 2);

  return 0;
}

int 
string_many(const char* s, int i, int j, const char* set)
{
  assert(NULL != set);
  CONVERT(s, i, j);

  if (i < j && NULL != strchr(set, s[i])) {
    do {
      ++i;
    } while (i < j && NULL != strchr(set, s[i]));
    return (i + 1);
  }

  return 0;
}

int 
string_rmany(const char* s, int i, int j, const char* set)
{
  assert(NULL != set);
  CONVERT(s, i, j);

  if (j > i && NULL != strchr(set, s[j - 1])) {
    do {
      --j;
    } while (j > i && NULL != strchr(set, s[j]));
    return (i + 2);
  }

  return 0;
}

int 
string_match(const char* s, int i, int j, const char* match)
{
  int len;

  assert(NULL != match);
  CONVERT(s, i, j);
  len = strlen(match);
  if (0 == len)
    return (i + 1);
  else if (1 == len) {
    if (i < j && s[i] == *match)
      return (i + 2);
  } else if (i + len <= j && (0 == strncmp(&s[i], match, len)))
    return (i + len + 1);

  return 0;
}

int 
string_rmatch(const char* s, int i, int j, const char* match)
{
  int len;

  assert(NULL != match);
  CONVERT(s, i, j);
  len =  strlen(match);
  if (0 == len)
    return (i + 1);
  else if (1 == len) {
    if (j > i && s[j - 1] == *match)
      return j;
  } else if (j - len >= i && (0 == strncmp(&s[j - len], match, len)))
    return (j - len + 1);

  return 0;
}

void 
string_fmt(int code, va_list* app, int (*visit)(int, void*), 
  void* arg, unsigned char flags[], int width, int precision)
{
  char* s;
  int i, j;

  assert(NULL != app && NULL != flags);
  s = va_arg(app, char*);
  i = va_arg(app, int);
  j = va_arg(app, int);
  CONVERT(s, i, j);

  format_puts(s + i, j - i, visit, arg, flags, width, precision);
}
