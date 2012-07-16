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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/assert.h"
#include "../inc/mem_check.h"


union lAlign {
#ifdef MAXALIGN
  char    pad[MAXALIGN];
#else
  int     intValue;
  long    longValue;
  long*   longPtr;
  void*   ptr;
  void*   (*funcPtr)(void);
  float   floatValue;
  double  doubleValue;
  long double longDoubleValue;
#endif
};


#define LHASHTABLE_LEN_DEF  (2048)
#define LHASH(p, t)         (((unsigned long)(p) >> 3) & (sizeof(t) / sizeof((t)[0]) - 1))
#define LDESCRIPTORS        (512)
#define LNALLOC             ((4096 + sizeof(union lAlign) - 1) / (sizeof(union lAlign))) * (sizeof(union lAlign))


const struct lExcept lmemcheck_failed = { "Memory check failed" };

struct lDescriptor {
  struct lDescriptor* free;
  struct lDescriptor* next;
  const void*         ptr;
  long                size;
  const char*         file;
  int                 line;
};
static struct lDescriptor* s_lhashtable[LHASHTABLE_LEN_DEF];
static struct lDescriptor lfreelist = {&lfreelist};


static struct lDescriptor* find(const void* ptr)
{
  struct lDescriptor* descriptorVal = s_lhashtable[LHASH(ptr, s_lhashtable)];
  while (NULL != descriptorVal && descriptorVal->ptr != ptr)
    descriptorVal = descriptorVal->next;
  return descriptorVal;
}

static struct lDescriptor* dalloc(void* ptr, long bytes, const char* file, int line)
{
  static struct lDescriptor* avail;
  static int left;

  if (left <= 0)
  {
    avail = (struct lDescriptor*)malloc(LDESCRIPTORS * sizeof(*avail));
    if (NULL == avail)
      return NULL;
    left = LDESCRIPTORS;
  }
  avail->ptr  = ptr;
  avail->size = bytes;
  avail->file = file;
  avail->line = line;
  avail->free = avail->next = NULL;
  --left;

  return avail++;
}


void* mem_alloc(long bytes, const char* file, int line)
{
  struct lDescriptor* descriptorVal;
  void*  ptr;

  assert(bytes > 0L);
  bytes = ((bytes + sizeof(union lAlign) - 1) / (sizeof(union lAlign))) * (sizeof(union lAlign));
  for (descriptorVal = lfreelist.free; NULL != descriptorVal; descriptorVal = descriptorVal->free)
  {
    if (descriptorVal->size > bytes)
    {
      descriptorVal->size -= bytes;
      ptr = (char*)descriptorVal->ptr + descriptorVal->size;
      if (NULL != (descriptorVal = dalloc(ptr, bytes, file, line)))
      {
        unsigned int hashVal = LHASH(ptr, s_lhashtable);
        descriptorVal->next = s_lhashtable[hashVal];
        s_lhashtable[hashVal] = descriptorVal;
        return ptr;
      }
      else
      {
        if (NULL == file)
          RAISE(lmemcheck_failed);
        else
          except_raise(&lmemcheck_failed, file, line);
      }
    }

    if (&lfreelist == descriptorVal)
    {
      struct lDescriptor* newPtr = NULL;
      if ((NULL == (ptr = malloc(bytes + LNALLOC))) 
        || (NULL == (newPtr = dalloc(ptr, bytes + LNALLOC, __FILE__, __LINE__))))
      {
        if (NULL == file)
          RAISE(lmemcheck_failed);
        else
          except_raise(&lmemcheck_failed, file, line);
      }
      newPtr->free = lfreelist.free;
      lfreelist.free = newPtr;
    }
  }

  assert(0);
  return NULL;
}

void* mem_calloc(long count, long elem_bytes, const char* file, int line)
{
  void* ptr;
  assert(count > 0L && elem_bytes > 0L);

  ptr = mem_alloc(count * elem_bytes, file, line);
  memset(ptr, 0, count * elem_bytes);

  return ptr;
}


void mem_free(void* ptr, const char* file, int line)
{
  if (NULL != ptr)
  {
    struct lDescriptor* descriptorVal = NULL;

    if (0 != (((unsigned long)ptr) % (sizeof(union lAlign))) 
      || NULL == (descriptorVal = find(ptr)) || NULL != descriptorVal->free)
      except_raise(&lassert_failed, file, line);

    descriptorVal->free = lfreelist.free;
    lfreelist.free = descriptorVal;
  }
}

void* mem_realloc(void* ptr, long bytes, const char* file, int line)
{
  struct lDescriptor* descriptorVal = NULL;
  void*  newPtr;

  assert(NULL != ptr && bytes > 0L);
  if (0 != (((unsigned long)ptr) % (sizeof(union lAlign))) 
    || NULL == (descriptorVal = find(ptr)) || NULL != descriptorVal->free)
    except_raise(&lassert_failed, file, line);

  newPtr = mem_alloc(bytes, file, line);
  memcpy(newPtr, ptr, bytes < descriptorVal->size ? bytes : descriptorVal->size);
  mem_free(ptr, file, line);

  return newPtr;
}
