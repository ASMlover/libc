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
#ifndef __FORMAT_HEADER_H__
#define __FORMAT_HEADER_H__

#include <stdio.h>
#include <stdarg.h>

typedef void (*format_callback_t)(int code, va_list* app, 
  int (*visit)(int c, void* arg), void* arg, 
  unsigned char flags[256], int width, int precision);

extern format_callback_t format_register(int code, format_callback_t cb);

extern void format_fmt(int (*visit)(int, void*), void* arg, const char* fmt, ...);
extern void format_vfmt(int (*visit)(int, void*), void* arg, const char* fmt, va_list ap);
extern void format_printf(const char* fmt, ...);
extern void format_fprintf(FILE* stream, const char* fmt, ...);
extern int format_sprintf(char* dest, int count, const char* fmt, ...);
extern int format_vsprintf(char* dest, int count, const char* fmt, va_list ap);
extern char* format_string(const char* fmt, ...);
extern char* format_vstring(const char* fmt, va_list ap);

extern void format_putd(const char* s, int len, int (*visit)(int, void*), 
    void* arg, unsigned char flags[256], int width, int precision);
extern void format_puts(const char* s, int len, int (*visit)(int, void*), 
    void* arg, unsigned char flags[256], int width, int precision);

#endif  /* __FORMAT_HEADER_H__ */
