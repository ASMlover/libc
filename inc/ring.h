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
#ifndef __RING_HEADER_H__
#define __RING_HEADER_H__

typedef void** lRingIter;

extern void* ring_create(void);
extern void* ring_create_by(void* x, ...);
extern void ring_release(void** R);

extern int ring_size(void* R);
extern int ring_empty(void* R);
extern void ring_clear(void* R);

extern void* ring_push_front(void* R, void* x);
extern void* ring_push_back(void* R, void* x);
extern void* ring_pop_front(void* R);
extern void* ring_pop_back(void* R);
extern void* ring_insert(void* R, int i, void* x);
extern void* ring_erase(void* R, int i);

extern void* ring_get(void* R, int i);
extern void* ring_set(void* R, int i, void* x);
extern void* ring_front(void* R);
extern void* ring_back(void* R);

extern void ring_for_each(void* R, void (*visit)(void*, void*), void* arg);
extern void ring_rotate(void* R, int n);

#endif  /* __RING_HEADER_H__ */
