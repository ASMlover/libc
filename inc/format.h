#ifndef __FORMAT_HEADER_H__
#define __FORMAT_HEADER_H__

#include <stdio.h>
#include <stdarg.h>

typedef void (*format_callback_t)(int code, va_list* app, 
  int (*visit)(int c, void* arg), void* arg, 
  unsigned char flags[256], int width, int precision);

extern format_callback_t format_register(int code, format_callback_t cb);

extern void format_fmt(int (*visit)(int, void*), void* arg, const char* fmt, ...);
extern void format_vfmt(int (*visit)(int, void*), void* arg, const char* fmt, va_list ap);
extern void format_printf(const char* fmt, ...);
extern void format_fprintf(FILE* stream, const char* fmt, ...);
extern int format_sprintf(char* dest, int count, const char* fmt, ...);
extern int format_vsprintf(char* dest, int count, const char* fmt, va_list ap);
extern char* format_string(const char* fmt, ...);
extern char* format_vstring(const char* fmt, va_list ap);

extern void format_putd(const char* s, int len, int (*visit)(int, void*), 
    void* arg, unsigned char flags[256], int width, int precision);
extern void format_puts(const char* s, int len, int (*visit)(int, void*), 
    void* arg, unsigned char flags[256], int width, int precision);

#endif  /* __FORMAT_HEADER_H__ */
