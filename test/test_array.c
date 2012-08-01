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
#include "../inc/memory.h"
#include "../inc/array.h"

#include "test.h"


static void array_object_show(void* A)
{
  fprintf(stdout,
      "  show object of array :\n"
      "\t__array__ -> {\n"
      "\t  object=>0x%p,\n"
      "\t  size=>%d,\n"
      "\t  empty=>'%s',\n"
      "\t  begin=>0x%p,\n"
      "\t  end=>0x%p,\n"
      "\t  front=>0x%p,\n"
      "\t  back=>0x%p,\n"
      "\t}\n", 
      A, array_size(A), (array_empty(A) ? "yes" : "no"), 
      array_begin(A), array_end(A), array_front(A), array_back(A)
      );
}

static void array_element_display(void* x, void* arg)
{
  {arg = arg;}
  if (NULL != x)
    fprintf(stdout, "\tdisplay element -> {object=>0x%p,value=>%.3f}\n", x, *(double*)x);
}

static void array_element_destroy(void* x, void* arg)
{
  {arg = arg;}
  if (NULL != x)
    fprintf(stdout, "\tdestroyed element -> {object=>0x%p,value=>%.3f}\n", x, *(double*)x);
  FREE(x);
}


void test_array(void)
{
  int i;
  double* d;
  void* A = array_create(0);
  fprintf(stdout, "call function : %s\n", __func__);
  array_object_show(A);

  fprintf(stdout, "\ntest function - array_push_back ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      NEW0(d);
      *d = (i + 1) * (i + 1) * rand() % 5555 * 0.123;
      fprintf(stdout, "\tappend into array {object=>0x%p, value=>%.3f}\n", d, *d);
      array_push_back(A, d);
    }
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    array_for_each(A, array_element_destroy, NULL);
    array_object_show(A);
    array_clear(A);
  }
  array_object_show(A);

  fprintf(stdout, "\ntest function - array_pop_back ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      NEW0(d);
      *d = (i + 1) * (i + 1) * rand() % 5555 * 0.123;
      fprintf(stdout, "\tappend into array {object=>0x%p, value=>%.3f}\n", d, *d);
      array_push_back(A, d);
    }
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    d = (double*)array_pop_back(A);
    fprintf(stdout, "  the pop element {object=>0x%p,value=>%.3f}\n", d, *d);
    FREE(d);
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    array_for_each(A, array_element_destroy, NULL);
    array_object_show(A);
    array_clear(A);
  }
  array_object_show(A);

  fprintf(stdout, "\ntest function - array_erase ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      NEW0(d);
      *d = (i + 1) * (i + 1) * rand() % 5555 * 0.123;
      fprintf(stdout, "\tappend into array {object=>0x%p, value=>%.3f}\n", d, *d);
      array_push_back(A, d);
    }
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    d = (double*)array_erase(A, array_begin(A));
    fprintf(stdout, "  the erased begin element {object=>0x%p,value=>%.3f}\n", d, *d);
    FREE(d);
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);
    d = (double*)array_erase(A, array_end(A));
    fprintf(stdout, "  the erased end element {object=>0x%p,value=>%.3f}\n", d, *d);
    FREE(d);
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    array_for_each(A, array_element_destroy, NULL);
    array_object_show(A);
    array_clear(A);
  }
  array_object_show(A);

  fprintf(stdout, "\ntest function - array_remove ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      NEW0(d);
      *d = (i + 1) * (i + 1) * rand() % 5555 * 0.123;
      fprintf(stdout, "\tappend into array {object=>0x%p, value=>%.3f}\n", d, *d);
      array_push_back(A, d);
    }
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    d = (double*)array_remove(A, 3);
    fprintf(stdout, "  the removed [3] -> {object=>0x%p,value=>%.3f}\n", d, *d);
    FREE(d);
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    array_for_each(A, array_element_destroy, NULL);
    array_object_show(A);
    array_clear(A);
  }
  array_object_show(A);

  fprintf(stdout, "\ntest function - array_copy ===>\n");
  {
    void* copy_A;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      NEW0(d);
      *d = (i + 1) * (i + 1) * rand() % 5555 * 0.123;
      fprintf(stdout, "\tappend into array {object=>0x%p, value=>%.3f}\n", d, *d);
      array_push_back(A, d);
    }
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    copy_A = array_copy(A, 10);
    array_object_show(copy_A);
    array_for_each(copy_A, array_element_display, NULL);
    array_release(&copy_A);

    array_for_each(A, array_element_destroy, NULL);
    array_clear(A);
  }
  array_object_show(A);

  fprintf(stdout, "\ntest function - array_resize ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      NEW0(d);
      *d = (i + 1) * (i + 1) * rand() % 5555 * 0.123;
      fprintf(stdout, "\tappend into array {object=>0x%p, value=>%.3f}\n", d, *d);
      array_push_back(A, d);
    }
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    array_resize(A, 20);
    array_object_show(A);
    array_for_each(A, array_element_display, NULL);

    array_for_each(A, array_element_destroy, NULL);
    array_clear(A);
  }
  array_object_show(A);

  fprintf(stdout, "\ntest function - array_release ===>\n");
  array_release(&A);
  array_object_show(A);
}
