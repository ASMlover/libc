#ifndef __XP_HEADER_H__
#define __XP_HEADER_H__

typedef unsigned char* byte_t;

extern int xp_add(int digits, byte_t* z, byte_t* x, byte_t* y, int carry);
extern int xp_sub(int digits, byte_t* z, byte_t* x, byte_t* y, int borrow);
extern int xp_mul(byte_t* z, int n, byte_t* x, int m, byte_t* y);
extern int xp_div(int n, byte_t* q, byte_t* x, int m, byte_t* y, byte_t* r, byte_t* temp);

extern int xp_sum(int n, byte_t* z, byte_t* x, int y);
extern int xp_diff(int n, byte_t* z, byte_t* x, int y);
extern int xp_product(int n, byte_t* z, byte_t* x, int y);
extern int xp_quotient(int n, byte_t* z, byte_t* x, int y);

extern int xp_neg(int n, byte_t* z, byte_t* x, int carry);
extern int xp_cmp(int n, byte_t* x, byte_t* y);
extern void xp_lshift(int n, byte_t* z, int m, byte_t* x, int s, int fill);
extern void xp_rshift(int n, byte_t* z, int m, byte_t* x, int s, int fill);

extern int xp_length(int n, byte_t* x);
extern unsigned long xp_fromint(int n, byte_t* z, unsigned long u);
extern unsigned long xp_toint(int n, byte_t* x);

extern int xp_fromstr(int n, byte_t* z, const char* str, int base, char** end);
extern char* xp_tostr(char* str, int size, int base, int n, byte_t* x);

#endif  /* __XP_HEADER_H__ */
