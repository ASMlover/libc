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
#include <float.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include "../inc/config.h"
#include "../inc/except.h"
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/format.h"




struct lFormatBuf {
  char* begin;
  char* next;
  int   size;
};


#define PAD(n, c, visit, arg)\
  do {\
    int count = (n);\
    while (count-- > 0)\
      visit((c), (arg));\
  } while (0)


static void 
convert_s(int code, va_list* app, int (*visit)(int, void*),
  void* arg, unsigned char flags[], int width, int precision)
{
  char* str = va_arg(*app, char*);

  assert(NULL != str);
  format_puts(str, strlen(str), visit, arg, flags, width, precision);
}

static void 
convert_d(int code, va_list* app, int (*visit)(int, void*), 
  void* arg, unsigned char flags[], int width, int precision)
{
  int val = va_arg(*app, int);
  unsigned int m;
  char buf[64];
  char* it = buf + sizeof(buf);

  if (INT_MIN == val)
    m = INT_MAX + 1U;
  else if (val < 0)
    m = -val;
  else 
    m = val;

  do {
    *--it = m % 10 + '0';
  } while ((m /= 10) > 0);
  if (val < 0)
    *--it = '-';

  format_putd(it, (buf + sizeof(buf)) - it, visit, arg, flags, width, precision);
}

static void 
convert_u(int code, va_list* app, int (*visit)(int, void*), 
  void* arg, unsigned char flags[], int width, int precision)
{
  unsigned int val = va_arg(*app, unsigned int);
  char buf[64];
  char* it = buf + sizeof(buf);

  do {
    *--it = val % 10 + '0';
  } while ((val /= 10) > 0);

  format_putd(it, (buf + sizeof(buf)) - it, visit, arg, flags, width, precision);
}

static void 
convert_o(int code, va_list* app, int (*visit)(int, void*), 
  void* arg, unsigned char flags[], int width, int precision)
{
  unsigned int val = va_arg(*app, unsigned int);
  char buf[64];
  char* it = buf + sizeof(buf);

  do {
    *--it = (val & 0x7) + '0';
  } while (0 != (val >>= 3));

  format_putd(it, (buf + sizeof(buf)) - it, visit, arg, flags, width, precision);
}


static void 
convert_x(int code, va_list* app, int (*visit)(int, void*), 
  void* arg, unsigned char flags[], int width, int precision)
{
  unsigned int val = va_arg(*app, unsigned int);
  char buf[64];
  char* it = buf + sizeof(buf);

  do {
    *--it = "0123456789abcdef"[val & 0xF];
  } while (0 != (val >>= 4));

  format_putd(it, (buf + sizeof(buf)) - it, visit, arg, flags, width, precision);
}

static void 
convert_p(int code, va_list* app, int (*visit)(int, void*), 
  void* arg, unsigned char flags[], int width, int precision)
{
  unsigned long val = (unsigned long)va_arg(*app, void*);
  char buf[64];
  char* it = buf + sizeof(buf);

  precision = INT_MIN;
  do {
    *--it = "0123456789abcdef"[val & 0xF];
  } while (0 != (val >>= 4));

  format_putd(it, (buf + sizeof(buf)) - it, visit, arg, flags, width, precision);
}

static void 
convert_c(int code, va_list* app, int (*visit)(int, void*), 
  void* arg, unsigned char flags[], int width, int precision)
{
  if (INT_MIN == width)
    width = 0;
  if (width < 0) {
    flags['-'] = 1;
    width = -width;
  }
  if (0 != flags['-'])
    PAD(width - 1, ' ', visit, arg);
  
  visit((unsigned char)va_arg(*app, int), arg);
  if (0 != flags['-'])
    PAD(width - 1, ' ', visit, arg);
}

