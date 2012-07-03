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
#include "../inc/error.h"
#include "../inc/arith.h"

#define IS_CLOSE2ZERO   (-2 == -13 / 5)

int arith_max(int x, int y)
{
  return x > y ? x : y;
}

int arith_min(int x, int y)
{
  return x < y ? x : y;
}

int arith_div(int x, int y)
{
  if (0 == y)
   error(__FILE__, __func__, __LINE__, Error_DividendIsZero);

  if (IS_CLOSE2ZERO && ((x < 0) != (y < 0)) && (0 != x % y))
    return x / y - 1;
  else
    return x / y;
}

int arith_mod(int x, int y)
{
  if (0 == y)
    error(__FILE__, __func__, __LINE__, Error_DividendIsZero);

  if (IS_CLOSE2ZERO && ((x < 0) != (y <0)) && (0 != x % y))
    return x % y + y;
  else
    return x % y;
}

int arith_floor(int x, int y)
{
  return arith_div(x, y);
}

int arith_ceiling(int x, int y)
{
  return arith_div(x, y) + (0 != x % y);
}
