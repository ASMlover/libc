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
#include <string.h>
#include "../inc/mem_check.h"

#include "test.h"



typedef struct _TestMemCheck {
  int   id;
  char  name[32];
} TestMemCheck;

void test_memcheck(void)
{
  fprintf(stdout, "call function : %s\n", __func__);
  
  fprintf(stdout, "test function MEM_ALLOC ===>\n");
  {
    TestMemCheck* tmc = (TestMemCheck*)MEM_ALLOC(sizeof(TestMemCheck));
    fprintf(stdout, "\tcall MEM_ALLOC success, object is id = %d, name = '%s'\n", tmc->id, tmc->name);
    tmc->id = rand() % 1000;
    strcpy(tmc->name, "MEM_ALLOC TestMemCheck");
    fprintf(stdout, "\tafter set variable, object is id = %d, name = '%s'\n", tmc->id, tmc->name);
    MEM_FREE(tmc);
  }

  fprintf(stdout, "test function MEM_CALLOC ===>\n");
  {
    TestMemCheck* tmc = (TestMemCheck*)MEM_CALLOC(1, sizeof(TestMemCheck));
    fprintf(stdout, "\tcall MEM_CALLOC success, object is id = %d, name = '%s'\n", tmc->id, tmc->name);
    tmc->id = rand() % 1000;
    strcpy(tmc->name, "MEM_CALLOC TestMemCheck");
    fprintf(stdout, "\tafter set variable, object is id = %d, name = '%s'\n", tmc->id, tmc->name);
    MEM_FREE(tmc);
  }

  fprintf(stdout, "\ntest function MEM_FREE ===>\n");
  {
    TestMemCheck* tmc = (TestMemCheck*)MEM_ALLOC(sizeof(TestMemCheck));
    MEM_FREE(tmc);
    fprintf(stdout, "\tafter free tm, it's pointer address is 0x%p\n", tmc);
  }
  
  fprintf(stdout, "\ntest function MEM_REALLOC ===>\n");
  {
    int* p = (int*)MEM_ALLOC(sizeof(int) * 10);
    int  i;

    for (i = 0; i < 10; ++i)
      p[i] = i * i;
    fprintf(stdout, "\tafter create the 'p' array, it's value is: \n");
    for (i = 0; i < 10; ++i)
      fprintf(stdout, "[%02d] = %03d\t", i + 1, p[i]);
    fprintf(stdout, "\n");

    p = (int*)MEM_REALLOC(p, sizeof(int) * 20);
    fprintf(stdout, "\tafter create the 'p' array, it's value is: \n");
    for (i = 0; i < 20; ++i)
      fprintf(stdout, "[%02d] = %03d\t", i + 1, p[i]);
    fprintf(stdout, "\n");

    for (i = 10; i < 20; ++i)
      p[i] = i * i;
    fprintf(stdout, "\tafter create the 'p' array, it's value is: \n");
    for (i = 0; i < 20; ++i)
      fprintf(stdout, "[%02d] = %03d\t", i + 1, p[i]);

    MEM_FREE(p);
  }  
}
