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
#include "../inc/arena.h"


#define LTHRESHOLD    (10)
const struct lExcept larena_createfailed = { "Arena creation failed" };
const struct lExcept larena_failed       = { "Arena allocation failed" };


struct lArena {
  struct lArena* prev;
  char* avail_beg;
  char* avail_end;
};

union lAlign {
#ifdef MAXALIGN
  char pad[MAXALIGN];
#else
  int     intValue;
  long    longValue;
  long*   longPtr;
  void*   ptr;
  void    (*funcPtr)(void);
  float   floatValue;
  double  doubleValue;
  long double longDoubleValue;
#endif
};

union lHeader {
  struct lArena arena;
  union lAlign  align;
};


static struct lArena* lfreechunks;
static int            lfreecounts;


int arena_create(void)
{
  struct lArena* object;
  size_t size = sizeof(struct lArena);

  object = (struct lArena*)malloc(size);
  if (NULL == object)
    RAISE(larena_createfailed);
  object->prev = NULL;
  object->avail_beg = object->avail_end = NULL;

  return (int)object;
}

void arena_release(int* arena)
{
  if (0 != *arena)
  {
    arena_free(*arena);
    free((void*)*arena);
    *arena = 0;
  }
}


void* arena_alloc(int arena, long bytes, const char* file, int line)
{
  assert(0 != arena && bytes > 0L);

  bytes = ((bytes + sizeof(union lAlign) - 1) / (sizeof(union lAlign))) * sizeof(union lAlign);
  while (bytes > ((struct lArena*)arena)->avail_end - ((struct lArena*)arena)->avail_beg)
  {
    struct lArena* ptr;
    char*          limit;

    if (NULL != (ptr = lfreechunks))
    {
      lfreechunks = lfreechunks->prev;
      --lfreecounts;
      limit = ptr->avail_end;
    }
    else 
    {
      long size = sizeof(union lHeader) + bytes + 10 * 1024;
      ptr = (struct lArena*)malloc(size);
      if (NULL == ptr)
      {
        if (NULL == file)
          RAISE(larena_failed);
        else
          except_raise(&larena_failed, file, line);
      }
      limit = (char*)ptr + size;
    }
    *ptr = *((struct lArena*)arena);
    ((struct lArena*)arena)->avail_beg = (char*)((union lHeader*)ptr + 1);
    ((struct lArena*)arena)->avail_end = limit;
    ((struct lArena*)arena)->prev      = ptr;
  }
  ((struct lArena*)arena)->avail_beg += bytes;

  return (((struct lArena*)arena)->avail_beg - bytes);
}

void* arena_calloc(int arena, long count, long elem_bytes, const char* file, int line)
{
  void* ptr;

  assert(count > 0L && elem_bytes > 0L);
  ptr = arena_alloc(arena, count * elem_bytes, file, line);
  memset(ptr, 0, count * elem_bytes);
  
  return ptr;
}

void arena_free(int arena)
{
  assert(0 != arena);
  while (NULL != ((struct lArena*)arena)->prev)
  {
    struct lArena tmp = *((struct lArena*)arena)->prev;
    if (lfreecounts < LTHRESHOLD)
    {
      ((struct lArena*)arena)->prev->prev = lfreechunks;
      lfreechunks = ((struct lArena*)arena)->prev;
      ++lfreecounts;
      lfreechunks->avail_end = ((struct lArena*)arena)->avail_end;
    }
    else 
      free(((struct lArena*)arena)->prev);
    *(struct lArena*)arena = tmp;
  }

  assert(NULL == ((struct lArena*)arena)->avail_beg);
  assert(NULL == ((struct lArena*)arena)->avail_end);
}
