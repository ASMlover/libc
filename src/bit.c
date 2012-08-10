#include <stdarg.h>
#include <string.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/bit.h"



struct lBit {
  unsigned char* bytes;
  unsigned long* dwords;
  int size;
};

#define BITS_PER_DWORD      (8 * sizeof(unsigned long))
#define NUM_OF_DWORDS(len)  ((((len) + BITS_PER_DWORD - 1) & (~(BITS_PER_DWORD - 1))) / BITS_PER_DWORD)
#define NUM_OF_BYTES(len)   ((((len) + 8 - 1) & (~(8 - 1))) / 8)

static unsigned char msbmask[] = {
  0xFF, 0xFE, 0xFC, 0xF8, 
  0xF0, 0xE0, 0xC0, 0x80
};
static unsigned char lsbmask[] = {
  0x01, 0x03, 0x07, 0x0F, 
  0x1F, 0x3F, 0x7F, 0xFF
};



static struct lBit* bit_copy(struct lBit* B)
{
  struct lBit* copy_B;

  assert(NULL != B);
  copy_B = bit_create(B->size);
  if (B->size > 0)
    memcpy(copy_B->bytes, B->bytes, NUM_OF_BYTES(B->size));
  return copy_B;
}




void* bit_create(int size)
{
  struct lBit* object;

  assert(size >= 0);
  NEW0(object);
  if (size > 0)
    object->dwords = CALLOC(NUM_OF_DWORDS(size), sizeof(unsigned long));
  else
    object->dwords = NULL;
  object->bytes = (unsigned char*)object->dwords;
  object->size  = size;

  return object;
}

void bit_release(void** B)
{
  assert(NULL != *B);
  FREE(((struct lBit*)*B)->dwords);
  FREE(*B);
}

int bit_size(void* B)
{
  return (NULL != B ? ((struct lBit*)B)->size : ERROR_LEN);
}

int bit_count(void* P)
{
  int count = 0, bits;
  struct lBit* B = (struct lBit*)P;
  static char count_list[] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
  };

  if (NULL != B) 
  {
    for (bits = NUM_OF_BYTES(B->size); --bits >= 0; )
    {
      unsigned char c = B->bytes[bits];
      count += count_list[c & 0xF] + count_list[c >> 4];
    }
    return count;
  }

  return 0;
}

void bit_clear(void* B)
{
  bit_clear_range(B, 0, bit_size(B) - 1);
}

int bit_set(void* P, int i, int val)
{
  int old_bit;
  struct lBit* B = (struct lBit*)P;

  assert(NULL != B && (0 == i || 1 == i) && 0 <= i && i < B->size);
  old_bit = ((B->bytes[i / 8] >> (i % 8)) & 1);
  if (1 == val)
    B->bytes[i / 8] |= (1 << (i % 8));
  else
    B->bytes[i / 8] &= ~(1 << (i % 8));

  return old_bit;
}

int bit_get(void* P, int i)
{
  struct lBit* B = (struct lBit*)P;
  assert(NULL != B && 0 <= i && i < B->size);
  return ((B->bytes[i / 8] >> (i % 8)) & 1);
}

void bit_clear_range(void* P, int beg, int end)
{
  struct lBit* B = (struct lBit*)P;

  assert(NULL != B && 0 <= beg && end < B->size && beg <= end);
  if (beg / 8 < end / 8)
  {
    int i;
    B->bytes[beg / 8] &= ~msbmask[beg % 8];
    for (i = beg / 8 + 1; i < end / 8; ++i)
      B->bytes[i] = 0;
    B->bytes[end / 8] &= ~lsbmask[end % 8];
  }
  else 
    B->bytes[beg / 8] &= ~(msbmask[beg % 8] & lsbmask[end % 8]);
}

void bit_set_range(void* P, int beg, int end)
{
  struct lBit* B = (struct lBit*)P;

  assert(NULL != B && 0 <= beg && end < B->size && beg <= end);
  if (beg / 8 < end / 8) 
  {
    int i;
    B->bytes[beg / 8] |= msbmask[beg % 8];
    for (i = beg / 8 + 1; i < end / 8; ++i)
      B->bytes[i] = 0xFF;
    B->bytes[end / 8] |= lsbmask[end % 8];
  }
  else
    B->bytes[beg / 8] |= (msbmask[beg % 8] & lsbmask[end % 8]);
}

void bit_not_range(void* P, int beg, int end)
{
  struct lBit* B = (struct lBit*)P;

  assert(NULL != B && 0 <= beg && end < B->size && beg <= end);
  if (beg / 8 < end / 8)
  {
    int i;
    B->bytes[beg / 8] ^= msbmask[beg % 8];
    for (i = beg / 8 + 1; i < end / 8; ++i)
      B->bytes[i] ^= 0xFF;
    B->bytes[end / 8] ^= lsbmask[end % 8];
  }
  else
    B->bytes[beg / 8] ^= (msbmask[beg % 8] & lsbmask[end % 8]);
}

int bit_lt(void* P1, void* P2)
{
  int i, ret = 0;
  struct lBit* B1 = (struct lBit*)P1;
  struct lBit* B2 = (struct lBit*)P2;

  assert(NULL != B1 && NULL != B2 && B1->size == B2->size);
  for (i = NUM_OF_DWORDS(B1->size); --i >= 0; )
  {
    if (0 != (B1->dwords[i] & ~B2->dwords[i]))
      return 0;
    else if (B1->dwords[i] != B2->dwords[i])
      ret |= 1;
  }

  return ret;
}

int bit_eq(void* P1, void* P2)
{
  int i;
  struct lBit* B1 = (struct lBit*)P1;
  struct lBit* B2 = (struct lBit*)P2;

  assert(NULL != B1 && NULL != B2 && B1->size == B2->size);
  for (i = NUM_OF_DWORDS(B1->size); --i >= 0; )
  {
    if (B1->dwords[i] != B2->dwords[i])
      return 0;
  }

  return 1;
}

int bit_leq(void* P1, void* P2)
{
  int i;
  struct lBit* B1 = (struct lBit*)P1;
  struct lBit* B2 = (struct lBit*)P2;

  assert(NULL != B1 && NULL != B2 && B1->size == B2->size);
  for (i = NUM_OF_DWORDS(B1->size); --i >= 0; )
  {
    if (0 != (B1->dwords[i] & ~B2->dwords[i]))
      return 0;
  }

  return 1;
}

void bit_for_each(void* P, void (*visit)(int, int, void*), void* arg)
{
  int i;
  struct lBit* B = (struct lBit*)P;

  if (NULL == B || NULL == visit)
    return;
  for (i = 0; i < B->size; ++i)
    visit(i, ((B->bytes[i / 8] >> (i % 8)) & 1), arg);
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
