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
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/list.h"


struct lListNode {
  void*             data;
  struct lListNode* prev;
  struct lListNode* next;
};

struct lList {
  struct lListNode node;
  int              size;
};


static inline struct lListNode* list_new_node(void* x)
{
  struct lListNode* node;
  NEW0(node);

  if (NULL != node)
    node->data = x;
  return node;
}



void* list_create(void)
{
  struct lList* self;

  NEW0(self);
  if (NULL != self)
  {
    self->node.prev = &self->node;
    self->node.next = &self->node;
  }

  return (void*)self;
}

void list_release(void** L)
{
  list_clear(*L, NULL);
  FREE(*L);
}

int list_size(void* L)
{
  return (NULL != L ? ((struct lList*)L)->size : ERROR_LEN);
}

int list_empty(void* L)
{
  return (list_begin(L) == list_end(L));
}

void list_clear(void* L, void (*destroy)(void*))
{
  lListIter it = list_begin(L);
  lListIter node;
  void*     data;

  if (NULL == L || NULL == it)
    return;
  while (it != list_end(L))
  {
    node = it;
    it   = list_iter_next(it);
    data = list_erase(L, node);
    if (NULL != destroy)
      destroy(data);
  }
  ((struct lList*)L)->size = 0;
}

int list_push_back(void* L, void* x)
{
  return list_insert(L, list_end(L), x);
}

int list_push_front(void* L, void* x)
{
  return list_insert(L, list_begin(L), x);
}

int list_insert(void* L, lListIter pos, void* x)
{
  struct lListNode* node = list_new_node(x);

  if (NULL == L || NULL == pos || NULL == node)
    return RESULT_FAIL;
  node->prev = ((struct lListNode*)pos)->prev;
  node->next = ((struct lListNode*)pos);
  ((struct lListNode*)pos)->prev->next = node;
  ((struct lListNode*)pos)->prev = node;
  ++((struct lList*)L)->size;

  return RESULT_OK;
}

void* list_pop_back(void* L)
{
  struct lListNode* node = (struct lListNode*)list_end(L);
  if (NULL != node)
    node = node->prev;
  return list_erase(L, (lListIter)node);
}

void* list_pop_front(void* L)
{
  return list_erase(L, list_begin(L));
}

void* list_erase(void* L, lListIter pos)
{
  struct lListNode* prev;
  struct lListNode* next;
  void*  erase_data;

  if (NULL == L || NULL == pos)
    return NULL;
  prev = ((struct lListNode*)pos)->prev;
  next = ((struct lListNode*)pos)->next;
  prev->next = next;
  next->prev = prev;
  erase_data = ((struct lListNode*)pos)->data;
  FREE(pos);
  --((struct lList*)L)->size;

  return erase_data;
}

lListIter list_begin(void* L)
{
  return (NULL != L ? (lListIter)(((struct lList*)L)->node.next) : NULL);
}

lListIter list_end(void* L)
{
  return (NULL != L ? (lListIter)(&((struct lList*)L)->node) : NULL);
}

lListIter list_iter_next(lListIter iter)
{
  return (NULL != iter ? (lListIter)(((struct lListNode*)iter)->next) : NULL);
}

void* list_front(void* L)
{
  struct lListNode* node = (struct lListNode*)list_begin(L);
  return (NULL != node ? node->data : NULL);
}

void* list_back(void* L)
{
  struct lListNode* node = (struct lListNode*)list_end(L);
  if (NULL != node)
    node = node->prev;
  return (NULL != node ? node->data : NULL);
}

void list_for_each(void* L, void (*visit)(void*, void*), void* arg)
{
  lListIter beg = list_begin(L);
  lListIter end = list_end(L);
  struct lListNode* node;

  if (NULL == L || NULL == beg)
    return;
  while (beg != end)
  {
    node = (struct lListNode*)beg;
    beg  = list_iter_next(beg);
    if (NULL != visit)
      visit(node->data, arg);
  }
}
