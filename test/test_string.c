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
#include <string.h>
#include <stdio.h>
#include "../inc/config.h"
#include "../inc/memory.h"
#include "../inc/string.h"

#include "test.h"



void 
test_string(void) 
{
  fprintf(stdout, "call function : %s\n", __func__);
  
  fprintf(stdout, "test function - string_sub ===>\n");
  {
    char* src = "string_sub";
    char* dest;

    dest = string_sub(src, 0, 5);
    fprintf(stdout, "\tstring_sub=>{src=>'%s', dest=>'%s'}\n", src, dest);
    FREE(dest);

    dest = string_sub(src, -1, -6);
    fprintf(stdout, "\tstring_sub=>{src=>'%s', dest=>'%s'}\n", src, dest);
    FREE(dest);

    dest = string_sub(src, 0, 0);
    fprintf(stdout, "\tstring_sub=>{src=>'%s', dest=>'%s'}\n", src, dest);
    FREE(dest);
  }

  fprintf(stdout, "\ntest function - string_dup ===>\n");
  {
    char* src = "string_dup";
    char* dest;

    dest = string_dup(src, 0, 5, 5);
    fprintf(stdout, "\tstring_dup=>{src=>'%s', dest=>'%s'}\n", src, dest);
    FREE(dest);
    
    dest = string_dup(src, 3, -6, 5);
    fprintf(stdout, "\tstring_dup=>{src=>'%s', dest=>'%s'}\n", src, dest);
    FREE(dest);
  }

  fprintf(stdout, "\ntest function - string_cat ===>\n");
  {
    char* src1 = "string_cat";
    char* src2 = "STRING_CAT";

    char* dest = string_cat(src1, 1, 3, src2, -2, -6);
    fprintf(stdout, "\tstring_cat=>{src1=>'%s', src2=>'%s', dest=>'%s'}\n", src1, src2, dest);
    FREE(dest);
  }

  fprintf(stdout, "\ntest function - string_vcat ===>\n");
  {
    char* dest = string_vcat("abc", 0, 2, "ABCDE", -1, -3, "***hello***", -2, -4, NULL);
    fprintf(stdout, "\tstring_vcat=>{dest=>'%s'}\n", dest);
    FREE(dest);
  }

  fprintf(stdout, "\ntest function - string_reverse ===>\n");
  {
    char* src = "string_reverse";
    char* dest = string_reverse(src, 0, 5);
    fprintf(stdout, "\tstring_reverse=>{src=>'%s', dest=>'%s'}\n", src, dest);
    FREE(dest);
  }

  fprintf(stdout, "\ntest function - string_map ===>\n");
  {
    char* src = "string_map";
    char* from = "abcdefghijklmnopqrstuvwxyz";
    char* to   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* dest = string_map(src, -1, -6, from, to);
    fprintf(stdout, "\tstirng_map=>{src=>'%s', from=>'%s', to=>'%s', dest=>'%s'}\n", 
        src, from, to, dest);
    FREE(dest);
  }

  fprintf(stdout, "\ntest function (posistion functions) ===>\n");
  {
    char* src = "posistion-functions(string module)";
    char* src1 = "abcdefg";
    char* src2 = "ABCDEFG";
    char* set = "string";
    fprintf(stdout, "\tstring_pos=>{i=>-5, pos=>%d}\n", string_pos(src, -5));
    fprintf(stdout, "\tstring_len=>{i=>0, j=>7, len=>%d}\n", string_len(src, 0, 7));
    fprintf(stdout, "\tstring_cmp=>{src1=>'%s', src2=>'%s', cmp_ret=>%d}\n", 
      src1, src2, string_cmp(src1, 0, 5, src2, 0, 5));
    fprintf(stdout, "\tstring_cmp=>{src1=>'%s', src1=>'%s', cmp_ret=>%d}\n", 
      src1, src1, string_cmp(src1, 0, 5, src1, 0, 5));
    fprintf(stdout, "\tstring_chr=>{i=>0, j=>1, c=>'s', pos=>%d}\n", string_chr(src, 0, 1, 's'));
    fprintf(stdout, "\tstring_rchr=>{i=>0, j=>1, c=>'s', pos=>%d}\n", string_rchr(src, 0, 1, 's'));
    fprintf(stdout, "\tstring_upto=>{i=>0, j=>1, set=>'%s', pos=>%d}\n", 
      set, string_upto(src, 0, 1, set));
    fprintf(stdout, "\tstring_rupto=>{i=>0, j=>1, set=>'%s', pos=>%d}\n", 
      set, string_rupto(src, 0, 1, set));
    fprintf(stdout, "\tstring_find=>{search=>'%s', pos=>%d}\n", set, string_find(src, 0, 1, set));
    fprintf(stdout, "\tstring_rfind=>{search=>'%s', pos=>%d}\n", set, string_rfind(src, 0, 1, set));
    fprintf(stdout, "\tstring_any=>{i=>5, set=>'%s', pos=>%d}\n", set, string_any(src, 5, set));
    fprintf(stdout, "\tstring_many=>{i=>0, j=>1, set=>'%s', pos=>%d}\n", 
      set, string_many(src, 0, 1, set));
    fprintf(stdout, "\tstring_rmany=>{i=>0, j=>1, set=>'%s', pos=>%d}\n", 
      set, string_rmany(src, 0, 1, set));
    fprintf(stdout, "\tstring_match=>{i=>0, j=>1, match=>'%s', pos=>%d}\n", 
      set, string_match(src, 0, 1, set));
    fprintf(stdout, "\tstring_rmatch=>{i=>0, j=>1, match=>'%s', pos=>%d}\n", 
      set, string_rmatch(src, 0, 1, set));
  }
}
