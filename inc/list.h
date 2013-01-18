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

typedef struct list_s* list_t;
typedef element_t* list_iter_t;

extern list_t list_create(void);
extern void list_release(list_t* L);

extern int list_size(list_t L);
extern int list_empty(list_t L);
extern void list_clear(list_t L, void (*destroy)(void*));

extern int list_push_back(list_t L, element_t x);
extern int list_push_front(list_t L, element_t x);
extern int list_insert(list_t L, list_iter_t pos, element_t x);
extern element_t list_pop_back(list_t L);
extern element_t list_pop_front(list_t L);
extern element_t list_erase(list_t L, list_iter_t pos);

extern list_iter_t list_begin(list_t L);
extern list_iter_t list_end(list_t L);
extern list_iter_t list_iter_next(list_iter_t iter);

extern element_t list_front(list_t L);
extern element_t list_back(list_t L);

extern void list_for_each(list_t L, 
  void (*visit)(element_t, void*), void* arg);

#endif  /* __LIST_HEADER_H__ */
