#ifndef __RING_HEADER_H__
#define __RING_HEADER_H__

extern void* ring_create(void);
extern void* ring_create_by(void* x, ...);
extern void ring_release(void** R);

extern int ring_size(void* R);
extern int ring_empty(void* R);
extern void ring_clear(void* R);

extern void* ring_push_front(void* R, void* x);
extern void* ring_push_back(void* R, void* x);
extern void* ring_pop_front(void* R);
extern void* ring_pop_back(void* R);
extern void* ring_insert(void* R, int i, void* x);
extern void* ring_erase(void* R, int i);

extern void* ring_get(void* R, int i);
extern void* ring_set(void* R, int i, void* x);

extern void ring_for_each(void* R, void (*visit)(void*, void*), void* arg);
extern void ring_rotate(void* R, int n);

#endif  /* __RING_HEADER_H__ */
