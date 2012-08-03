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
#include "../inc/config.h"
#include "../inc/sequence.h"

#include "test.h"


static void sequence_object_show(void* S)
{
  fprintf(stdout,
      "  show sequence object :\n"
      "\t__sequence__ -> {\n"
      "\t  object => 0x%p,\n"
      "\t  size => %d,\n"
      "\t  empty => '%s',\n"
      "\t  front => 0x%p,\n"
      "\t  back => 0x%p,\n"
      "\t}\n", 
      S, sequence_size(S), (sequence_empty(S) ? "yes" : "no"), 
      sequence_front(S), sequence_back(S)
      );
}

static void sequence_element_display(void* x, void* arg)
{
  {arg = arg;}
  if (NULL != x)
    fprintf(stdout, "\tdisplay element -> {object=>0x%p, value=>%.3f}\n", x, *(double*)x);
}

static void sequence_element_destroy(void* x, void* arg)
{
  {arg = arg;}
  if (NULL != x)
  {
    fprintf(stdout, "\tdestroy element -> {object=>0x%p, value=>%.3f}\n", x, *(double*)x);
    free(x);
  }
}


void test_sequence(void)
{
  int i;
  void* S = sequence_create(0);
  fprintf(stdout, "call function : %s\n", __func__);
  sequence_object_show(S);

  fprintf(stdout, "\ntest function - sequence_push_front ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 20; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5555 * 0.123 * 20;
      fprintf(stdout, "\tpush_front -> {object=>0x%p, value=>%.3f}\n", d, *d);
      sequence_push_front(S, d);
    }
    sequence_object_show(S);
    sequence_for_each(S, sequence_element_display, NULL);

    sequence_for_each(S, sequence_element_destroy, NULL);
    sequence_object_show(S);
    sequence_clear(S);
  }
  sequence_object_show(S);
  
  fprintf(stdout, "\ntest function - sequence_push_back ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 20; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5555 * 0.123 * 20;
      fprintf(stdout, "\tpush_back -> {object=>0x%p, value=>%.3f}\n", d, *d);
      sequence_push_back(S, d);
    }
    sequence_object_show(S);
    sequence_for_each(S, sequence_element_display, NULL);

    sequence_for_each(S, sequence_element_destroy, NULL);
    sequence_object_show(S);
    sequence_clear(S);
  }
  sequence_object_show(S);
  
  fprintf(stdout, "\ntest function - sequence_get/sequence_set ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 20; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5555 * 0.123 * 20;
      fprintf(stdout, "\tpush_back -> {object=>0x%p, value=>%.3f}\n", d, *d);
      sequence_push_back(S, d);
    }
    sequence_object_show(S);
    sequence_for_each(S, sequence_element_display, NULL);

    for (i = 0; i < sequence_size(S); ++i)
    {
      double* r;
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * 1.0;
      r = sequence_set(S, i, d);
      fprintf(stdout, "\tset -> {object=>0x%p,value=>%.3f}\n", d, *d);
      fprintf(stdout, "\tset return -> {object=>0x%p,value=>%.3f}\n", r, *r);
      free(r), r = NULL;
    }
    sequence_object_show(S);
    for (i = 0; i < sequence_size(S); ++i)
    {
      double* d = sequence_get(S, i);
      if (NULL != d)
        fprintf(stdout, "\tget -> {index=>%d,object=>0x%p,value=>%.3f}\n", i, d, *d);
    }

    sequence_for_each(S, sequence_element_destroy, NULL);
    sequence_object_show(S);
    sequence_clear(S);
  }
  sequence_object_show(S);

  fprintf(stdout, "\ntest function - sequence_pop_front ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 20; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5555 * 0.123 * 20;
      fprintf(stdout, "\tpush_back -> {object=>0x%p, value=>%.3f}\n", d, *d);
      sequence_push_back(S, d);
    }
    sequence_object_show(S);
    sequence_for_each(S, sequence_element_display, NULL);

    while (!sequence_empty(S))
    {
      double* d = sequence_pop_front(S);
      if (NULL != d)
      {
        fprintf(stdout, "\tpop_front -> {object=>0x%p,value=>%.3f}\n", d, *d);
        free(d);
      }
    }
  }
  sequence_object_show(S);
  
  fprintf(stdout, "\ntest function - sequence_pop_back ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 20; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5555 * 0.123 * 20;
      fprintf(stdout, "\tpush_back -> {object=>0x%p, value=>%.3f}\n", d, *d);
      sequence_push_back(S, d);
    }
    sequence_object_show(S);
    sequence_for_each(S, sequence_element_display, NULL);

    while (!sequence_empty(S))
    {
      double* d = sequence_pop_back(S);
      if (NULL != d)
      {
        fprintf(stdout, "\tpop_back -> {object=>0x%p,value=>%.3f}\n", d, *d);
        free(d);
      }
    }
  }
  sequence_object_show(S);

  fprintf(stdout, "\ntest function - sequence_release ===>\n");
  sequence_release(&S);
  sequence_object_show(S);


  fprintf(stdout, "\ntest function - sequence_create_by ===>\n");
  {
    S = sequence_create_by("a", "b", "c", "d", "e", NULL);
    sequence_object_show(S);

    for (i = 0; i < sequence_size(S); ++i)
    {
      char* s = sequence_get(S, i);
      if (NULL != s)
        fprintf(stdout, "\telement display -> {object=>0x%p,value=>%s}\n", s, s);
    }

    sequence_release(&S);
    sequence_object_show(S);
  }
}
