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
#include <time.h>
#include "../inc/assert.h"
#include "../inc/memory.h"
#include "../inc/list.h"

#include "test.h"


static void list_object_show(void* L)
{
  fprintf(stdout, 
    "\t__list__ : __object__ 0x%p = {\n"
    "\t  size=>%d,\n"
    "\t  empty=>%s,\n"
    "\t  front=>0x%p,\n"
    "\t  back=>0x%p,\n"
    "\t  begin=>0x%p,\n"
    "\t  end=>0x%p\n"
    "\t}\n", 
    L, list_size(L), (list_empty(L) ? "yes" : "no"), 
    list_front(L), list_back(L), list_begin(L), list_end(L));
}

static void list_object_show_elements_double(void* L)
{
  lListIter beg = list_begin(L), end = list_end(L);
  int i;

  for (i = 0 ; beg != end; ++i, beg = list_iter_next(beg))
    fprintf(stdout, "\tlist object element [%02d] =>{element=>0x%p, value=>%.3f}\n", 
      i, *beg, *((double*)*beg));
}

static void list_element_show_double(void* x, void* arg)
{
  {arg = arg;}
  fprintf(stdout, "\tlist object element => {element=>0x%p, value=>%.3f}\n", x, *(double*)x);
}

static void list_element_destroy_double(void* x, void* arg)
{
  {arg = arg;}
  fprintf(stdout, "\tthe destroyed element {element=>0x%p, value=>%.3f}\n", x, *(double*)x);
  free(x);
}

static void list_element_destroy(void* x)
{
  list_element_destroy_double(x, NULL);
}


void test_list(void)
{
  void* L;

  fprintf(stdout, "call function : %s\n", __func__);

  L = list_create();
  fprintf(stdout, "create list object %s {object=>0x%p}\n", (NULL != L ? "success" : "failed"), L);
  list_object_show(L);

  fprintf(stdout, "\ntest function - list_push_back ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 10; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d  = (i + 1) * (i + 1) * rand() % 1000 * 0.123;
      fprintf(stdout, "\t{element=>0x%p, value=>%.3f}\n", d, *d);
      list_push_back(L, d);
    }
    list_object_show(L);
    list_object_show_elements_double(L);
    list_clear(L, list_element_destroy);
  }
  list_object_show(L);

  fprintf(stdout, "\ntest function - list_push_front ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 10; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 1000 * 0.321;
      fprintf(stdout, "\t{element=>0x%p, value=>%.3f}\n", d, *d);
      list_push_front(L, d);
    }
    list_object_show(L);
    list_object_show_elements_double(L);
    list_clear(L, list_element_destroy);
  }
  list_object_show(L);

  fprintf(stdout, "\ntest function - list_insert ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 500 * 0.543 + 10000;
      fprintf(stdout, "\t{element=>0x%p, value=>%.3f}\n", d, *d);
      list_insert(L, list_end(L), d);
    }
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 500 * 0.345 + 50000;
      fprintf(stdout, "\t{element=>0x%p, value=>%.3f}\n", d, *d);
      list_insert(L, list_begin(L), d);
    }

    list_object_show(L);
    list_object_show_elements_double(L);
    list_clear(L, list_element_destroy);
  }
  list_object_show(L);

  fprintf(stdout, "\ntest function - list_pop_back ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 50000 * 0.789;
      fprintf(stdout, "\t{element=>0x%p, value=>%.3f}\n", d, *d);
      list_push_back(L, d);
    }
    list_object_show(L);
    list_object_show_elements_double(L);

    while (!list_empty(L))
      list_element_destroy(list_pop_back(L));
  }
  list_object_show(L);

  fprintf(stdout, "\ntest function - list_push_front ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 99999 * 0.119;
      fprintf(stdout, "\t{element=>0x%p, value=>%.3f}\n", d, *d);
      list_push_back(L, d);
    }
    list_object_show(L);
    list_object_show_elements_double(L);

    while (!list_empty(L))
      list_element_destroy(list_pop_front(L));
  }
  list_object_show(L);

  fprintf(stdout, "\ntest function - list_erase ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 99999 * 0.119;
      fprintf(stdout, "\t{element=>0x%p, value=>%.3f}\n", d, *d);
      list_push_back(L, d);
    }
    list_object_show(L);
    list_object_show_elements_double(L);

    while (!list_empty(L))
      list_element_destroy(list_erase(L, list_begin(L)));
  }
  list_object_show(L);

  fprintf(stdout, "\ntest function - list_for_each ===>\n");
  {
    int i;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * rand() % 10000 * 0.911;
      list_push_back(L, d);
    }
    list_object_show(L);
    list_for_each(L, list_element_show_double, NULL);
    list_for_each(L, list_element_destroy_double, NULL);
    list_object_show(L);
    list_clear(L, NULL);
  }
  list_object_show(L);

  list_release(&L);
  fprintf(stdout, "\nrelease list object {object=>0x%p}\n", L);
}
