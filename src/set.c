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
#include <limits.h>
#include <stddef.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"
#include "../inc/arith.h"

#include "../inc/set.h"


struct lSetNode {
  const void*      member;
  struct lSetNode* prev;
  struct lSetNode* next;
};
struct lSet {
  int (*compare)(const void*, const void*);
  unsigned int (*hash_value)(const void*);
  int storage;
  int size;
  unsigned int timestamp;
  struct lSetNode   node;
  struct lSetNode** sets;
};


static int compare_def(const void* x, const void* y)
{
  return (x != y ? (x > y ? 1 : -1) : 0);
}

static unsigned hash_value_def(const void* x)
{
  unsigned int hash = 1315423911;

  hash ^= ((hash << 5) + (unsigned int)x + (hash >> 2));
  return (hash & 0xFFFFFFF);
}

static struct lSet* set_copy(struct lSet* S, int count)
{
  struct lSet* copy_S;
  lSetIter beg, end;
    
  assert(NULL != S);
  end = set_end(S);
  copy_S = (struct lSet*)set_create(count, S->compare, S->hash_value);
  for (beg = set_begin(S); beg != end; beg = set_iter_next(beg))
    set_insert(copy_S, ((struct lSetNode*)beg)->member);

  return copy_S;
}




void* set_create(int count, 
    int (*compare)(const void*, const void*), 
    unsigned int (*hash_value)(const void*))
{
  struct lSet* object;
  int i;
  static int primes[] = {509, 509, 1021, 2053, 4093, 8191, 16381, 32771, 65521, INT_MAX};

  assert(count > 0);
  for (i = 1; primes[i] < count; ++i)
  {}
  object = CALLOC(1, sizeof(*object) + primes[i - 1] * sizeof(struct lSetNode*));
  if (NULL != object)
  {
    object->storage    = primes[i - 1];
    object->compare    = (NULL != compare ? compare : compare_def);
    object->hash_value = (NULL != hash_value ? hash_value : hash_value_def);
    object->sets       = (struct lSetNode**)(object + 1);
    object->node.prev  = &object->node;
    object->node.next  = &object->node;
  }

  return object;
}

void set_release(void** S)
{
  set_clear(*S);
  FREE(*S);
}

int set_size(void* S)
{
  return (NULL != S ? ((struct lSet*)S)->size : ERROR_LEN);
}

int set_empty(void* S)
{
  return (set_begin(S) == set_end(S));
}

void set_clear(void* S)
{
  lSetIter beg = set_begin(S), end = set_end(S);
  struct lSetNode* node;

  if (NULL == S || NULL == beg)
    return;
  if (((struct lSet*)S)->size > 0)
  {
    while (beg != end)
    {
      node = (struct lSetNode*)beg;
      beg  = set_iter_next(beg);
      set_remove(S, node->member);
    }
    ((struct lSet*)S)->size = 0;
  }
}

int set_find(void* S, const void* member)
{
  int i;
  struct lSetNode* node;

  if (NULL == S)
    return EXISTS_NO;
  i = ((struct lSet*)S)->hash_value(member) % ((struct lSet*)S)->storage;
  node = ((struct lSet*)S)->sets[i];

  if (NULL != node && (0 == ((struct lSet*)S)->compare(member, node->member)))
    return EXISTS_YES;
  return EXISTS_NO;
}

int set_insert(void* S, const void* member)
{
  int i;
  struct lSetNode* node;

  if (NULL == S)
    return RESULT_FAIL;

  i = ((struct lSet*)S)->hash_value(member) % ((struct lSet*)S)->storage;
  node = ((struct lSet*)S)->sets[i];
  if (NULL == node || 0 != ((struct lSet*)S)->compare(member, node->member))
  {
    struct lSetNode* pos = &((struct lSet*)S)->node;
    NEW0(node);
    node->member = member;
    node->prev   = pos->prev;
    node->next   = pos;
    pos->prev->next = node;
    pos->prev    = node;
    ((struct lSet*)S)->sets[i] = node;
    ++((struct lSet*)S)->size;
  }
  else 
    node->member = member;
  ++((struct lSet*)S)->timestamp;

  return RESULT_OK;
}

void* set_remove(void* S, const void* member)
{
  int i;
  struct lSetNode* node;

  if (NULL == S)
    return NULL;

  ++((struct lSet*)S)->timestamp;
  i = ((struct lSet*)S)->hash_value(member) % ((struct lSet*)S)->storage;
  node = ((struct lSet*)S)->sets[i];
  if (NULL != node && 0 == ((struct lSet*)S)->compare(member, node->member))
  {
    struct lSetNode* prev = node->prev;
    struct lSetNode* next = node->next;
    prev->next = next;
    next->prev = prev;
    FREE(((struct lSet*)S)->sets[i]);
    --((struct lSet*)S)->size;

    return (void*)member;
  }

  return NULL;
}

lSetIter set_begin(void* S)
{
  return (NULL != S ? (lSetIter)(((struct lSet*)S)->node.next) : NULL);
}

lSetIter set_end(void* S)
{
  return (NULL != S ? (lSetIter)(&((struct lSet*)S)->node) : NULL);
}

lSetIter set_iter_next(lSetIter iter)
{
  return (NULL != iter ? (lSetIter)(((struct lSetNode*)iter)->next) : NULL);
}

