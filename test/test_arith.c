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
#include "test.h"
#include "../inc/arith.h"


void test_arith(void)
{
  fprintf(stdout, "call function : %s\n", __func__);

  fprintf(stdout, "test function arith_max ===>\n");
  fprintf(stdout, "\tmax(13, 3) = %d\n", arith_max(13, 3));
  fprintf(stdout, "\tmax(3, 13) = %d\n", arith_max(3, 13));
  fprintf(stdout, "\tmax(-3, -13) = %d\n", arith_max(-3, -13));
  fprintf(stdout, "\tmax(-13, -3) = %d\n", arith_max(-13, -3));
  fprintf(stdout, "\tmax(-3, 2) = %d\n", arith_max(-3, 2));
  fprintf(stdout, "\tmax(2, -3) = %d\n", arith_max(2, -3));

  fprintf(stdout, "test function arith_min ===>\n");
  fprintf(stdout, "\tmin(13, 3) = %d\n", arith_min(13, 3));
  fprintf(stdout, "\tmin(3, 13) = %d\n", arith_min(3, 13));
  fprintf(stdout, "\tmin(-3, -13) = %d\n", arith_min(-3, -13));
  fprintf(stdout, "\tmin(-13, -3) = %d\n", arith_min(-13, -3));
  fprintf(stdout, "\tmin(-3, 2) = %d\n", arith_min(-3, 2));
  fprintf(stdout, "\tmin(2, -3) = %d\n", arith_min(2, -3));

  fprintf(stdout, "test function arith_div ===>\n");
  fprintf(stdout, "\t13 / 5 = %d\n", arith_div(13, 5));
  fprintf(stdout, "\t5 / 13 = %d\n", arith_div(5, 13));
  fprintf(stdout, "\t-13 / 5 = %d\n", arith_div(-13, 5));
  fprintf(stdout, "\t-13 / -5 = %d\n", arith_div(-13, -5));
  fprintf(stdout, "\t13 / -5 = %d\n", arith_div(13, -5));
  fprintf(stdout, "\t-5 / 13 = %d\n", arith_div(-5, 13));
  fprintf(stdout, "\t-5 / -13 = %d\n", arith_div(-5, -13));
  fprintf(stdout, "\t0 / 14 = %d\n", arith_div(0, 14));
  fprintf(stdout, "\t0 / -14 = %d\n", arith_div(0, -14));
  // fprintf(stdout, "\t13 / 0 = %d\n", arith_div(13, 0));
  
  fprintf(stdout, "test function arith_mod ===>\n");
  fprintf(stdout, "\t13 %% 5 = %d\n", arith_mod(13, 5));
  fprintf(stdout, "\t5 %% 13 = %d\n", arith_mod(5, 13));
  fprintf(stdout, "\t-13 %% 5 = %d\n", arith_mod(-13, 5));
  fprintf(stdout, "\t-5 %% 13 = %d\n", arith_mod(-5, 13));
  fprintf(stdout, "\t13 %% -5 = %d\n", arith_mod(13, -5));
  fprintf(stdout, "\t5 %% -13 = %d\n", arith_mod(5, -13));
  fprintf(stdout, "\t-13 %% -5 = %d\n", arith_mod(-13, -5));
  fprintf(stdout, "\t-5 %% -13 = %d\n", arith_mod(-5, -13));
  fprintf(stdout, "\t0 %% 5 = %d\n", arith_mod(0, 5));
  fprintf(stdout, "\t0 %% -5 = %d\n", arith_mod(0, -5));
  // fprintf(stdout, "\t5 %% 0 == %d\n", arith_mod(5, 0));

  fprintf(stdout, "test function arith_floor as function arith_div ===>\n");

  fprintf(stdout, "test function arith_ceiling ===>\n");
  fprintf(stdout, "\tceiling(13, 5) = %d\n", arith_ceiling(13, 5));
  fprintf(stdout, "\tceiling(5, 13) = %d\n", arith_ceiling(5, 13));
  fprintf(stdout, "\tceiling(-13, 5) = %d\n", arith_ceiling(-13, 5));
  fprintf(stdout, "\tceiling(-5, 13) = %d\n", arith_ceiling(-5, 13));
  fprintf(stdout, "\tceiling(13, -5) = %d\n", arith_ceiling(13, -5));
  fprintf(stdout, "\tceiling(5, -13) = %d\n", arith_ceiling(5, -13));
  fprintf(stdout, "\tceiling(-13, -5) = %d\n", arith_ceiling(-13, -5));
  fprintf(stdout, "\tceiling(-5, -13) = %d\n", arith_ceiling(-5, -13));
  fprintf(stdout, "\tceiling(0, 5) = %d\n", arith_ceiling(0, 5));
  fprintf(stdout, "\tceiling(0, -5) = %d\n", arith_ceiling(0, -5));
  // fprintf(stdout, "\tceiling(5, 0) = %d\n", arith_ceiling(5, 0));
}
