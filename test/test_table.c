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
#include "../inc/table.h"

#include "test.h"


static void table_object(void* T)
{
  fprintf(stdout, 
    "\t__table__ -> {\n"
    "\t  object=>0x%p,\n"
    "\t  size=>%d,\n"
    "\t  empty=>'%s',\n"
    "\t  begin=>0x%p,\n"
    "\t  end=>0x%p,\n"
    "\t}\n", 
    T, table_size(T), (table_empty(T) ? "yes" : "no"), 
    table_begin(T), table_end(T)
    );
}

static void table_key_value_show(const void* key, void* value, void* arg)
{
  {arg = arg;}
  fprintf(stdout, "\tkey-value=>{key=>%d,value=>{object=>0x%p,value=>%.3f}}\n", 
    (int)key, value, *(double*)value);
}

static void table_key_value_destroy(const void* key, void* value, void* arg)
{
  {arg = arg;}
  fprintf(stdout, "\tdestroyed {key=>%d,value=>{object=>0x%p,value=>%.3f}}\n", 
    (int)key, value, *(double*)value);
  free(value);
}


void test_table(void)
{
  int i;
  void* T = table_create(100, NULL, NULL);
  fprintf(stdout, "call function : %s\n", __func__);
  table_object(T);

  fprintf(stdout, "\ntest function - table_insert ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.123;
      fprintf(stdout, "\tinsert {key=>%d,value=>{object=>0x%p,value=>%.3f}}\n", i, d, *d);
      table_insert(T, (const void*)i, d);
    }
    table_for_each(T, table_key_value_show, NULL);
    table_for_each(T, table_key_value_destroy, NULL);
    table_object(T);
    table_clear(T);
  }
  table_object(T);

  fprintf(stdout, "\ntest function - table_remove ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.123;
      fprintf(stdout, "\tinsert {key=>%d,value=>{object=>0x%p,value=>%.3f}}\n", i, d, *d);
      table_insert(T, (const void*)i, d);
    }
    table_for_each(T, table_key_value_show, NULL);
    table_for_each(T, table_key_value_destroy, NULL);
    table_object(T);
    for (i = 0; i < 5; ++i)
      table_remove(T, (const void*)i);
    table_object(T);
    table_clear(T);
  }
  table_object(T);

  fprintf(stdout, "\ntest function - table_get ===>\n");
  {
    double* d;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 5000 * 0.123;
      fprintf(stdout, "\tinsert {key=>%d,value=>{object=>0x%p,value=>%.3f}}\n", i, d, *d);
      table_insert(T, (const void*)i, d);
    }
    table_object(T);

    d = table_get(T, (const void*)3);
    if (NULL != d)
      fprintf(stdout, "\t{key=>3, value=>0x%p} => %.3f\n", d, *d);

    table_for_each(T, table_key_value_show, NULL);
    table_for_each(T, table_key_value_destroy, NULL);
    table_clear(T);
  }
  table_object(T);

  fprintf(stdout, "\ntest function - table_release ===>\n");
  table_release(&T);
  table_object(T);
}