static void 
convert_f(int code, va_list* app, int (*visit)(int, void*), 
  void* arg, unsigned char flags[], int width, int precision)
{
  static char fmt[] = "%.dd?";
  char buf[DBL_MAX_10_EXP + 1 + 1 + 99 + 1];

  if (precision < 0)
    precision = 6;
  if ('g' == code && 0 == precision)
    precision = 1;

  assert(precision <= 99);
  fmt[4] = code;
  fmt[3] = precision % 10 + '0';
  fmt[2] = (precision / 10) % 10 + '0';
  sprintf(buf, fmt, va_arg(*app, double));

  format_putd(buf, strlen(buf), visit, arg, flags, width, precision);
}


static char* lfmt_flags = "-+ 0";
static const struct lExcept lfmt_overflow = { "Formatting overflow" };
static format_callback_t convert_list[256] = {
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 0   ~ 7   */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 8   ~ 15  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 16  ~ 23  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 24  ~ 31  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 32  ~ 39  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 40  ~ 47  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 48  ~ 55  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 56  ~ 63  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 64  ~ 71  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 72  ~ 79  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 80  ~ 87  */
  0,         0, 0, 0,         0,         0,         0,         0,         /**!< 88  ~ 95  */
  0,         0, 0, convert_c, convert_d, convert_f, convert_f, convert_f, /**!< 96  ~ 103 */
  0,         0, 0, 0,         0,         0,         0,         convert_o, /**!< 104 ~ 111 */
  convert_p, 0, 0, convert_s, 0,         convert_u, 0,         0,         /**!< 112 ~ 119 */
  convert_x, 0, 0, 0,         0,         0,         0,         0,         /**!< 120 ~ 127 */
};




static inline int 
output_c(int c, void* arg) 
{
  return fputc(c, (FILE*)arg);
}

static inline int 
insert_c(int c, void* arg) 
{
  struct lFormatBuf* buf = (struct lFormatBuf*)arg;

  if (buf->next >= buf->begin + buf->size)
    RAISE(lfmt_overflow);
  *buf->next++ = c;

  return c;
}

static inline int 
append_c(int c, void* arg)
{
  struct lFormatBuf* buf = (struct lFormatBuf*)arg;

  if (buf->next >= buf->begin + buf->size) {
    REALLOC(buf->begin, 2 * buf->size);
    buf->next = buf->begin + buf->size;
    buf->size *= 2;
  }
  *buf->next++ = c;

  return c;
}





format_callback_t 
format_register(int code, format_callback_t convert)
{
  format_callback_t old_callback;

  assert(0 < code && code < COUNTOF(convert_list));
  old_callback = convert_list[code];
  convert_list[code] = convert;

  return old_callback;
}

void 
format_fmt(int (*visit)(int, void*), void* arg, const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  format_vfmt(visit, arg, fmt, ap);
  va_end(ap);
}

void 
format_vfmt(int (*visit)(int, void*), void* arg, const char* fmt, va_list ap)
{
  assert(NULL != visit && NULL != fmt);

  while (*fmt) {
    if ('%' != *fmt || '%' == *++fmt)
      visit((unsigned char)*fmt++, arg);
    else {
      unsigned char c, flags[256] = {0};
      int width = INT_MIN, precision = INT_MIN;

      if (NULL != lfmt_flags) {
        unsigned char cc = *fmt;
        for ( ; 0 != cc && NULL != strchr(lfmt_flags, cc); cc = *++fmt) {
          assert(flags[cc] < 255);
          ++flags[cc];
        }
      }
      if ('*' == *fmt || isdigit(*fmt)) {
        int n;
        if ('*' == *fmt) {
          n = va_arg(ap, int);
          assert(INT_MIN != n);
          ++fmt;
        } else {
          for (n = 0; isdigit(*fmt); ++fmt) {
            int d = *fmt - '0';
            assert(n <= (INT_MAX - d) / 10);
            n = 10 * n + d;
          }
          width = n;
        }
      }

      if ('.' == *fmt && ('*' == *++fmt || isdigit(*fmt))) {
        int n;
        if ('*' == *fmt) {
          n = va_arg(ap, int);
          assert(INT_MIN != n);
          ++fmt;
        } else {
          for (n = 0; isdigit(*fmt); ++fmt) {
            int d = *fmt - '0';
            assert(n <= (INT_MAX - d) / 10);
            n = 10 * n + d;
          }
        }
        precision = n;
      }
      c = *fmt++;
      assert(NULL != convert_list[c]);
      convert_list[c](c, &ap, visit, arg, flags, width, precision);
    }
  }
}

