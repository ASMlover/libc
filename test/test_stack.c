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
#include <time.h>
#include "../inc/stack.h"
#include "../inc/memory.h"

#include "test.h"


void test_stack(void)
{
  int S, i;

  fprintf(stdout, "call function : %s\n", __func__);

  fprintf(stdout, "test function stack_new ===>\n");
  S = stack_create();
  if (0 == S)
    fprintf(stdout, "\tcreate new stack object failed\n");
  else
    fprintf(stdout, "\tcreate new stack object success, S = 0x%08x\n", S);

  fprintf(stdout, "\ntest function stack_empty/stack_push/stack_pop ===>\n");
  fprintf(stdout, "\tnow the stack %s empty\n", stack_empty(S) ? "is" : "is not");
  srand((unsigned int)time(0));
  for (i = 0; i < 10; ++i)
  {
    double* d = (double*)ALLOC(sizeof(double));
    *d = rand() % 1000 * 8.012;
    stack_push(S, d);
    fprintf(stdout, "\t\tpush data [0x%p][%lf]\n", d, *d);
  }
  fprintf(stdout, "\tafter push 10 elements, stack %s empty\n", stack_empty(S) ? "is" : "is not");
  while (!stack_empty(S))
  {
    double* d = stack_pop(S);
    fprintf(stdout, "\t\tpop data [0x%p][%lf]\n", d, *d);
    FREE(d);
  }
  fprintf(stdout, "\tafter pop elements, stack %s empty\n", stack_empty(S) ? "is" : "is not");

  stack_release(&S);
  fprintf(stdout, "\nafter call function stack_free, S = 0x%p\n", (void*)S);
}
