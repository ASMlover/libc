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
#ifndef __LIST_HEADER_H__
#define __LIST_HEADER_H__

#define ERROR_LEN   (-1)
#define RESULT_OK   (0)
#define RESULT_FAIL (1)

typedef void** lListIter;

extern void* list_create(void);
extern void list_release(void** L);

extern int list_size(void* L);
extern int list_empty(void* L);
extern void list_clear(void* L, void (*destroy)(void*));

extern int list_push_back(void* L, void* x);
extern int list_push_front(void* L, void* x);
extern int list_insert(void* L, lListIter pos, void* x);
extern void* list_pop_back(void* L);
extern void* list_pop_front(void* L);
extern void* list_erase(void* L, lListIter pos);

extern lListIter list_begin(void* L);
extern lListIter list_end(void* L);
extern lListIter list_iter_next(lListIter iter);

extern void* list_front(void* L);
extern void* list_back(void* L);

extern void list_for_each(void* L, void (*visit)(void*, void*), void* arg);

#endif  /* __LIST_HEADER_H__ */
