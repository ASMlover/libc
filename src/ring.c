#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/ring.h"


struct lRingNode {
  void* data;
  struct lRingNode* prev;
  struct lRingNode* next;
};
struct lRing {
  struct lRingNode node;
  int              size;
};



void* ring_create(void)
{
  return NULL;
}

void* ring_create_by(void* x, ...)
{
  return NULL;
}

void ring_release(void** R)
{
}

int ring_size(void* R)
{
  return ERROR_LEN;
}

int ring_empty(void* R)
{
  return 0;
}

void ring_clear(void* R)
{
}

void* ring_push_front(void* R, void* x)
{
  return x;
}

void* ring_push_back(void* R, void* x)
{
  return x;
}

void* ring_pop_front(void* R)
{
  return NULL;
}

void* ring_pop_back(void* R)
{
  return NULL;
}

void* ring_insert(void* R, int i, void* x)
{
  return x;
}

void* ring_erase(void* R, int i)
{
  return NULL;
}

void* ring_get(void* R, int i)
{
  return NULL;
}

void* ring_set(void* R, int i, void* x)
{
  return NULL;
}

void ring_for_each(void* R, void (*visit)(void*, void*), void* arg)
{
}

void ring_rotate(void* R, int n)
{
}
