#ifndef __BIT_HEADER_H__
#define __BIT_HEADER_H__

extern void* bit_create(int size);
extern void bit_release(void** B);

extern int bit_size(void* B);
extern int bit_count(void* B);  /**!< number of ones in bit set. */
extern void bit_clear(void* B);

extern int bit_set(void* B, int i, int val);
extern int bit_get(void* B, int i);

extern void bit_clear_range(void* B, int beg, int end);
extern void bit_set_range(void* B, int beg, int end);
extern void bit_not_range(void* B, int beg, int end);

extern int bit_lt(void* B1, void* B2);
extern int bit_eq(void* B1, void* B2);
extern int bit_leq(void* B1, void* B2);

extern void bit_for_each(void* B, void (*visit)(int, int, void*), void* arg);

extern void* bit_union(void* B1, void* B2);
extern void* bit_inter(void* B1, void* B2);
extern void* bit_minus(void* B1, void* B2);
extern void* bit_diff(void* B1, void* B2);

#endif  /* __BIT_HEADER_H__ */
