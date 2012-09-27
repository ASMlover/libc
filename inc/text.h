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
 *    notice, this list of conditions and the following disclaimer in
 *  * Redistributions in binary form must reproduce the above copyright
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
#ifndef __TEXT_HEADER_H__
#define __TEXT_HEADER_H__

#include <stdarg.h>

extern void text_free(void** T);
extern int text_len(void* T);
extern const char* text_str(void* T);

extern void* text_set(const char* str);
extern char* text_get(void* T, char* str, int len);
extern void* text_box(const char* str, int len);

extern void* text_sub(void* T, int i, int j);
extern int text_pos(void* T, int i);
extern void* text_cat(void* T1, void* T2);
extern void* text_dup(void* T, int n);
extern void* text_reverse(void* T);
extern void* text_map(void* T, const void* from, const void* to);

extern int text_cmp(void* T1, void* T2);
extern int text_chr(void* T, int i, int j, int c);
extern int text_rchr(void* T, int i, int j, int c);
extern int text_upto(void* T, int i, int j, void* set);
extern int text_rupto(void* T, int i, int j, void* set);
extern int text_any(void* T, int i, void* set);
extern int text_many(void* T, int i, int j, void* set);
extern int text_rmany(void* T, int i, int j, void* set);

extern int text_find(void* T, int i, int j, void* s);
extern int text_rfind(void* T, int i, int j, void* s);
extern int text_match(void* T, int i, int j, void* s);
extern int text_rmatch(void* T, int i, int j, void* s);

extern void text_fmt(int code, va_list* app, 
  int (*visit)(int, void*), void* arg, 
  unsigned char flags[], int width, int precision);

extern void* text_save(void);
extern void text_restore(void* save);

#endif  /* __TEXT_HEADER_H__ */
