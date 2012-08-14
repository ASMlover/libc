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
#include "../inc/bit.h"

#include "test.h"


static void bit_object_show(void* B)
{
  fprintf(stdout, 
      "\t__bit__ -> {\n"
      "\t  object=>0x%p,\n"
      "\t  size=>%d,\n"
      "\t  count=>%d,\n"
      "\t}\n", 
      B, bit_size(B), bit_count(B)
      );
}

static void bit_object_bit_show(int i, int v, void* arg)
{
  {arg = arg;}
  fprintf(stdout, "\tbit object bit {bit=>%d,value=>%d}\n", i, v);
}


void test_bit(void)
{
  int i;
  void* B = bit_create(10);
  fprintf(stdout, "call function : %s\n", __func__);
  bit_object_show(B);

  fprintf(stdout, "\ntest function - bit_set/bit_get ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < bit_size(B); ++i)
      bit_set(B, i, rand() % 2);

    bit_object_show(B);
    for (i = 0; i < bit_size(B); ++i)
      fprintf(stdout, "\tbit values [%02d] => %d\n", i, bit_get(B, i));
  }

  fprintf(stdout, "\ntest function - bit_clear_range ===>\n");
  {
    bit_clear_range(B, 0, 4);
    bit_object_show(B);
    bit_for_each(B, bit_object_bit_show, NULL);
  }

  fprintf(stdout, "\ntest function - bit_set_range ===>\n");
  {
    bit_set_range(B, 5, 9);
    bit_object_show(B);
    bit_for_each(B, bit_object_bit_show, NULL);
  }

  fprintf(stdout, "\ntest function - bit_not_range ===>\n");
  {
    bit_not_range(B, 0, 9);
    bit_object_show(B);
    bit_for_each(B, bit_object_bit_show, NULL);
  }

  fprintf(stdout, "\ntest function - bit_clear ===>\n");
  {
    bit_clear(B);
    bit_object_show(B);
  }

  fprintf(stdout, "\ntest function - bit_release ===>\n");
  bit_release(&B);
  bit_object_show(B);


  fprintf(stdout, "\ntest function - bit_lt/bit_eq/bit_leq ===>\n");
  {
    void* B1 = bit_create(5);
    void* B2 = bit_create(5);

    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      bit_set(B1, i, rand() % 2);
      bit_set(B2, i, rand() % 2);
    }
    fprintf(stdout, "    B1 object show:\n");
    bit_for_each(B1, bit_object_bit_show, NULL);
    fprintf(stdout, "    B2 object show:\n");
    bit_for_each(B2, bit_object_bit_show, NULL);

    fprintf(stdout, "    B1 < B2 ? '%s'\n", bit_lt(B1, B2) ? "yes" : "no");
    fprintf(stdout, "    B1 = B2 ? '%s'\n", bit_eq(B1, B2) ? "yes" : "no");
    fprintf(stdout, "    B1 <= B2 ? '%s'\n", bit_leq(B1, B2) ? "yes" : "no");

    bit_release(&B1);
    bit_release(&B2);
  }

  fprintf(stdout, "\ntest function - union/inter/minus/diff ===>\n");
  {
    void* B1 = bit_create(5);
    void* B2 = bit_create(5);

    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      bit_set(B1, i, rand() % 2);
      bit_set(B2, i, rand() % 2);
    }
    fprintf(stdout, "    B1 object show:\n");
    bit_for_each(B1, bit_object_bit_show, NULL);
    fprintf(stdout, "    B2 object show:\n");
    bit_for_each(B2, bit_object_bit_show, NULL);

    B = bit_union(B1, B2);
    fprintf(stdout, "    B1 union B2 ->\n");
    bit_for_each(B, bit_object_bit_show, NULL);
    bit_release(&B);

    B = bit_inter(B1, B2);
    fprintf(stdout, "    B1 inter B2 ->\n");
    bit_for_each(B, bit_object_bit_show, NULL);
    bit_release(&B);
    
    B = bit_minus(B1, B2);
    fprintf(stdout, "    B1 minus B2 ->\n");
    bit_for_each(B, bit_object_bit_show, NULL);
    bit_release(&B);

    B = bit_diff(B1, B2);
    fprintf(stdout, "    B1 diff B2 ->\n");
    bit_for_each(B, bit_object_bit_show, NULL);
    bit_release(&B);

    bit_release(&B1);
    bit_release(&B2);
  }
}
