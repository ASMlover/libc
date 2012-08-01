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
#ifndef __SEQUENCE_HEADER_H__
#define __SEQUENCE_HEADER_H__

typedef void** lSequenceIter;

extern void* sequence_create(int storage);
extern void* sequence_create_by(void* x, ...);
extern void sequence_release(void** S);

extern int sequence_size(void* S);
extern int sequence_empty(void* S);
extern void sequence_clear(void* S);

extern void* sequence_push_front(void* S, void* x);
extern void* sequence_push_back(void* S, void* x);
extern void* sequence_pop_front(void* S);
extern void* sequence_pop_back(void* S);
extern void* sequence_set(void* S, int i, void* x);
extern void* sequence_get(void* S, int i);

extern lSequenceIter sequence_begin(void* S);
extern lSequenceIter sequence_end(void* S);
extern lSequenceIter sequence_iter_next(lSequenceIter iter);

extern void* sequence_front(void* S);
extern void* sequence_back(void* S);

extern void sequence_for_each(void* S, void (*visit)(void*, void*), void* arg);

#endif  /* __SEQUENCE_HEADER_H__ */
