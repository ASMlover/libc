#include <float.h>
#include <ctype.h>
#include <math.h>
#include "../inc/except.h"
#include "../inc/assert.h"
#include "../inc/memory.h"

#include "../inc/format.h"


format_callback_t format_register(int code, format_callback_t convert)
{
  return NULL;
}

void format_fmt(int (*visit)(int, void*), void* arg, const char* fmt, ...)
{
}

void format_vfmt(int (*visit)(int, void*), void* arg, const char* fmt, va_list ap)
{
}

void format_printf(const char* fmt, ...)
{
}

void format_fprintf(FILE* stream, const char* fmt, ...)
{
}

int format_sprintf(char* dest, int count, const char* fmt, ...)
{
  return 0;
}

int format_vsprintf(char* dest, int count, const char* fmt, va_list ap)
{
  return 0;
}

char* format_string(const char* fmt, ...)
{
  return NULL;
}

char* format_vstring(const char* fmt, va_list ap)
{
  return NULL;
}

void format_putd(const char* s, int len, int (*visit)(int, void*), 
  void* arg, unsigned char flags[256], int width, int precision)
{
}

void format_puts(const char* s, int len, int (*visit)(int, void*), 
  void* arg, unsigned char flags[256], int width, int precision)
{
}
