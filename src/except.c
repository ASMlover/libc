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
#if _WIN32 || _WIN64
  #include <windows.h>
#endif
#include "../inc/assert.h"

#include "../inc/except.h"


struct lExceptFrame* lexcept_stack = NULL;

void except_raise(const struct lExcept* e, const char* file, int line)
{
#if _WIN32 || _WIN64
  struct lExceptFrame* ef;
  if (-1 == lexcept_index)
    except_init();
  ef = TlsGetValue(lexcept_index);
#else
  struct lExceptFrame* ef = lexcept_stack;
#endif

  assert(e);
  if (NULL == ef)
  {
    fprintf(stderr, "Uncaught exception");
    if (NULL != e->reason)
      fprintf(stderr, "  %s", e->reason);
    else 
      fprintf(stderr, "  at 0x%p", e);
    if (NULL != file && line > 0)
      fprintf(stderr, "  raised at %s:%d\n", file, line);
    fprintf(stderr, "aborting ...\n");
    fflush(stderr);
    abort();
  }
  ef->exception = (struct lExcept*)e;
  ef->file      = file;
  ef->line      = line;

#if _WIN32 || _WIN64
  except_pop();
#else
  lexcept_stack = lexcept_stack->prev;
#endif

  longjmp(ef->env, EXCEPT_RAISED);
}


#if _WIN32 || _WIN64
  #ifndef _CRT_WIDE
    #define __CRT_WIDE(_String) L ## _String
    #define _CRT_WIDE(_String) __CRT_WIDE(_String)
  #endif
  
  #if _UNICODE || UNICODE
    _CRTIMP void __cdecl _wassert(const wchar_t*, const wchar_t*, unsigned int);
  #else
    _CRTIMP void __cdecl _assert(const char*, const char*, unsigned int);
  #endif

  #undef assert

  #if _UNICODE || UNICODE
    #define assert(e) ((e) || (_wassert(_CRT_WIDE(#e), _CRT_WIDE(__FILE__), __LINE__), 0))
  #else
    #define assert(e) ((e) || (_assert((#e), __FILE__, __LINE__), 0))
  #endif

int lexcept_index = -1;
void except_init(void)
{
  BOOL cond;

  lexcept_index = TlsAlloc();
  assert(TLS_OUT_OF_INDEXES != lexcept_index);
  cond = TlsSetValue(lexcept_index, NULL);
  assert(TRUE == cond);
}

void except_push(struct lExceptFrame* ef)
{
  BOOL cond;

  ef->prev = TlsGetValue(lexcept_index);
  cond = TlsSetValue(lexcept_index, ef);
  assert(TRUE == cond);
}

void except_pop(void)
{
  struct lExceptFrame* ef = TlsGetValue(lexcept_index);
  BOOL cond;

  cond = TlsSetValue(lexcept_index, ef->prev);
  assert(TRUE == cond);
}

#endif
