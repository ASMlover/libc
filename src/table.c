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
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/table.h"


struct lTableNode {
  const void*        key;
  void*              value;
  struct lTableNode* prev;
  struct lTableNode* next;
};

struct lTable {
  int (*compare)(const void* x, const void* y);
  unsigned int (*hash_value)(const void* key);
  int storage;
  int size;
  unsigned int timestamp;
  struct lTableNode   node;
  struct lTableNode** tables;
};



static int compare_def(const void* x, const void* y)
{
  return (x != y ? (x > y ? 1 : -1) : 0);
}

static unsigned int hash_value_def(const void* key)
{
  unsigned int hash = 1315423911;

  hash ^= ((hash << 5) + (unsigned int)key + (hash >> 2));
  return (hash & 0xFFFFFFF);
}

/*
static unsigned int get_hash_value(const char* key)
{
  unsigned int hash = 1315423911;

  while ('\0' != *key)
    hash ^= ((hash << 5) + *key++ + (hash >> 2));

  return (hash & 0x7FFFFFFF);
}
*/




static void table_erase(struct lTable* T, struct lTableNode* pos)
{
  struct lTableNode* prev = pos->prev;
  struct lTableNode* next = pos->next;
  prev->next = next;
  next->prev = prev;
  FREE(pos);
  --T->size;
}



void* table_create(int count, 
    int (*compare)(const void*, const void*), 
    unsigned int (*hash_value)(const void*))
{
  struct lTable* object;
  int i;
  static int primes[] = {509, 509, 1021, 2053, 4093, 8191, 16381, 32771, 65521, INT_MAX};

  for (i = 1; primes[i] < count; ++i)
  {}
  object = CALLOC(1, sizeof(*object) + primes[i - 1] * sizeof(struct lTableNode*));
  if (NULL != object)
  {
    object->storage    = primes[i - 1];
    object->compare    = (NULL != compare ? compare : compare_def);
    object->hash_value = (NULL != hash_value ? hash_value : hash_value_def);
    object->tables     = (struct lTableNode**)(object + 1);
    object->node.prev  = &object->node;
    object->node.next  = &object->node;
  }

  return object;
}

void table_release(void** T)
{
  table_clear(*T);
  FREE(*T);
}

int table_size(void* T)
{
  return (NULL != T ? ((struct lTable*)T)->size : ERROR_LEN);
}

int table_empty(void* T)
{
  return (table_begin(T) == table_end(T));
}

void table_clear(void* T)
{
  lTableIter beg = table_begin(T);
  lTableIter end = table_end(T);
  struct lTableNode* node;

  if (NULL == T || NULL == beg)
    return;
  if (((struct lTable*)T)->size > 0)
  {
    /* int i; */
    while (beg != end)
    {
      node = (struct lTableNode*)beg;
      beg  = table_iter_next(beg);
      table_remove(T, node->key);
      /*
      i = ((struct lTable*)T)->hash_value(node->key) % ((struct lTable*)T)->storage;
      table_erase((struct lTable*)T, node);
      ((struct lTable*)T)->tables[i] = NULL;
      */
    }
    ((struct lTable*)T)->size = 0;
  }
}


int table_insert(void* T, const void* key, void* x)
{
  int i;
  struct lTableNode* node;

  if (NULL == T)
    return RESULT_FAIL;
  
  i = ((struct lTable*)T)->hash_value(key) % ((struct lTable*)T)->storage;
  node = ((struct lTable*)T)->tables[i];
  if (NULL == node || 0 != ((struct lTable*)T)->compare(key, node->key))
  {
    struct lTableNode* pos = &((struct lTable*)T)->node;
    NEW0(node);
    node->key   = key;
    node->prev  = pos->prev;
    node->next  = pos;
    pos->prev->next = node;
    pos->prev   = node;
    ((struct lTable*)T)->tables[i] = node;
    ++((struct lTable*)T)->size;
  }
  node->value = x;
  ++((struct lTable*)T)->timestamp;

  return RESULT_OK;
}

void* table_remove(void* T, const void* key)
{
  int i;
  struct lTableNode* node;

  if (NULL == T)
    return NULL;

  ++((struct lTable*)T)->timestamp;
  i = ((struct lTable*)T)->hash_value(key) % ((struct lTable*)T)->storage;
  node = ((struct lTable*)T)->tables[i];
  if (NULL != node && 0 == ((struct lTable*)T)->compare(key, node->key))
  {
    void*  remove_data      = node->value;
    struct lTableNode* prev = node->prev;
    struct lTableNode* next = node->next;
    prev->next = next;
    next->prev = prev;
    FREE(((struct lTable*)T)->tables[i]);
    --((struct lTable*)T)->size;

    return remove_data;
  }
  
  return NULL;
}

void* table_get(void* T, const void* key)
{
  int i;
  struct lTableNode* node;

  if (NULL == T)
    return NULL;
  i = ((struct lTable*)T)->hash_value(key) % ((struct lTable*)T)->storage;
  node = ((struct lTable*)T)->tables[i];

  return (NULL != node ? node->value : NULL);
}

lTableIter table_begin(void* T)
{
  return (NULL != T ? (lTableIter)(((struct lTable*)T)->node.next) : NULL);
}

lTableIter table_end(void* T)
{
  return (NULL != T ? (lTableIter)(&((struct lTable*)T)->node) : NULL);
}

lTableIter table_iter_next(lTableIter iter)
{
  return (NULL != iter ? (lTableIter)(((struct lTableNode*)iter)->next) : NULL);
}

const void* table_iter_key(lTableIter iter)
{
  return (NULL != iter ? ((struct lTableNode*)iter)->key : NULL);
}

void* table_iter_value(lTableIter iter)
{
  return (NULL != iter ? ((struct lTableNode*)iter)->value : NULL);
}

void table_for_each(void* T, void (*visit)(const void*, void*, void*), void* arg)
{
  unsigned int stamp;
  lTableIter beg = table_begin(T);
  lTableIter end = table_end(T);

  if (NULL == T || NULL == beg)
    return;
  stamp = ((struct lTable*)T)->timestamp;
  for ( ; beg != end; beg = table_iter_next(beg))
  {
    visit(((struct lTableNode*)beg)->key, ((struct lTableNode*)beg)->value, arg);
    assert(stamp == ((struct lTable*)T)->timestamp);
  }
}
