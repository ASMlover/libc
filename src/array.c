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
#include <string.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/array.h"


struct lArray {
  void** elements;
  void** begin;
  void** end;
  void** end_of_storage;
};




void* array_create(int storage)
{
  struct lArray* object;

  NEW0(object);
  if (NULL != object)
  {
    if (0 != storage)
    {
      object->elements = (void**)CALLOC(storage, sizeof(void*));
      object->begin    = object->elements;
      object->end      = object->elements + storage;
      object->end_of_storage = object->end;
    }
  }

  return object;
}

void array_release(void** A)
{
  array_clear(*A);
  FREE(*A);
}

int array_size(void* A)
{
  return (NULL != A ? (((struct lArray*)A)->end - ((struct lArray*)A)->begin) : ERROR_LEN);
}

int array_empty(void* A)
{
  return (array_begin(A) == array_end(A));
}

void array_clear(void* A)
{
  if (NULL != A)
  {
    FREE(((struct lArray*)A)->elements);
    ((struct lArray*)A)->begin          = ((struct lArray*)A)->elements;
    ((struct lArray*)A)->end            = ((struct lArray*)A)->elements;
    ((struct lArray*)A)->end_of_storage = ((struct lArray*)A)->elements;
  }
}

int array_push_back(void* A, void* x)
{
  return (NULL != array_insert(A, array_end(A), x) ? RESULT_OK : RESULT_FAIL);
}

void* array_pop_back(void* A)
{
  void* pop_data;

  if (NULL == A)
    return NULL;
  --((struct lArray*)A)->end;
  pop_data = *((struct lArray*)A)->end;
  *((struct lArray*)A)->end = NULL;

  return pop_data;
}

void* array_set(void* A, int i, void* x)
{
  assert(NULL != A && i >= 0 && i < array_size(A));
  ((struct lArray*)A)->elements[i] = x;

  return x;
}

void* array_get(void* A, int i)
{
  assert(NULL != A && i >= 0 && i < array_size(A));
  return ((struct lArray*)A)->elements[i];
}

void* array_insert(void* A, lArrayIter pos, void* x)
{
  assert(NULL != A);
  if (((struct lArray*)A)->end < ((struct lArray*)A)->end_of_storage && pos == array_end(A))
  {
    *((struct lArray*)A)->end = x;
    ++((struct lArray*)A)->end;
  }
  else 
  {
    if (((struct lArray*)A)->end < ((struct lArray*)A)->end_of_storage)
    {
      memmove(pos + 1, pos, (array_end(A) - pos) * sizeof(void*));
      ++((struct lArray*)A)->end;
      *pos = x;
    }
    else
    {
      int old_size = ((struct lArray*)A)->end - ((struct lArray*)A)->begin;
      int new_size = (0 != old_size ? 2 * old_size : 1);
      void** new_elements = (void**)CALLOC(new_size, sizeof(void*));

      memcpy(new_elements, ((struct lArray*)A)->elements, (pos - ((struct lArray*)A)->begin) * sizeof(void*));
      *(void**)((char*)new_elements + (pos - ((struct lArray*)A)->begin) * sizeof(void*)) = x;
      memcpy((char*)new_elements + (pos - ((struct lArray*)A)->begin + 1) * sizeof(void*), 
        ((struct lArray*)A)->elements + (pos - ((struct lArray*)A)->begin) * sizeof(void*), 
        (((struct lArray*)A)->end - pos) * sizeof(void*));

      FREE(((struct lArray*)A)->elements);
      ((struct lArray*)A)->elements       = new_elements;
      ((struct lArray*)A)->begin          = new_elements;
      ((struct lArray*)A)->end            = new_elements + old_size + 1;
      ((struct lArray*)A)->end_of_storage = new_elements + new_size;
    }
  }

  return x;
}

void* array_erase(void* A, lArrayIter pos)
{
  void* erase_data;

  assert(NULL != A && NULL != pos);
  erase_data = (pos == array_end(A) ? *(pos - 1) : *pos);
  if (pos + 1 < array_end(A))
    memmove(pos, pos + 1, (((struct lArray*)A)->end - (pos + 1)) * sizeof(void*));
  --((struct lArray*)A)->end;
  *((struct lArray*)A)->end = NULL;

  return erase_data;
}

void* array_remove(void* A, int i)
{
  void* remove_data;
  assert(NULL != A && i >= 0 && i < array_size(A));
  
  remove_data = ((struct lArray*)A)->elements[i];
  memmove(((struct lArray*)A)->begin + i, ((struct lArray*)A)->begin + i + 1, 
      (array_size(A) - (i + 1)) * sizeof(void*));
  --((struct lArray*)A)->end;
  *((struct lArray*)A)->end = NULL;

  return remove_data;
}

void* array_front(void* A)
{
  lArrayIter beg = array_begin(A);
  return (NULL != beg ? *beg : NULL);
}

void* array_back(void* A)
{
  lArrayIter end = array_end(A);
  return (NULL != end ? *(end - 1) : NULL);
}

lArrayIter array_begin(void* A)
{
  return (NULL != A ? (lArrayIter)(((struct lArray*)A)->begin) : NULL);
}

lArrayIter array_end(void* A)
{
  return (NULL != A ? (lArrayIter)(((struct lArray*)A)->end) : NULL);
}

lArrayIter array_iter_next(lArrayIter iter)
{
  return (NULL != iter ? ++iter : NULL);
}

void array_for_each(void* A, void (*visit)(void*, void*), void* arg)
{
  lArrayIter beg = array_begin(A), end = array_end(A);

  if (NULL == A || NULL == visit || NULL == beg)
    return;
  for ( ; beg != end; ++beg)
    visit(*beg, arg);
}

void* array_copy(void* A, int copy_len)
{
  void* copy_A;
  int   src_size, dest_size;

  assert(NULL != A && copy_len >= 0);
  copy_A      = array_create(copy_len);
  src_size    = array_size(A);
  dest_size   = array_size(copy_A);
  if (dest_size >= src_size && src_size > 0)
    memcpy(((struct lArray*)copy_A)->elements, ((struct lArray*)A)->elements, src_size * sizeof(void*));
  else if (src_size > dest_size && dest_size > 0)
    memcpy(((struct lArray*)copy_A)->elements, ((struct lArray*)A)->elements, dest_size * sizeof(void*));

  return copy_A;
}

void array_resize(void* A, int storage)
{
  assert(NULL != A && storage >= 0);
  if (0 == storage)
    FREE(((struct lArray*)A)->elements);
  else if (0 == array_size(A))
    ((struct lArray*)A)->elements = CALLOC(storage, sizeof(void*));
  else
  {
    int n = array_size(A);
    ((struct lArray*)A)->elements = REALLOC(((struct lArray*)A)->elements, storage * sizeof(void*));
    memset(((struct lArray*)A)->elements + n, 0, (storage - n) * sizeof(void*));
  }
  ((struct lArray*)A)->begin          = ((struct lArray*)A)->elements;
  ((struct lArray*)A)->end            = ((struct lArray*)A)->elements + storage;
  ((struct lArray*)A)->end_of_storage = ((struct lArray*)A)->elements + storage;
}
