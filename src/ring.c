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
  struct lRingNode* head;
  int               size;
};



static struct lRingNode* ring_new_node(void* x)
{
  struct lRingNode* node;
  NEW0(node);

  if (NULL != node)
    node->data = x;
  return node;
}

static void* 
ring_erase_internal(struct lRing* R, struct lRingNode* pos)
{
  struct lRingNode* prev = pos->prev;
  struct lRingNode* next = pos->next;
  void*  erase_data;

  prev->next = next;
  next->prev = prev;
  erase_data = pos->data;
  FREE(pos);
  if (0 == --R->size)
    R->head = NULL;

  return erase_data;
}





void* ring_create(void)
{
  struct lRing* object;
  NEW0(object);

  return object;
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

void* ring_push_front(void* P, void* x)
{
  struct lRing* R = (struct lRing*)P;
  if (NULL == ring_push_back(P, x))
    return NULL;

  R->head = R->head->prev;
  return x;
}

void* ring_push_back(void* P, void* x)
{
  struct lRing*     R    = (struct lRing*)P;
  struct lRingNode* node = ring_new_node(x);

  if (NULL == R || NULL == node)
    return NULL;

  if (NULL == R->head)
    R->head = node->prev = node->next = node;
  else
  {
    node->prev = R->head->prev;
    node->next = R->head;
    R->head->prev->next = node;
    R->head->prev = node;
  }
  ++R->size;

  return x;
}

void* ring_pop_front(void* P)
{
  struct lRing* R = (struct lRing*)P;

  if (NULL != R && NULL != R->head)
  {
    struct lRingNode* pos = R->head;
    R->head = R->head->next;
    return ring_erase_internal(R, pos);
  }
  else
    return NULL;
}

void* ring_pop_back(void* P)
{
  struct lRing* R = (struct lRing*)P;

  if (NULL != R && NULL != R->head)
  {
    struct lRingNode* pos = R->head->prev;
    return ring_erase_internal(R, pos);
  }
  else
    return NULL;
}

void* ring_insert(void* P, int i, void* x)
{
  /** TODO: */
  struct lRing* R = (struct lRing*)P;
  assert(NULL != R && i >= -R->size && i <= R->size);

  if (0 == i || i == -R->size)
    return ring_push_front(R, x);
  else if (-1 == i || i == R->size)
    return ring_push_back(R, x);
  else
  {
    struct lRingNode* node = ring_new_node(x);
    struct lRingNode* iter = R->head;
    int pos = (i < 0 ? i + R->size : i);
    int idx;

    if (pos <= R->size / 2)
    {
      for (idx = pos; idx > 0; --idx)
        iter = iter->next;
    }
    else
    {
      for (idx = R->size - pos; idx > 0; --idx)
        iter = iter->prev;
    }
  }

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
