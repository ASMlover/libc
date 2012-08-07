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
#include "../inc/assert.h"
#include "../inc/ring.h"

#include "test.h"


static void ring_object_show(void* R)
{
  fprintf(stdout, 
      "\t__ring__ -> {\n"
      "\t  object=>0x%p,\n"
      "\t  size=>%d,\n"
      "\t  empty=>'%s',\n"
      "\t  front=>0x%p,\n"
      "\t  back=>0x%p,\n"
      "\t}\n", 
      R, ring_size(R), (ring_empty(R) ? "yes" : "no"), 
      ring_front(R), ring_back(R)
      );
}

static void ring_element_display(void* x, void* arg)
{
  {arg = arg;}
  if (NULL != x)
    fprintf(stdout, "\tdisplay element {object=>0x%p,value=>%.3f}\n", x, *(double*)x);
}

static void ring_element_destroy(void* x, void* arg)
{
  {arg = arg;}
  if (NULL != x)
  {
    fprintf(stdout, "\tdestrpy element {object=>0x%p,value=>%.3f}\n", x, *(double*)x);
    free(x);
  }
}


void test_ring(void)
{
  int i;
  void* x;
  void* R = ring_create();
  fprintf(stdout, "call function : %s\n", __func__);
  ring_object_show(R);

  fprintf(stdout, "\ntest function - ring_push_front ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.346;
      fprintf(stdout, "\tpush_front element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_push_front(R, d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    ring_for_each(R, ring_element_destroy, NULL);
    ring_object_show(R);
    ring_clear(R);
  }
  ring_object_show(R);
  
  fprintf(stdout, "\ntest function - ring_push_back ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.346;
      fprintf(stdout, "\tpush_back element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_push_back(R, d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    ring_for_each(R, ring_element_destroy, NULL);
    ring_object_show(R);
    ring_clear(R);
  }
  ring_object_show(R);
  
  fprintf(stdout, "\ntest function - ring_pop_front ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.346;
      fprintf(stdout, "\tpush_back element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_push_back(R, d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    x = ring_pop_front(R);
    fprintf(stdout, "\tthe pop_front element {object=>0x%p,value=>%.3f}\n", x, *(double*)x);
    free(x);
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    ring_for_each(R, ring_element_destroy, NULL);
    ring_object_show(R);
    ring_clear(R);
  }
  ring_object_show(R);
  
  fprintf(stdout, "\ntest function - ring_pop_back ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.346;
      fprintf(stdout, "\tpush_back element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_push_back(R, d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    x = ring_pop_back(R);
    fprintf(stdout, "\tthe pop_back element {object=>0x%p,value=>%.3f}\n", x, *(double*)x);
    free(x);
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    ring_for_each(R, ring_element_destroy, NULL);
    ring_object_show(R);
    ring_clear(R);
  }
  ring_object_show(R);
  
  fprintf(stdout, "\ntest function - ring_insert ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.346;
      fprintf(stdout, "\tpush_back element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_push_back(R, d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    {
      double* d = (double*)malloc(sizeof(double));
      *d = 123456.123;
      fprintf(stdout, "\tinsert element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_insert(R, 0, d);

      d = (double*)malloc(sizeof(double));
      *d = 54321.321;
      fprintf(stdout, "\tinsert element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_insert(R, -5, d);
      
      d = (double*)malloc(sizeof(double));
      *d = 55555.565;
      fprintf(stdout, "\tinsert element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_insert(R, 7, d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    ring_for_each(R, ring_element_destroy, NULL);
    ring_object_show(R);
    ring_clear(R);
  }
  ring_object_show(R);
  
  fprintf(stdout, "\ntest function - ring_erase ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.346;
      fprintf(stdout, "\tpush_back element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_push_back(R, d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    {
      double* d = ring_erase(R, 0);
      fprintf(stdout, "\terase element {object=>0x%p,value=>%.3f}\n", d, *d);
      free(d);

      d = ring_erase(R, 3);
      fprintf(stdout, "\terase element {object=>0x%p,value=>%.3f}\n", d, *d);
      free(d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    ring_for_each(R, ring_element_destroy, NULL);
    ring_object_show(R);
    ring_clear(R);
  }
  ring_object_show(R);
  
  fprintf(stdout, "\ntest function - ring_get ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.346;
      fprintf(stdout, "\tpush_back element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_push_back(R, d);
    }
    ring_object_show(R);

    for (i = 0; i < ring_size(R); ++i)
    {
      double* d = ring_get(R, i);
      fprintf(stdout, "\tget element {object=>0x%p,value=>%.3f}\n", d, *d);
    }

    ring_for_each(R, ring_element_destroy, NULL);
    ring_object_show(R);
    ring_clear(R);
  }
  ring_object_show(R);
  
  fprintf(stdout, "\ntest function - ring_set ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.346;
      fprintf(stdout, "\tpush_back element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_push_back(R, d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    {
      double* d = (double*)malloc(sizeof(double));
      *d = 999.999;
      fprintf(stdout, "\tnew set element {object=>0x%p,value=>%.3f}\n", d, *d);
      x = ring_set(R, 3, d);
      fprintf(stdout, "\tafter set - old data {object=>0x%p,value=>%.3f}\n", x, *(double*)x);
      free(x);
    }
    ring_for_each(R, ring_element_display, NULL);

    ring_for_each(R, ring_element_destroy, NULL);
    ring_object_show(R);
    ring_clear(R);
  }
  ring_object_show(R);
  
  fprintf(stdout, "\ntest function - ring_rotate ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.346;
      fprintf(stdout, "\tpush_back element {object=>0x%p,value=>%.3f}\n", d, *d);
      ring_push_back(R, d);
    }
    ring_object_show(R);
    ring_for_each(R, ring_element_display, NULL);

    ring_rotate(R, 3);
    ring_for_each(R, ring_element_display, NULL);
    ring_rotate(R, -4);
    ring_for_each(R, ring_element_display, NULL);

    ring_for_each(R, ring_element_destroy, NULL);
    ring_object_show(R);
    ring_clear(R);
  }
  ring_object_show(R);

  fprintf(stdout, "\ntest function - ring_release ===>\n");
  ring_release(&R);
  ring_object_show(R);
}
