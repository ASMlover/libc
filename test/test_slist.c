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
#include "../inc/assert.h"
#include "../inc/slist.h"

#include "test.h"


static void slist_object_show(void* L)
{
  fprintf(stdout, 
    "\t__slist__ : __object__ = {\n"
    "\t  object => 0x%p,\n"
    "\t  size => %d,\n"
    "\t  empty => '%s',\n"
    "\t  front => 0x%p,\n"
    "\t  back => 0x%p,\n"
    "\t  begin => 0x%p,\n"
    "\t  end => 0x%p,\n"
    "\t}\n", 
    L, slist_size(L), (slist_empty(L) ? "yes" : "no"), slist_front(L), 
    slist_back(L), slist_begin(L), slist_end(L)
    );
}

static void slist_element_show_double(void* x, void* arg)
{
  {arg = arg;}
  fprintf(stdout, "\tslist element {object=>0x%p,value=>%.3f}\n", x, *(double*)x);
}

static void slist_object_elements_show_double(void* L)
{
  lSlistIter beg = slist_begin(L), end = slist_end(L);
  int i;

  for (i = 0 ; beg != end; ++i, beg = slist_iter_next(beg))
    fprintf(stdout, "\tslist element [%02d] {iter=>0x%p,object=>0x%p,value=>%.3f}\n", 
      i, beg, *beg, *(double*)*beg);
}

static void slist_element_destory_double(void* x, void* arg)
{
  {arg = arg;}
  fprintf(stdout, "\tthe destroyed element {object=>0x%p,value=>%.3f}\n", x, *(double*)x);
  free(x);
}

static void slist_element_destory(void* x)
{
  slist_element_destory_double(x, NULL);
}


void test_slist(void)
{
  void* L = slist_create();

  fprintf(stdout, "call function : %s\n", __func__);
  fprintf(stdout, "create slist object '%s'\n", (NULL != L ? "success" : "failed"));
  slist_object_show(L);

  fprintf(stdout, "\ntest function - slist_push_back ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 1000 * 0.123;
      fprintf(stdout, "\tpush_back {object=>0x%p,value=>%.3f}\n", d, *d);
      slist_push_back(L, d);
    }

    slist_object_show(L);
    slist_object_elements_show_double(L);
    slist_clear(L, slist_element_destory);
  }
  slist_object_show(L);

  fprintf(stdout, "\ntest function - slist_push_front ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 1000 * 0.123;
      fprintf(stdout, "\tpush_back {object=>0x%p,value=>%.3f}\n", d, *d);
      slist_push_front(L, d);
    }

    slist_object_show(L);
    slist_object_elements_show_double(L);
    slist_clear(L, slist_element_destory);
  }
  slist_object_show(L);

  fprintf(stdout, "\ntest function - slist_pop_front ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 1000 * 0.123;
      fprintf(stdout, "\tpush_back {object=>0x%p,value=>%.3f}\n", d, *d);
      slist_push_back(L, d);
    }
    slist_object_show(L);
    slist_object_elements_show_double(L);

    while (!slist_empty(L))
      slist_element_destory(slist_pop_front(L));

    slist_clear(L, slist_element_destory);
  }
  slist_object_show(L);

  fprintf(stdout, "\ttest of function - slist_for_each ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 1000 * 0.123;
      fprintf(stdout, "\tpush_back {object=>0x%p,value=>%.3f}\n", d, *d);
      slist_push_back(L, d);
    }
    slist_object_show(L);

    slist_for_each(L, slist_element_show_double, NULL);
    slist_for_each(L, slist_element_destory_double, NULL);
    slist_object_show(L);

    slist_clear(L, NULL);
  }
  slist_object_show(L);

  slist_release(&L);
  fprintf(stdout, "\ntest function - slist_release ===>\n");
  slist_object_show(L);
}
