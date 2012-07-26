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
#include "../inc/memory.h"

#include "../inc/slist.h"


struct lSlistNode {
  void*              data;
  struct lSlistNode* next;
};

struct lSlist {
  struct lSlistNode* head;
  struct lSlistNode* tail;
  int                size;
};


static inline struct lSlistNode* slist_new_node(void* x)
{
  struct lSlistNode* node;
  NEW0(node);

  if (NULL != node)
    node->data = x;
  return node;
}



void* slist_create(void)
{
  struct lSlist* self;
  NEW0(self);

  return self;
}

void slist_release(void** L)
{
  slist_clear(*L, NULL);
  FREE(*L);
}

int slist_size(void* L)
{
  return (NULL != L ? ((struct lSlist*)L)->size : ERROR_LEN);
}

int slist_empty(void* L)
{
  return (NULL != L ? NULL == ((struct lSlist*)L)->head : 0);
}

void slist_clear(void* L, void (*destroy)(void*))
{
  struct lSlistNode* node;
  
  if (NULL == L)
    return;
  while (NULL != ((struct lSlist*)L)->head)
  {
    node = ((struct lSlist*)L)->head;
    ((struct lSlist*)L)->head = ((struct lSlist*)L)->head->next;
    if (NULL != destroy)
      destroy(node->data);
  }
  ((struct lSlist*)L)->tail = NULL;
  ((struct lSlist*)L)->size = 0;
}

int slist_push_back(void* L, void* x)
{
  struct lSlistNode* node = slist_new_node(x);

  if (NULL == L || NULL == node)
    return RESULT_FAIL;
  if (NULL == ((struct lSlist*)L)->head || NULL == ((struct lSlist*)L)->tail)
    ((struct lSlist*)L)->head = ((struct lSlist*)L)->tail = node;
  else 
  {
    ((struct lSlist*)L)->tail->next = node;
    ((struct lSlist*)L)->tail       = node;
  }
  ++((struct lSlist*)L)->size;

  return RESULT_OK;
}

int slist_push_front(void* L, void* x)
{
  struct lSlistNode* node = slist_new_node(x);

  if (NULL == L || NULL == node)
    return RESULT_FAIL;
  node->next = ((struct lSlist*)L)->head;
  ((struct lSlist*)L)->head = node;
  ++((struct lSlist*)L)->size;

  return RESULT_OK;
}

void* slist_pop_front(void* L)
{
  struct lSlistNode* node;

  if (NULL == L)
    return NULL;
  if (NULL != ((struct lSlist*)L)->head)
  {
    void* pop_data;

    node = ((struct lSlist*)L)->head;
    ((struct lSlist*)L)->head = ((struct lSlist*)L)->head->next;
    pop_data = node->data;
    FREE(node);
    if (NULL == ((struct lSlist*)L)->head)
      ((struct lSlist*)L)->tail = NULL;
    --((struct lSlist*)L)->size;

    return pop_data;
  }

  return NULL;
}

lSlistIter slist_begin(void* L)
{
  return (NULL != L ? (lSlistIter)(((struct lSlist*)L)->head) : NULL);
}

lSlistIter slist_end(void* L)
{
  return (NULL);
}

lSlistIter slist_iter_next(lSlistIter iter)
{
  return (NULL != iter ? (lSlistIter)(((struct lSlistNode*)iter)->next) : NULL);
}

void* slist_front(void* L)
{
  struct lSlistNode* node;

  if (NULL == L)
    return NULL;
  node = ((struct lSlist*)L)->head;
  return (NULL != node ? node->data : NULL);
}

void* slist_back(void* L)
{
  struct lSlistNode* node;

  if (NULL == L)
    return NULL;
  node = ((struct lSlist*)L)->tail;
  return (NULL != node ? node->data : NULL);
}

void slist_for_each(void* L, void (*visit)(void*, void*), void* arg)
{
  struct lSlistNode* node;

  if (NULL == L)
    return;
  node = ((struct lSlist*)L)->head;
  while (NULL != node)
  {
    if (NULL != visit)
      visit(node->data, arg);
    node = node->next;
  }
}