void 
format_printf(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  format_vfmt(output_c, stdout, fmt, ap);
  va_end(ap);
}

void 
format_fprintf(FILE* stream, const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  format_vfmt(output_c, stream, fmt, ap);
  va_end(ap);
}

int 
format_sprintf(char* dest, int count, const char* fmt, ...)
{
  int ret;
  va_list ap;

  va_start(ap, fmt);
  ret = format_vsprintf(dest, count, fmt, ap);
  va_end(ap);

  return ret;
}

int 
format_vsprintf(char* dest, int count, const char* fmt, va_list ap)
{
  struct lFormatBuf buf;
  
  assert(NULL != dest && count > 0 && NULL != fmt);
  buf.begin = buf.next = dest;
  buf.size  = count;
  format_vfmt(insert_c, &buf, fmt, ap);
  insert_c(0, &buf);

  return (buf.next - buf.begin - 1);
}

char* 
format_string(const char* fmt, ...)
{
  char* str;
  va_list ap;

  assert(NULL != fmt);
  va_start(ap, fmt);
  str = format_vstring(fmt, ap);
  va_end(ap);

  return str;
}

char* 
format_vstring(const char* fmt, va_list ap)
{
  struct lFormatBuf buf;

  assert(NULL != fmt);
  buf.size = 256;
  buf.begin = buf.next = CALLOC(1, buf.size);
  format_vfmt(append_c, &buf, fmt, ap);
  append_c(0, &buf);

  return REALLOC(buf.begin, buf.next - buf.begin);
}

void 
format_putd(const char* s, int len, int (*visit)(int, void*), 
  void* arg, unsigned char flags[256], int width, int precision)
{
  int i, n, sign;

  assert(NULL != s && len >= 0 && NULL != flags);
  if (INT_MIN == width)
    width = 0;
  if (width < 0) {
    flags['-'] = 1;
    width = -width;
  }
  if (precision >= 0)
    flags['0'] = 0;
  if (len > 0 && ('-' == *s || '+' == *s)) {
    sign = *s++;
    --len;
  } else if (0 != flags['+'])
    sign = '+';
  else if (0 != flags[' '])
    sign = ' ';
  else
    sign = 0;

  if (precision < 0)
    precision = 1;
  if (len < precision)
    n = precision;
  else if (0 == precision && 1 == len && '0' == s[0])
    n = 0;
  else 
    n = len;

  if (sign)
    ++n;
  if (0 != flags['-']) {
    if (sign)
      visit(sign, arg);
  } else if (0 != flags['0']) {
    if (sign)
      visit(sign, arg);
    PAD(width - n, '0', visit, arg);
  } else {
    PAD(width - n, ' ', visit, arg);
    if (sign)
      visit(sign, arg);
  }
  PAD(precision - len, '0', visit, arg);

  for (i = 0; i < len; ++i)
    visit((unsigned char)*s++, arg);

  if (0 != flags['-'])
    PAD(width - n, ' ', visit, arg);
}

void 
format_puts(const char* s, int len, int (*visit)(int, void*), 
  void* arg, unsigned char flags[256], int width, int precision)
{
  int i;
  assert(NULL != s && len >= 0 && NULL != flags);

  if (INT_MIN == width)
    width = 0;
  if (width < 0) {
    flags['-'] = 1;
    width = -width;
  }
  if (precision >= 0)
    flags['0'] = 0;
  if (precision >= 0 && precision < len)
    len = precision;
  if (0 == flags['-'])
    PAD(width - len, ' ', visit, arg);
  for (i = 0; i < len; ++i)
    visit((unsigned char)*s++, arg);

  if (0 != flags['-'])
    PAD(width - len, ' ', visit, arg);
}
