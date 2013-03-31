/*
 * Copyright (c) 2013 ASMlover. All rights reserved.
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
#ifndef __XP_HEADER_H__
#define __XP_HEADER_H__

typedef unsigned char byte_t;

extern int xp_add(int digits, byte_t* z, byte_t* x, byte_t* y, int carry);
extern int xp_sub(int digits, byte_t* z, byte_t* x, byte_t* y, int borrow);
extern int xp_mul(byte_t* z, int n, byte_t* x, int m, byte_t* y);
extern int xp_div(int n, byte_t* q, byte_t* x, int m, byte_t* y, byte_t* r, byte_t* temp);

extern int xp_sum(int n, byte_t* z, byte_t* x, int y);
extern int xp_diff(int n, byte_t* z, byte_t* x, int y);
extern int xp_product(int n, byte_t* z, byte_t* x, int y);
extern int xp_quotient(int n, byte_t* z, byte_t* x, int y);

extern int xp_neg(int n, byte_t* z, byte_t* x, int carry);
extern int xp_cmp(int n, byte_t* x, byte_t* y);
extern void xp_lshift(int n, byte_t* z, int m, byte_t* x, int s, int fill);
extern void xp_rshift(int n, byte_t* z, int m, byte_t* x, int s, int fill);

extern int xp_length(int n, byte_t* x);
extern unsigned long xp_fromint(int n, byte_t* z, unsigned long u);
extern unsigned long xp_toint(int n, byte_t* x);

extern int xp_fromstr(int n, byte_t* z, const char* str, int base, char** end);
extern char* xp_tostr(char* str, int size, int base, int n, byte_t* x);

#endif  /* __XP_HEADER_H__ */
