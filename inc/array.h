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
#ifndef __ARRAY_HEADER_H__
#define __ARRAY_HEADER_H__

typedef void** lArrayIter;

extern void* array_create(int storage);
extern void array_release(void** A);

extern int array_size(void* A);
extern int array_empty(void* A);
extern void array_clear(void* A);

extern int array_push_back(void* A, void* x);
extern void* array_pop_back(void* A);
extern void* array_set(void* A, int i, void* x);
extern void* array_get(void* A, int i);
extern lArrayIter array_insert(void* A, lArrayIter pos, void* x);
extern lArrayIter array_erase(void* A, lArrayIter pos);
extern void* array_remove(void* A, int i);

extern void* array_front(void* A);
extern void* array_back(void* A);

extern lArrayIter array_begin(void* A);
extern lArrayIter array_end(void* A);
extern lArrayIter array_iter_next(lArrayIter iter);

extern void array_for_each(void* A, void (*visit)(void*, void*), void* arg);
extern void* array_copy(void* A, int copy_len);
extern void array_resize(void* A, int storage);

#endif  /* __ARRAY_HEADER_H__ */
