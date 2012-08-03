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
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/sequence.h"


#define LSEQUENCE_LEN_DEF   (16)

struct lSequence {
  void** elements;
  int    storage;
  int    size;
  int    head;
};


static void sequence_grow(struct lSequence* S)
{
  int old_storage = S->storage;
  int new_storage = (0 != old_storage ? 2 * old_storage : 1);
  
  S->elements = (void**)REALLOC(S->elements, new_storage);
  memset(S->elements + old_storage, 0, (new_storage - old_storage) * sizeof(void*));
  S->storage  = new_storage;

  if (S->head > 0)
  {
    void** old_elements = &S->elements[S->head];
    memcpy(old_elements + old_storage, old_elements, ((old_storage - S->head) * sizeof(void*)));
    S->head += old_storage;
  }
}



void* sequence_create(int storage)
{
  struct lSequence* object;

  assert(storage >= 0);
  NEW0(object);
  if (NULL != object)
  {
    storage = (0 != storage ? storage : LSEQUENCE_LEN_DEF);
    object->elements = (void**)CALLOC(storage, sizeof(void*));
    object->storage  = storage;
  }

  return object;
}

void* sequence_create_by(void* x, ...)
{
  va_list ap;
  void*   S = sequence_create(0);

  va_start(ap, x);
  for ( ; NULL != x; x = va_arg(ap, void*))
    sequence_push_back(S, x);
  va_end(ap);

  return S;
}

void sequence_release(void** S)
{
  sequence_clear(*S);
  FREE(*S);
}

int sequence_size(void* S)
{
  return (NULL != S ? ((struct lSequence*)S)->size : ERROR_LEN);
}

int sequence_empty(void* S)
{
  return (NULL != S ? (0 == ((struct lSequence*)S)->size) : 0);
}

void sequence_clear(void* S)
{
  if (NULL == S)
    return;
  FREE(((struct lSequence*)S)->elements);
  ((struct lSequence*)S)->storage = 0;
  ((struct lSequence*)S)->size    = 0;
  ((struct lSequence*)S)->head    = 0;
}

void* sequence_push_front(void* S, void* x)
{
  assert(NULL != S);
  if (((struct lSequence*)S)->size >= ((struct lSequence*)S)->storage)
    sequence_grow((struct lSequence*)S);
  if (--((struct lSequence*)S)->head < 0)
    ((struct lSequence*)S)->head = ((struct lSequence*)S)->storage - 1;
  ++((struct lSequence*)S)->size;
  ((struct lSequence*)S)->elements[((struct lSequence*)S)->head % ((struct lSequence*)S)->storage] = x;

  return x;
}

void* sequence_push_back(void* S, void* x)
{
  int i;

  assert(NULL != S);
  if (((struct lSequence*)S)->size >= ((struct lSequence*)S)->storage)
    sequence_grow((struct lSequence*)S);
  i = ((struct lSequence*)S)->size++;
  ((struct lSequence*)S)->elements[(((struct lSequence*)S)->head + i) % ((struct lSequence*)S)->storage] = x;

  return x;
}

void* sequence_pop_front(void* P)
{
  void* pop_data;
  struct lSequence* S = (struct lSequence*)P;

  assert(NULL != S && S->size > 0);
  pop_data = S->elements[S->head % S->storage];
  S->elements[S->head % S->storage] = NULL;
  S->head = (S->head + 1) % S->storage;
  --S->size;

  return pop_data;
}

void* sequence_pop_back(void* P)
{
  void* pop_data;
  int i;
  struct lSequence* S = (struct lSequence*)P;

  assert(NULL != S && S->size > 0);
  i = --S->size;
  pop_data = S->elements[(S->head + i) % S->storage];
  S->elements[(S->head + i) % S->storage] = NULL;

  return pop_data;
}

void* sequence_set(void* P, int i, void* x)
{
  void* old_x;
  struct lSequence* S = (struct lSequence*)P;

  assert(NULL != S && i >= 0 && i < S->size);
  old_x = S->elements[(S->head + i) % S->storage];
  S->elements[(S->head + i) % S->storage] = x;

  return old_x;
}

void* sequence_get(void* P, int i)
{
  struct lSequence* S = (struct lSequence*)P;

  assert(NULL != S && i >= 0 && i < S->size);
  return S->elements[(S->head + i) % S->storage];
}

void* sequence_front(void* P)
{
  struct lSequence* S = (struct lSequence*)P;

  return ((NULL != S && 0 < S->size) 
      ? S->elements[S->head % S->storage] : NULL);
}

void* sequence_back(void* P)
{
  struct lSequence* S = (struct lSequence*)P;

  return ((NULL != S && 0 < S->size) 
      ? S->elements[(S->head + (S->size - 1)) % S->storage] : NULL);
}

void sequence_for_each(void* P, void (*visit)(void*, void*), void* arg)
{
  int i;
  struct lSequence* S = (struct lSequence*)P;

  if (NULL == S || NULL == visit)
    return;
  for (i = 0; i < S->size; ++i)
    visit(S->elements[(S->head + i) % S->storage], arg);
}
