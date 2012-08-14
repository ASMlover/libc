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
#ifndef __BIT_HEADER_H__
#define __BIT_HEADER_H__

extern void* bit_create(int size);
extern void bit_release(void** B);

extern int bit_size(void* B);
extern int bit_count(void* B);  /**!< number of ones in bit set. */
extern void bit_clear(void* B);

extern int bit_set(void* B, int i, int val);
extern int bit_get(void* B, int i);

extern void bit_clear_range(void* B, int beg, int end);
extern void bit_set_range(void* B, int beg, int end);
extern void bit_not_range(void* B, int beg, int end);

extern int bit_lt(void* B1, void* B2);
extern int bit_eq(void* B1, void* B2);
extern int bit_leq(void* B1, void* B2);

extern void bit_for_each(void* B, void (*visit)(int, int, void*), void* arg);

extern void* bit_union(void* B1, void* B2);
extern void* bit_inter(void* B1, void* B2);
extern void* bit_minus(void* B1, void* B2);
extern void* bit_diff(void* B1, void* B2);

#endif  /* __BIT_HEADER_H__ */
