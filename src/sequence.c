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
#include "../inc/array.h"

#include "../inc/sequence.h"




void* sequence_create(int storage)
{
  return NULL;
}

void* sequence_create_by(void* x, ...)
{
  return NULL;
}

void sequence_release(void** S)
{
}

int sequence_size(void* S)
{
  return ERROR_LEN;
}

int sequence_empty(void* S)
{
  return 0;
}

void sequence_clear(void* S)
{
}

void* sequence_push_front(void* S, void* x)
{
  return NULL;
}

void* sequence_push_back(void* S, void* x)
{
  return NULL;
}

void* sequence_pop_front(void* S)
{
  return NULL;
}

void* sequence_pop_back(void* S)
{
  return NULL;
}

void* sequence_set(void* S, int i, void* x)
{
  return NULL;
}

void* sequence_get(void* S, int i)
{
  return NULL;
}

lSequenceIter sequence_begin(void* S)
{
  return NULL;
}

lSequenceIter sequence_end(void* S)
{
  return NULL;
}

lSequenceIter sequence_iter_next(lSequenceIter iter)
{
  return NULL;
}

void* sequence_front(void* S)
{
  return NULL;
}

void* sequence_back(void* S)
{
  return NULL;
}

void sequence_for_each(void* S, void (*visit)(void*, void*), void* arg)
{
}
