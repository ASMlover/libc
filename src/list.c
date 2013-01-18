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
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/list.h"


typedef struct list_node_s {
  element_t data;
  struct list_node_s* prev;
  struct list_node_s* next;
} *list_node_t;

struct list_s {
  int size;
  struct list_node_s node;
};


static inline 
list_node_t list_new_node(element_t x)
{
  list_node_t node;
  NEW0(node);

  if (NULL != node)
    node->data = x;
  return node;
}




list_t 
list_create(void)
{
  list_t self;
  NEW0(self);

  if (NULL != self) {
    self->node.prev = &self->node;
    self->node.next = &self->node;
  }

  return self;
}

void 
list_release(list_t* L)
{
  list_clear(*L, NULL);
  FREE(*L);
}

int 
list_size(list_t L)
{
  return (NULL != L ? L->size : ERROR_LEN);
}

int 
list_empty(list_t L)
{
  assert(NULL != L);
  return (L->node.next == &L->node);
}

void 
list_clear(list_t L, void (*destroy)(void*))
{
  list_node_t it, node;
  element_t   data;

  if (NULL == L)
    return;

  it = L->node.next;
  while (it != &L->node) {
    node = it;
    it   = it->next;
    data = list_erase(L, (list_iter_t)node);
    if (NULL != destroy)
      destroy(data);
  }
}

int 
list_push_back(list_t L, element_t x)
{
  return list_insert(L, list_end(L), x);
}

int 
list_push_front(list_t L, element_t x)
{
  return list_insert(L, list_begin(L), x);
}

int 
list_insert(list_t L, list_iter_t pos, element_t x)
{
  list_node_t node = list_new_node(x);

  if (NULL == L || NULL == pos || NULL == node)
    return RESULT_FAIL;
  node->prev = ((list_node_t)pos)->prev;
  node->next = ((list_node_t)pos);
  ((list_node_t)pos)->prev->next = node;
  ((list_node_t)pos)->prev = node;
  ++L->size;

  return RESULT_OK;
}

element_t 
list_pop_back(list_t L)
{
  list_node_t node = (list_node_t)list_end(L);
  if (NULL != node)
    node = node->prev;
  return list_erase(L, (list_iter_t)node);
}

element_t 
list_pop_front(list_t L)
{
  return list_erase(L, list_begin(L));
}

element_t 
list_erase(list_t L, list_iter_t pos)
{
  list_node_t prev, next;
  element_t erase_data;

  if (NULL == L || NULL == pos)
    return NULL;
  prev = ((list_node_t)pos)->prev;
  next = ((list_node_t)pos)->next;
  prev->next = next;
  next->prev = prev;
  erase_data = ((list_node_t)pos)->data;
  FREE(pos);
  --L->size;

  return erase_data;
}

list_iter_t 
list_begin(list_t L)
{
  return (NULL != L ? (list_iter_t)L->node.next : NULL);
}

list_iter_t 
list_end(list_t L)
{
  return (NULL != L ? (list_iter_t)&L->node : NULL);
}

list_iter_t 
list_iter_next(list_iter_t iter)
{
  return (NULL != iter ? (list_iter_t)((list_node_t)iter)->next : NULL);
}

element_t 
list_front(list_t L)
{
  list_node_t node = (list_node_t)list_begin(L);
  return (NULL != node ? node->data : NULL);
}

element_t 
list_back(list_t L)
{
  list_node_t node = (list_node_t)list_end(L);
  if (NULL != node)
    node = node->prev;
  return (NULL != node ? node->data : NULL);
}

void 
list_for_each(list_t L, void (*visit)(element_t, void*), void* arg)
{
  list_node_t beg, end, node;

  if (NULL == L)
    return;
  beg = L->node.next;
  end = &L->node;
  while (beg != end)
  {
    node = beg;
    beg  = beg->next;
    if (NULL != visit)
      visit(node->data, arg);
  }
}
