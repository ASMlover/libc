#include <stdarg.h>
#include <string.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/bit.h"




void* bit_create(int size)
{
  return NULL;
}

void bit_release(void** B)
{
}

int bit_size(void* B)
{
  return ERROR_LEN;
}

int bit_count(void* B)
{
  return 0;
}

void bit_clear(void* B)
{
}

int bit_set(void* B, int i, int val)
{
  return val;
}

int bit_get(void* B, int i)
{
  return 0;
}

void bit_clear_range(void* B, int beg, int end)
{
}

void bit_set_range(void* B, int beg, int end)
{
}

void bit_not_range(void* B, int beg, int end)
{
}

int bit_lt(void* B1, void* B2)
{
  return 0;
}

int bit_eq(void* B1, void* B2)
{
  return 0;
}

int bit_leq(void* B1, void* B2)
{
  return 0;
}

void bit_for_each(void* B, void (*visit)(int, int, void*), void* arg)
{
}

void* bit_union(void* B1, void* B2)
{
  return NULL;
}

void* bit_inter(void* B1, void* B2)
{
  return NULL;
}

void* bit_minus(void* B1, void* B2)
{
  return NULL;
}

void* bit_diff(void* B1, void* B2)
{
  return NULL;
}
