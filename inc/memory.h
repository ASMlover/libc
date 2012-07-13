#ifndef __MEMORY_HEADER_H__
#define __MEMORY_HEADER_H__

#include "except.h"

extern const struct lExcept lmemory_failed;

extern void* memory_alloc(long bytes, const char* file, int line);
extern void* memory_calloc(long count, long elem_bytes, const char* file, int line);
extern void memory_free(void* ptr, const char* file, int line);
extern void* memory_realloc(void* ptr, long bytes, const char* file, int line);

#define ALLOC(bytes)                memory_alloc((bytes), __FILE__, __LINE__)
#define CALLOC(count, elem_bytes)   memory_calloc((count), (elem_bytes), __FILE__, __LINE__)
#define NEW(ptr)                    ((ptr) = ALLOC((long)sizeof(*(ptr))))
#define NEW0(ptr)                   ((ptr) = CALLOC(1, (long)sizeof(*(ptr))))
#define FREE(ptr)                   ((void)(memory_free((ptr), __FILE__, __LINE__), (ptr) = 0))
#define REALLOC(ptr, bytes)         memory_realloc((ptr), (bytes), __FILE__, __LINE__)

#endif  /* __MEMORY_HEADER_H__ */
