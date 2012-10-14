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
 *    notice, this list of conditions and the following disclaimer in
 *  * Redistributions in binary form must reproduce the above copyright
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
#include <string.h>
#include "../inc/text.h"

#include "test.h"




static void 
show_text_object(const char* name, void* T) 
{
  name = (NULL != name ? name : "Default");
  if (NULL != T) {
    fprintf(stdout, 
      "\t__text__ '%s' => {\n"
      "\t  object=>0x%p, \n"
      "\t  string=>'%s', \n"
      "\t  length=>%d, \n"
      "\t}\n", 
      name, T, text_str(T), text_len(T)
      );
  } else 
    fprintf(stdout, "\t__text__ => 0x%p\n", T);
}


void 
test_text(void) 
{
  fprintf(stdout, "call function : %s\n", __func__);

  fprintf(stdout, "test function - text_set ===>\n"); 
  {
    const char* s = "Hello, world!";
    void* T = text_set(s);

    show_text_object(NULL, T);
    text_free(&T);

    show_text_object(NULL, T);
  }

  fprintf(stdout, "test function - text_get ===>\n");
  {
    char buf[64] = {0};
    void* T = text_set("text_get");

    show_text_object(NULL, T);
    fprintf(stdout, "\tget => {str=>'%s'}\n", text_get(T, buf, 64));
    fprintf(stdout, "\tthe get string is : %s\n", buf);

    text_free(&T);
  }

  fprintf(stdout, "test function - text_box ===>\n");
  {
    char* s = "text_box";
    int   n = (int)strlen(s);

    void* T = text_box(s, n);
    show_text_object(NULL, T);

    text_free(&T);
  }

  fprintf(stdout, "test function - text_sub ===>\n");
  {
    char* s = "test_text=>{str=>text_sub}";
    void* T = text_set(s);
    void* sub;

    show_text_object(NULL, T);
    sub = text_sub(T, 1, 5);
    show_text_object(NULL, sub);
    text_free(sub);
    text_free(&T);
  }

  fprintf(stdout, "test function - text_pos ===>\n");
  {
    void* T = text_set("text=>{str=>text_pos}");

    show_text_object(NULL, T);
    fprintf(stdout, "\ttext pos is : %d\n", text_pos(T, -10));
    text_free(T);
  }

  fprintf(stdout, "test function - text operations ===>\n");
  {
    void* from = text_set("abcdefghijklmnopqrstuvwxyz");
    void* to = text_set("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    void* T1 = text_set("text1");
    void* T2 = text_set("text2");
    void* S;
    void* T;

    show_text_object("from", from);
    show_text_object("to", to);
    show_text_object("T1", T1);
    show_text_object("T2", T2);
    
    T = text_cat(T1, T2);
    show_text_object("T-text", T);

    S = text_dup(T, 2);
    show_text_object("dup", S);
    text_free(&S);

    S = text_reverse(T);
    show_text_object("reverse", S);
    text_free(&S);

    S = text_map(T, from, to);
    show_text_object("map", S);
    text_free(&S);

    text_free(&from);
    text_free(&to);
    text_free(&T);
    text_free(&T2);
    text_free(&T1);
  }

  fprintf(stdout, "test function - text operations ===>\n");
  {
    void* t1 = text_set("Hello1");
    void* t2 = text_set("Hello2");
    void* s1 = text_set("ell");

    show_text_object("t1", t1);
    show_text_object("t2", t2);
    show_text_object("s1", s1);
    fprintf(stdout, "\ttext_cmp => %d\n", text_cmp(t1, t2));
    fprintf(stdout, "\ttext_chr => %d\n", text_chr(t1, 1, 3, 'e'));
    fprintf(stdout, "\ttext_rchr => %d\n", text_rchr(t1, 1, 3, 'e'));
    fprintf(stdout, "\ttext_upto => %d\n", text_upto(t1, 1, 3, t2));
    fprintf(stdout, "\ttext_rupto => %d\n", text_rupto(t1, 1, 4, t2));
    fprintf(stdout, "\ttext_any => %d\n", text_any(t1, 2, t2));
    fprintf(stdout, "\ttext_many => %d\n", text_many(t1, 1, 4, t2));
    fprintf(stdout, "\ttext_rmany => %d\n", text_rmany(t1, 1, 3, t2));
    fprintf(stdout, "\ttext_find => %d\n", text_find(t1, 1, 5, s1));
    fprintf(stdout, "\ttext_rfind => %d\n", text_rfind(t1, 1, 5, s1));
    fprintf(stdout, "\ttext_match => %d\n", text_match(t1, 1, 4, s1));
    fprintf(stdout, "\ttext_rmantch => %d\n", text_rmatch(t1, 1, 5, s1));

    text_free(&s1);
    text_free(&t2);
    text_free(&t1);
  }
}
