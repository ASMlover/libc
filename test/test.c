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
#include "test.h"


#define COUNTOF(x)  (sizeof(x) / sizeof(*x))

static void test_unknown(void)
{
  fprintf(stdout, 
          "Usage: libc [OPTION] ...\n"
          "Test c like library.\n\n"
          "  help       display this help and exit\n"
          "  arith      display testcases of arith\n"
          "  stack      display testcases of stack\n"
          "  atom       display testcases of atom\n"
          "  except     display testcases of exception\n"
          "  mem        display testcases of memory\n"
          "  memchk     display testcases of mem_check\n"
          "  arena      display testcases of arena\n"
          "  list       display testcases of list\n"
         );
}


typedef void (*func_callback)(void);

struct TestFunc {
  char* cmd;
  func_callback cb;
};

static struct TestFunc g_sFuncs[] = {
  { "unknown", test_unknown   }, 
  { "help",    test_unknown   }, 
  { "arith",   test_arith     }, 
  { "stack",   test_stack     }, 
  { "atom",    test_atom      }, 
  { "except",  test_except    }, 
  { "mem",     test_memory    }, 
  { "memchk",  test_memcheck  }, 
  { "arena",   test_arena     }, 
  { "list",    test_list      }, 
};


void test_main(const char* cmd)
{
  const char* s = (NULL != cmd ? cmd : "unknown");
  int i, called = 0;

  for (i = 0; i < COUNTOF(g_sFuncs); ++i)
  {
    if (0 == stricmp(s, g_sFuncs[i].cmd))
    {
      g_sFuncs[i].cb();
      called = 1;
      break;
    }
  }

  if (!called)
    test_unknown();
}
