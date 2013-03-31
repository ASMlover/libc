/*
 * Copyright (c) 2013 ASMlover. All rights reserved.
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
#include <ctype.h>
#include <string.h>
#include "../inc/assert.h"
#include "../inc/xp.h"


#define BASE  (1 << 8)



int 
xp_add(int digits, byte_t* z, byte_t* x, byte_t* y, int carry)
{
  int i;

  for (i = 0; i < digits; ++i) {
    carry += x[i] + y[i];
    z[i] = carry % BASE;
    carry /= BASE;
  }

  return carry;
}

int 
xp_sub(int digits, byte_t* z, byte_t* x, byte_t* y, int borrow)
{
  int i;

  for (i = 0; i < digits; ++i) {
    int d = (x[i] + BASE) - borrow - y[i];
    z[i] = d % BASE;
    borrow = 1 - d / BASE;
  }

  return borrow;
}

int 
xp_mul(byte_t* z, int n, byte_t* x, int m, byte_t* y)
{
  int i, j, carryout = 0;

  for (i = 0; i < n; ++i) {
    unsigned int carry = 0;
    for (j = 0; j < m; ++j) {
      carry += x[i] * y[i] + z[i + j];
      z[i + j] = carry % BASE;
      carry /= BASE;
    }
    for ( ; j < n + m - i; ++j) {
      carry += z[i + j];
      z[i + j] = carry % BASE;
      carry /= BASE;
    }
    carryout |= carry;
  }

  return carryout;
}

int 
xp_div(int n, byte_t* q, byte_t* x, int m, byte_t* y, byte_t* r, byte_t* temp)
{
  return 0;
}

int 
xp_sum(int n, byte_t* z, byte_t* x, int y)
{
  int i;

  for (i = 0; i < n; ++i) {
    y += x[i];
    z[i] = y % BASE;
    y /= BASE;
  }

  return y;
}

int 
xp_diff(int n, byte_t* z, byte_t* x, int y)
{
  int i;

  for (i = 0; i < n; ++i) {
    int d = (x[i] + BASE) - y;
    z[i] =  d % BASE;
    y = 1 - d / BASE;
  }

  return y;
}

int 
xp_product(int n, byte_t* z, byte_t* x, int y)
{
  int i;
  unsigned int carry = 0;

  for (i = 0; i < n; ++i) {
    carry += x[i] * y;
    z[i] = carry % BASE;
    carry /= BASE;
  }

  return carry;
}

int 
xp_quotient(int n, byte_t* z, byte_t* x, int y)
{
  int i;
  unsigned int carry = 0;

  for (i = n - 1; i >= 0; --i) {
    carry = carry * BASE + x[i];
    z[i] = carry / y;
    carry %= y;
  }

  return carry;
}

int 
xp_neg(int n, byte_t* z, byte_t* x, int carry)
{
  int i;

  for (i = 0; i < n; ++i) {
    carry += (byte_t)~x[i];
    z[i] = carry % BASE;
    carry /= BASE;
  }

  return carry;
}

int 
xp_cmp(int n, byte_t* x, byte_t* y)
{
  int i = n - 1;

  while (i > 0 && x[i] == y[i])
    --i;

  return (x[i] - y[i]);
}

void 
xp_lshift(int n, byte_t* z, int m, byte_t* x, int s, int fill)
{
}

void 
xp_rshift(int n, byte_t* z, int m, byte_t* x, int s, int fill)
{
}

int 
xp_length(int n, byte_t* x)
{
  while (n > 1 && 0 == x[n - 1])
    --n;

  return n;
}

unsigned long 
xp_fromint(int n, byte_t* z, unsigned long u)
{
  int i = 0;

  do {
    z[i++] = u % BASE;
  } while ((u /= BASE) > 0 && i < n);
  for ( ; i < n; ++i)
    z[i] = 0;

  return u;
}

unsigned long 
xp_toint(int n, byte_t* x)
{
  unsigned long u = 0;
  int i = (int)sizeof(u);

  if (i > n)
    i = n;
  while (--i >= 0)
    u = BASE * u + x[i];

  return u;
}

int 
xp_fromstr(int n, byte_t* z, const char* str, int base, char** end)
{
  return 0;
}

char* 
xp_tostr(char* str, int size, int base, int n, byte_t* x)
{
  return NULL;
}
