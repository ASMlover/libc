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
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/assert.h"
#include "../inc/config.h"
#include "../inc/format.h"

#include "test.h"




void test_format(void)
{
  fprintf(stdout, "call function : %s\n", __func__);

  format_printf("test function - format_printf ===>\n");
  format_fprintf(stdout, "test function - format_fprintf ===>\n");

  srand((unsigned int)time(0));
  format_fprintf(stdout, "\ntest function - format_sprintf ===>\n");
  {
    char buf[128];
    int  v = rand() % 1000;
    format_sprintf(buf, sizeof(buf), "the rand value is : %d\n", v);
    fprintf(stdout, "\t%s", buf);
  }

  fprintf(stdout, "\ntest function - format_string ===>\n");
  {
    char* s = format_string("format_string test --- rand value = %d\n", rand() % 2000);
    fprintf(stdout, "\t%s\n", s);
    free(s);
  }
}
