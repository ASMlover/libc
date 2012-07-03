/*
 * Copyright (c) 2012 ASMlove. All rights reserved.
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
#include "../inc/atom.h"

#include "test.h"


void test_atom(void)
{
  char* s = "test_atom";
  char* v;
  fprintf(stdout, "call function : %s\n", __func__);

  fprintf(stdout, "test function atom_new ===>\n");
  v = (char*)atom_new(s, strlen(s));
  fprintf(stdout, "\tcall atom_new(s, strlen(s)) = %s\n", v);

  fprintf(stdout, "\ntest function atom_length ===>\n");
  fprintf(stdout, "\tcall atom_length(v) = %d\n", atom_length(v));

  fprintf(stdout, "\ntest function atom_int ===>\n");
  fprintf(stdout, "\tcall atom_int(100) = %s\n", atom_int(100));

  fprintf(stdout, "\ntest function atom_string ===>\n");
  fprintf(stdout, "\tcall atom_string(\"Hello, world!\") = %s\n", atom_string("Hello, world!"));
}
