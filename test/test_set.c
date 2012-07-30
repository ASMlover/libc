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
#include <string.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/set.h"

#include "test.h"


static void set_object(void* S)
{
  fprintf(stdout, 
      "\t__set__ -> {\n"
      "\t  object=>0x%p,\n"
      "\t  size=>%d,\n"
      "\t  empty=>'%s',\n"
      "\t  begin=>0x%p,\n"
      "\t  end=>0x%p,\n"
      "\t}\n", 
      S, set_size(S), (set_empty(S) ? "yes" : "no"), 
      set_begin(S), set_end(S)
      );
}

static void set_member_show_double(const void* member, void* arg)
{
  {arg = arg;}
  fprintf(stdout, "\tset member=>{object=>0x%p,value=>%.3f}\n", member, *(double*)member);
}

static void set_member_destroy(const void* member, void* arg)
{
  {arg = arg;}
  fprintf(stdout, "\tdestroyed=>{object=>0x%p,value=>%.3f}\n", member, *(double*)member);
  free((void*)member);
}



void test_set(void)
{
  int i;
  void* S = set_create(100, NULL, NULL);
  fprintf(stdout, "call function : %s\n", __func__);
  set_object(S);

  fprintf(stdout, "\ntest function - set_insert ===>\n");
  {
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 1000 * 0.456;
      fprintf(stdout, "\tinsert {object=>0x%p, vlaue=>%.3f}\n", d, *d);
      set_insert(S, d);
    }
    set_object(S);

    set_for_each(S, set_member_show_double, NULL);
    set_for_each(S, set_member_destroy, NULL);
    set_object(S);
    set_clear(S);
  }
  set_object(S);

  fprintf(stdout, "\ntest function - set_remove ===>\n");
  {
    double* remove_member = NULL;
    srand((unsigned int)time(0));
    for (i = 0; i < 5; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * rand() % 1000 * 0.456;
      fprintf(stdout, "\tinsert {object=>0x%p, vlaue=>%.3f}\n", d, *d);
      set_insert(S, d);

      if (0 == i)
        remove_member = d;
    }
    set_object(S);
    set_for_each(S, set_member_show_double, NULL);

    set_remove(S, remove_member);
    set_object(S);
    set_for_each(S, set_member_show_double, NULL);

    set_for_each(S, set_member_destroy, NULL);
    set_object(S);
    set_clear(S);
  }
  set_object(S);

  fprintf(stdout, "\ntest function - set_release ===>\n");
  set_release(&S);
  set_object(S);


  fprintf(stdout, "\n\ntest function - set operations ===>\n");
  {
    void* s = set_create(100, NULL, NULL);
    void* t = set_create(100, NULL, NULL);
    void* oper_s;

    for (i = 0; i < 7; ++i)
    {
      double* d = (double*)malloc(sizeof(double));
      *d = (i + 1) * (i + 1) * 0.234;
      fprintf(stdout, "\tinsert s {object=>0x%p, value=>%.3f}\n", d, *d);
      if (i < 5)
        set_insert(s, d);
      set_insert(t, d);        
    }

    fprintf(stdout, "  show 's' set object:\n");
    set_object(s);
    set_for_each(s, set_member_show_double, NULL);
    fprintf(stdout, "  show 't' set object:\n");
    set_object(t);
    set_for_each(t, set_member_show_double, NULL);

    /* set_union */
    fprintf(stdout, "  test function - set_union ===>\n");
    oper_s = set_union(NULL, t);
    fprintf(stdout, "    s = NULL, t = t:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release union(s=NULL,t=t):\n");
    set_object(oper_s);
    /* *** */
    oper_s = set_union(s, NULL);
    fprintf(stdout, "    s = s, t = NULL:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release union(s=s,t=NULL):\n");
    set_object(oper_s);
    /* *** */
    oper_s = set_union(s, t);
    fprintf(stdout, "    s = s, t = t:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release union(s=s,t=t):\n");
    set_object(oper_s);

    /* set_inter */
    fprintf(stdout, "  test function - set_inter ===>\n");
    oper_s = set_inter(NULL, t);
    fprintf(stdout, "    s = NULL, t = t:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release inter(s=NULL,t=t):\n");
    set_object(oper_s);
    /* *** */
    oper_s = set_inter(s, NULL);
    fprintf(stdout, "    s = s, t = NULL:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release inter(s=s,t=NULL):\n");
    set_object(oper_s);
    /* *** */
    oper_s = set_inter(s, t);
    fprintf(stdout, "    s = s, t = t:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release inter(s=s,t=t):\n");
    set_object(oper_s);

    /* set_minus */
    fprintf(stdout, "  test function - set_minus ===>\n");
    oper_s = set_minus(NULL, t);
    fprintf(stdout, "    s = NULL, t = t:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release minus(s=NULL,t=t):\n");
    set_object(oper_s);
    /* *** */
    oper_s = set_minus(s, NULL);
    fprintf(stdout, "    s = s, t = NULL:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release minus(s=s,t=NULL):\n");
    set_object(oper_s);
    /* *** */
    oper_s = set_minus(s, t);
    fprintf(stdout, "    s = s, t = t:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release minus(s=s,t=t):\n");
    set_object(oper_s);

    /* set_diff */
    fprintf(stdout, "  test function - set_diff ===>\n");
    oper_s = set_diff(NULL, t);
    fprintf(stdout, "    s = NULL, t = t:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release diff(s=NULL,t=t):\n");
    set_object(oper_s);
    /* *** */
    oper_s = set_diff(s, NULL);
    fprintf(stdout, "    s = s, t = NULL:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release diff(s=s,t=NULL):\n");
    set_object(oper_s);
    /* *** */
    oper_s = set_diff(s, t);
    fprintf(stdout, "    s = s, t = t:\n");
    set_object(oper_s);
    set_for_each(oper_s, set_member_show_double, NULL);
    set_clear(oper_s);
    set_release(&oper_s);
    fprintf(stdout, "    after release diff(s=s,t=t):\n");
    set_object(oper_s);


    fprintf(stdout, "  release 's' and 't' object:\n");
    set_for_each(t, set_member_destroy, NULL);
    set_clear(s);
    set_clear(t);
    set_release(&s);
    set_release(&t);
    fprintf(stdout, "  show 's' set object:\n");
    set_object(s);
    fprintf(stdout, "  show 't' set object:\n");
    set_object(t);
  }
}
