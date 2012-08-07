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
  va_list ap;
  void* R = ring_create();

  va_start(ap, x);
  for ( ; NULL != x; x = va_arg(ap, void*))
    ring_push_back(R, x);
  va_end(ap);

  return R;
}

void ring_release(void** R)
{
  ring_clear(*R);
  FREE(*R);
}

int ring_size(void* R)
{
  return (NULL != R ? ((struct lRing*)R)->size : ERROR_LEN);
}

int ring_empty(void* R)
{
  return (NULL != R ? (NULL == ((struct lRing*)R)->head) : 0);
}

void ring_clear(void* P)
{
  struct lRing* R = (struct lRing*)P;
  struct lRingNode* node;

  if (NULL == R || NULL == R->head)
    return;
  while (R->size-- > 0)
  {
    node = R->head;
    R->head = R->head->next;
    FREE(node);
  }
  R->head = NULL;
  R->size = 0;
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

    node->prev = iter->prev;
    node->next = iter;
    iter->prev->next = node;
    iter->prev = node;
    ++R->size;
  }

  return x;
}

void* ring_erase(void* P, int i)
{
  struct lRing* R = (struct lRing*)P;
  int idx;
  struct lRingNode* node;
  void* erase_data;

  if (NULL == R || i < 0 || i >= R->size)
    return NULL;
  node = R->head;
  if (i <= R->size / 2)
  {
    for (idx = i; idx > 0; --idx)
      node = node->next;
  }
  else 
  {
    for (idx = R->size - i; idx > 0; --idx)
      node = node->prev;
  }
  if (0 == i)
    R->head = R->head->next;

  erase_data = node->data;
  node->prev->next = node->next;
  node->next->prev = node->prev;
  FREE(node);

  if (0 == --R->size)
    R->head = NULL;

  return erase_data;
}

void* ring_get(void* P, int i)
{
  struct lRingNode* iter;
  struct lRing* R = (struct lRing*)P;
  int idx;

  if (NULL == R || i < 0 || i >= R->size)
    return NULL;
  iter = R->head;
  if (i <= R->size / 2)
  {
    for (idx = i; idx > 0; --idx)
      iter = iter->next;
  }
  else
  {
    for (idx = R->size - i; idx > 0; --idx)
      iter = iter->prev;
  }

  return iter->data;
}

void* ring_set(void* P, int i, void* x)
{
  int idx;
  void* old_data;
  struct lRingNode* iter;
  struct lRing* R = (struct lRing*)P;

  if (NULL == R || i < 0 || i >= R->size)
    return NULL;
  iter = R->head;
  if (i <= R->size / 2)
  {
    for (idx = i; idx > 0; --idx)
      iter = iter->next;
  }
  else
  {
    for (idx = R->size - i; idx > 0; --idx)
      iter = iter->prev;
  }
  old_data = iter->data;
  iter->data = x;

  return old_data;
}

void* ring_front(void* P)
{
  struct lRing* R = (struct lRing*)P;
  return (NULL != R && NULL != R->head ? R->head->data : NULL);
}

void* ring_back(void* P)
{
  struct lRing* R = (struct lRing*)P;
  return (NULL != R && NULL != R->head ? R->head->prev->data : NULL);
}

void ring_for_each(void* P, void (*visit)(void*, void*), void* arg)
{
  struct lRingNode* iter;
  struct lRing* R = (struct lRing*)P;

  if (NULL == R || NULL == visit)
    return;
  else
  {
    int i;
    for (iter = R->head, i = 0; NULL != iter && i < R->size; ++i, iter = iter->next)
      visit(iter->data, arg);
  }
}

void ring_rotate(void* P, int n)
{
  int idx, pos;
  struct lRingNode* iter;
  struct lRing* R = (struct lRing*)P;

  if (NULL == R || n < -R->size || n > R->size)
    return;
  pos = (n >= 0 ? n % R->size : n + R->size);

  iter = R->head;
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
  R->head = iter;
}
