#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "../assert.h"

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
