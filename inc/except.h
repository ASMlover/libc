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
#ifndef __EXCEPT_HEADER_H__
#define __EXCEPT_HEADER_H__

#include <setjmp.h>

struct lExcept { const char* reason; };
struct lExceptFrame {
  struct lExceptFrame* prev;
  jmp_buf              env;
  const char*          file;
  int                  line;
  struct lExcept*      exception;
};
enum {
  EXCEPT_ENTERED    = 0, 
  EXCEPT_RAISED     = 1, 
  EXCEPT_HANDLED    = 2, 
  EXCEPT_FINALIZED  = 3, 
};
extern struct lExceptFrame* lexcept_stack;
extern const struct lExcept lassert_failed;
extern void except_raise(const struct lExcept* e, const char* file, int line);

#if _WIN32 || _WIN64
  extern int lexcept_index;
  extern void except_init(void);
  extern void except_push(struct lExceptFrame* ef);
  extern void except_pop(void);

  #define RAISE(e)  except_raise(&(e), __FILE__, __LINE__)
  #define RERAISE   except_raise(lexcept_frame.exception, lexcept_frame.file, lexcept_frame.line)
  #define RETURN    switch (except_pop, 0) default: return
  #define TRY do {\
    volatile int lexcept_flag;\
    struct lExceptFrame lexcept_frame;\
    if (-1 == lexcept_index)\
      except_init();\
    except_push(&lexcept_frame);\
    lexcept_flag = setjmp(lexcept_frame.env);\
    if (EXCEPT_ENTERED == lexcept_flag) {
  #define EXCEPT(e)\
      if (EXCEPT_ENTERED == lexcept_flag)\
        except_pop();\
    } else if (lexcept_frame.exception == &(e)) {\
      lexcept_flag = EXCEPT_HANDLED;
  #define ELSE\
      if (EXCEPT_ENTERED == lexcept_flag)\
        except_pop();\
    } else {\
      lexcept_flag = EXCEPT_HANDLED;
  #define FINALLY\
      if (EXCEPT_ENTERED == lexcept_flag)\
        except_pop();\
    } {\
      if (EXCEPT_ENTERED == lexcept_flag)\
        lexcept_flag = EXCEPT_FINALIZED;
  #define END_TRY\
      if (EXCEPT_ENTERED == lexcept_flag)\
        except_pop();\
    }\
    if (EXCEPT_RAISED == lexcept_flag)\
      RERAISE;\
  } while (0)
#else
  #define RAISE(e)  except_raise(&(e), __FILE__, __LINE__)
  #define RERAISE   except_raise(lexcept_frame.exception, lexcept_frame.file, lexcept_frame.line)
  #define RETURN    switch (lexcept_stack = lexcept_stack->prev, 0) default: return
  #define TRY do {\
    volatile int lexcept_flag;\
    struct lExceptFrame lexcept_frame;\
    lexcept_frame.prev = lexcept_stack;\
    lexcept_stack = &lexcept_frame;\
    lexcept_flag = setjmp(lexcept_frame.env);\
    if (EXCEPT_ENTERED == lexcept_flag) {
  #define EXCEPT(e)\
      if (EXCEPT_ENTERED == lexcept_flag)\
        lexcept_stack = lexcept_stack->prev;\
    } else if (lexcept_frame.exception == &(e)) {\
      lexcept_flag = EXCEPT_HANDLED;
  #define ELSE\
      if (EXCEPT_ENTERED == lexcept_flag)\
        lexcept_stack = lexcept_stack->prev;\
    } else {\
      lexcept_flag = EXCEPT_HANDLED;
  #define FINALLY\
      if (EXCEPT_ENTERED == lexcept_flag)\
        lexcept_stack = lexcept_stack->prev;\
    } {\
      if (EXCEPT_ENTERED == lexcept_flag)\
        lexcept_flag = EXCEPT_FINALIZED;
  #define END_TRY\
      if (EXCEPT_ENTERED == lexcept_flag)\
        lexcept_stack = lexcept_stack->prev;\
    }\
    if (EXCEPT_RAISED == lexcept_flag)\
      RERAISE;\
  } while (0)
#endif

#endif  /* __EXCEPT_HEADER_H__ */
