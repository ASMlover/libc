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
#ifndef __TABLE_HEADER_H__
#define __TABLE_HEADER_H__

typedef void** lTableIter;

extern void* table_create(int count, 
    int (*compare)(const void*, const void*), 
    unsigned int (*hash_value)(const void*));
extern void table_release(void** T);

extern int table_size(void* T);
extern int table_empty(void* T);
extern void table_clear(void* T);

extern int table_insert(void* T, const void* key, void* x);
extern void* table_remove(void* T, const void* key);
extern void* table_get(void* T, const void* key);

extern lTableIter table_begin(void* T);
extern lTableIter table_end(void* T);
extern lTableIter table_iter_next(lTableIter iter);

extern const void* table_iter_key(lTableIter iter);
extern void* table_iter_value(lTableIter iter);

extern void table_for_each(void* T, void (*visit)(const void*, void*, void*), void* arg);

#endif  /* __TABLE_HEADER_H__ */
