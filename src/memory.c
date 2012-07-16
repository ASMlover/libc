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
#include <stddef.h>
#include "../inc/assert.h"

#include "../inc/memory.h"



const struct lExcept lmemory_failed = { "Allocation Failed" };

void* memory_alloc(long bytes, const char* file, int line)
{
  void* ptr;

  assert(bytes > 0L);
  ptr = malloc(bytes);
  if (NULL == ptr)
  {
    if (NULL == file)
      RAISE(lmemory_failed);
    else
      except_raise(&lmemory_failed, file, line);
  }

  return ptr;
}

void* memory_calloc(long count, long elem_bytes, const char* file, int line)
{
  void* ptr;

  assert(count > 0L && elem_bytes > 0L);
  ptr = calloc(count, elem_bytes);
  if (NULL == ptr)
  {
    if (NULL == file)
      RAISE(lmemory_failed);
    else
      except_raise(&lmemory_failed, file, line);
  }

  return ptr;
}

void memory_free(void* ptr, const char* file, int line)
{
  if (NULL != ptr)
    free(ptr);
}

void* memory_realloc(void* ptr, long bytes, const char* file, int line)
{
  assert(NULL != ptr && bytes > 0);
  ptr = realloc(ptr, bytes);
  if (NULL == ptr)
  {
    if (NULL == file)
      RAISE(lmemory_failed);
    else
      except_raise(&lmemory_failed, file, line);
  }

  return ptr;
}