void set_for_each(void* S, void (*visit)(const void*, void*), void* arg)
{
  unsigned int stamp;
  lSetIter beg = set_begin(S);
  lSetIter end = set_end(S);

  if (NULL == S || NULL == visit || NULL == beg)
    return;
  stamp = ((struct lSet*)S)->timestamp;
  for ( ; beg != end; beg = set_iter_next(beg))
  {
    visit(((struct lSetNode*)beg)->member, arg);
    assert(stamp == ((struct lSet*)S)->timestamp);
  }
}

void* set_union(void* S, void* T)
{
  if (NULL == S)
  {
    assert(NULL != T);
    return set_copy((struct lSet*)T, ((struct lSet*)T)->storage);
  }
  else if (NULL == T)
    return set_copy((struct lSet*)S, ((struct lSet*)S)->storage);
  else
  {
    lSetIter beg, end = set_end(T);
    struct lSet* union_S = set_copy((struct lSet*)S, 
        arith_max(((struct lSet*)S)->storage, ((struct lSet*)T)->storage));
    assert(((struct lSet*)S)->compare == ((struct lSet*)T)->compare
        && ((struct lSet*)S)->hash_value == ((struct lSet*)T)->hash_value);

    for (beg = set_begin(T); beg != end; beg = set_iter_next(beg))
      set_insert(union_S, ((struct lSetNode*)beg)->member);

    return union_S;
  }

  return NULL;
}

void* set_inter(void* S, void* T)
{
  if (NULL == S)
  {
    assert(NULL != T);
    return set_create(((struct lSet*)T)->storage, ((struct lSet*)T)->compare, 
        ((struct lSet*)T)->hash_value);
  }
  else if (NULL == T)
  {
    return set_create(((struct lSet*)S)->storage, ((struct lSet*)S)->compare, 
        ((struct lSet*)S)->hash_value);
  }
  else if (set_size(S) < set_size(T))
    set_inter(T, S);
  else
  {
    lSetIter beg, end = set_end(T);
    struct lSet* inter_S = (struct lSet*)set_create(arith_min(((struct lSet*)S)->storage, 
      ((struct lSet*)T)->storage), ((struct lSet*)S)->compare, ((struct lSet*)T)->hash_value);
    assert(((struct lSet*)S)->compare == ((struct lSet*)T)->compare
        && ((struct lSet*)S)->hash_value == ((struct lSet*)T)->hash_value);

    for (beg = set_begin(T); beg != end; beg = set_iter_next(beg))
    {
      if (EXISTS_YES == set_find(S, ((struct lSetNode*)beg)->member))
        set_insert(inter_S, ((struct lSetNode*)beg)->member);
    }

    return inter_S;
  }

  return NULL;
}

void* set_minus(void* S, void* T)
{
  if (NULL == S)
  {
    assert(NULL != T);
    return set_create(((struct lSet*)T)->storage, ((struct lSet*)T)->compare, 
        ((struct lSet*)T)->hash_value);
  }
  else if (NULL == T)
    return set_copy((struct lSet*)S, ((struct lSet*)S)->storage);
  else
  {
    lSetIter beg, end = set_end(S);
    struct lSet* minus_S = (struct lSet*)set_create(arith_min(((struct lSet*)S)->storage, 
      ((struct lSet*)T)->storage), ((struct lSet*)T)->compare, ((struct lSet*)T)->hash_value);
    assert(((struct lSet*)S)->compare == ((struct lSet*)T)->compare 
        && ((struct lSet*)S)->hash_value == ((struct lSet*)T)->hash_value);
    
    for (beg = set_begin(S); beg != end; beg = set_iter_next(beg))
    {
      if (EXISTS_NO == set_find(T, ((struct lSetNode*)beg)->member))
        set_insert(minus_S, ((struct lSetNode*)beg)->member);
    }

    return minus_S;
  }

  return NULL;
}

void* set_diff(void* S, void* T)
{
  if (NULL == S)
  {
    assert(NULL != T);
    return set_copy((struct lSet*)T, ((struct lSet*)T)->storage);
  }
  else if (NULL == T)
    return set_copy((struct lSet*)S, ((struct lSet*)S)->storage);
  else
  {
    lSetIter beg, end;
    struct lSet* diff_S = (struct lSet*)set_create(arith_min(((struct lSet*)S)->storage, 
      ((struct lSet*)T)->storage), ((struct lSet*)S)->compare, ((struct lSet*)S)->hash_value);
    assert(((struct lSet*)S)->compare == ((struct lSet*)T)->compare 
        && ((struct lSet*)S)->hash_value == ((struct lSet*)T)->hash_value);

    end = set_end(T);
    for (beg = set_begin(T); beg != end; beg = set_iter_next(beg))
    {
      if (EXISTS_NO == set_find(S, ((struct lSetNode*)beg)->member))
        set_insert(diff_S, ((struct lSetNode*)beg)->member);
    }

    end = set_end(S);
    for (beg = set_begin(S); beg != end; beg = set_iter_next(beg))
    {
      if (EXISTS_NO == set_find(T, ((struct lSetNode*)beg)->member))
        set_insert(diff_S, ((struct lSetNode*)beg)->member);
    }

    return diff_S;
  }

  return NULL;
}
