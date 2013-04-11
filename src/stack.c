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


typedef struct stack_node_s {
  struct stack_node_s* next;
  element_t x;
} *stack_node_t;

struct stack_s {
  int count;
  stack_node_t head;
};

static void 
stack_clear(stack_t* self)
{
  stack_node_t t, n;
  for (t = self->head; NULL != t; t = n) {
    n = t->next;
    FREE(t);
  }
  self->count = 0;
}


stack_t* 
stack_create(void)
{
  stack_t* self = (stack_t*)CALLOC(sizeof(*self), sizeof(char));

  return self;
}

void 
stack_release(stack_t** S)
{
  assert(NULL != *S);
  stack_clear(*S);
  FREE(*S);
}

int 
stack_empty(stack_t* S)
{
  return (NULL != S ? (0 == S->head) : ERROR_LEN);
}

void 
stack_push(stack_t* S, element_t x)
{
  stack_node_t t;

  assert(NULL != S);
  t = (stack_node_t)ALLOC(sizeof(*t));
  t->x = x;
  t->next = S->head;
  S->head = t;
  ++S->count;
}

element_t 
stack_pop(stack_t* S)
{
  element_t x;
  stack_node_t t;

  assert(0 != S);
  assert(S->count > 0);
  t = S->head;
  S->head = t->next;
  --S->count;
  x = t->x;
  FREE(t);

  return x;
}
