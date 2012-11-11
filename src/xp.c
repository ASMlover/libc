#include <ctype.h>
#include <string.h>
#include "../inc/assert.h"
#include "../inc/xp.h"


#define BASE  (1 << 8)



int 
xp_add(int digits, byte_t* z, byte_t* x, byte_t* y, int carry)
{
  return 0;
}

int 
xp_sub(int digits, byte_t* z, byte_t* x, byte_t* y, int borrow)
{
  return 0;
}

int 
xp_mul(byte_t* z, int n, byte_t* x, int m, byte_t* y)
{
  return 0;
}

int 
xp_div(int n, byte_t* q, byte_t* x, int m, byte_t* y, byte_t* r, byte_t* temp)
{
  return 0;
}

int 
xp_sum(int n, byte_t* z, byte_t* x, int y)
{
  return 0;
}

int 
xp_diff(int n, byte_t* z, byte_t* x, int y)
{
  return 0;
}

int 
xp_product(int n, byte_t* z, byte_t* x, int y)
{
  return 0;
}

int 
xp_quotient(int n, byte_t* z, byte_t* x, int y)
{
  return 0;
}

int 
xp_neg(int n, byte_t* z, byte_t* x, int carry)
{
  return 0;
}

int 
xp_cmp(int n, byte_t* x, byte_t* y)
{
  return 0;
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
  return 0;
}

unsigned long 
xp_fromint(int n, byte_t* z, unsigned long u)
{
  return 0;
}

unsigned long 
xp_toint(int n, byte_t* x)
{
  return 0;
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
