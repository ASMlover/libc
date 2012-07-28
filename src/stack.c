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

#include "../inc/stack.h"


struct lStackNode {
  void* x;
  struct lStackNode* next;
};
struct lStack {
  struct lStackNode* head;
  int count;
};

static void stack_clear(struct lStack* self)
{
  struct lStackNode* t;
  struct lStackNode* n;
  for (t = self->head; NULL != t; t = n)
  {
    n = t->next;
    FREE(t);
  }
  self->count = 0;
}


void* stack_create(void)
{
  struct lStack* self;
  size_t size = sizeof(struct lStack);

  self = (struct lStack*)CALLOC(size, sizeof(char));
  return (void*)self;
}

void stack_release(void** S)
{
  assert(NULL != *S);
  stack_clear((struct lStack*)*S);
  FREE(*S);
}

int stack_empty(void* S)
{
  return (NULL != S ? (0 == ((struct lStack*)S)->count) : ERROR_LEN);
}

void stack_push(void* S, void* x)
{
  struct lStackNode* t;
  size_t size = sizeof(struct lStackNode);

  assert(NULL != S);
  t = (struct lStackNode*)CALLOC(size, sizeof(char));
  t->x = x;
  t->next = ((struct lStack*)S)->head;
  ((struct lStack*)S)->head = t;
  ++((struct lStack*)S)->count;
}

void* stack_pop(void* S)
{
  void* x;
  struct lStackNode* t;

  assert(0 != S);
  assert(((struct lStack*)S)->count > 0);
  t = ((struct lStack*)S)->head;
  ((struct lStack*)S)->head = t->next;
  --((struct lStack*)S)->count;
  x = t->x;
  FREE(t);

  return x;
}
