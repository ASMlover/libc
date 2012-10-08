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
#include <string.h>
#include <limits.h>
#include "../inc/config.h"
#include "../inc/assert.h"
#include "../inc/memory.h"
#include "../inc/format.h"

#include "../inc/text.h"




#define INDEX(i, len)   ((i) <= 0? (i) + (len) : (i) - 1)
#define ISATEND(t, n)\
  ((t)->str + (t)->len == g_current->avail && g_current->avail + (n) <= g_current->limit)
#define EQUAL(t, i, j)\
  (0 == memcmp(&(t)->str[i], (t)->str, (t)->len))



struct lText {
  int len;
  const char* str;
};

struct lChunk {
  struct lChunk* next;
  char* avail;
  char* limit;
};

struct lTextSave {
  struct lChunk* current;
  char* avail;
};


static char g_sets[] = 
  "\000\001\002\003\004\005\006\007\010\011\012\013\014\015\016\017"
  "\020\021\022\023\024\025\026\027\030\031\032\033\034\035\036\037"
  "\040\041\042\043\044\045\046\047\050\051\052\053\054\055\056\057"
  "\060\061\062\063\064\065\066\067\070\071\072\073\074\075\076\077"
  "\100\101\102\103\104\105\106\107\110\111\112\113\114\115\116\117"
  "\120\121\122\123\124\125\126\127\130\131\132\133\134\135\136\137"
  "\140\141\142\143\144\145\146\147\150\151\152\153\154\155\156\157"
  "\160\161\162\163\164\165\166\167\170\171\172\173\174\175\176\177"
  "\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217"
  "\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237"
  "\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257"
  "\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277"
  "\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317"
  "\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337"
  "\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357"
  "\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377";

static const struct lText g_text_sets   = {256, g_sets};
static const struct lText g_text_ascii  = {127, g_sets};
static const struct lText g_text_ucase  = {26, g_sets + 'A'};
static const struct lText g_text_lcase  = {26, g_sets + 'a'};
static const struct lText g_text_digits = {10, g_sets + '0'};
static const struct lText g_text_null   = {0, g_sets};


static struct lChunk  g_head = {NULL, NULL, NULL};
static struct lChunk* g_current = &g_head;

static char* 
alloc(int len)
{
  assert(len >= 0);

  if (g_current->avail + len > g_current->limit) {
    g_current = g_current->next = ALLOC(sizeof(*g_current) + 10240 + len);
    g_current->avail = (char*)(g_current + 1);
    g_current->limit = g_current->avail + 10240 + len;
    g_current->next  = NULL;
  }
  g_current->avail += len;
  return (g_current->avail - len);
}



void 
text_free(void** T)
{
  FREE(*T);
}

int 
text_len(void* P)
{
  struct lText* T = (struct lText*)P;
  assert(NULL != T);

  return (T->len);
}

const char* 
text_str(void* P)
{
  struct lText* T = (struct lText*)P;
  assert(NULL != T);

  return (T->str);
}



void* 
text_set(const char* str)
{
  struct lText* text;
  NEW0(text);

  assert(NULL != str);
  text->len = strlen(str);
  text->str = memcpy(alloc(text->len), str, text->len);

  return text;
}

char* 
text_get(void* P, char* str, int len)
{
  struct lText* T = (struct lText*)P;

  assert(NULL !=T && T->len >= 0 && NULL != T->str);
  if (NULL == str)
    str = ALLOC(T->len + 1);
  else 
    assert(len >= T->len + 1);
  memcpy(str, T->str, T->len);
  str[T->len] = '\0';

  return str;
}

void* 
text_box(const char* str, int len)
{
  struct lText* T;
  NEW0(T);

  assert(NULL != str && len >= 0);
  T->str = str;
  T->len = len;

  return T;
}


/**!< text operations */
void* 
text_sub(void* P, int i, int j)
{
  struct lText* text;
  struct lText* T = (struct lText*)P;
  NEW0(text);

  assert(NULL != T && T->len >= 0 && NULL != T->str);
  i = INDEX(i, T->len);
  j = INDEX(j, T->len);
  if (i > j) {
    int t = i;
    i = j;
    j = t;
  }
  assert(i >= 0 && j <= T->len);
  text->len = j - i;
  text->str = T->str + i;

  return text;
}

int 
text_pos(void* P, int i)
{
  struct lText* T = (struct lText*)P;
  assert(NULL != T && T->len >= 0 && NULL != T->str);
  i = INDEX(i, T->len);
  assert(i >= 0 && i <= T->len);

  return (i + 1);
}

void* 
text_cat(void* P1, void* P2)
{
  struct lText* text;
  struct lText* T1 = (struct lText*)P1;
  struct lText* T2 = (struct lText*)P2;

  assert(NULL != T1 && T1->len >= 0 && NULL != T1->str);
  assert(NULL != T2 && T2->len >= 0 && NULL != T2->str);
  if (0 == T1->len)
    return T2;
  if (0 == T2->len)
    return T1;
  if (T1->str + T1->len == T2->str) {
    T1->len += T2->len;
    return T1;
  }

  NEW0(text);
  text->len = T1->len + T2->len;
  if (ISATEND(T1, T2->len)) {
    text->str = T1->str;
    memcpy(alloc(T2->len), T2->str, T2->len);
  } else {
    char* p;
    text->str = p = alloc(T1->len + T2->len);
    memcpy(p, T1->str, T1->len);
    memcpy(p + T1->len, T2->str, T2->len);
  }

  return text;
}

void* 
text_dup(void* P, int n)
{
  char* p;
  struct lText* text;
  struct lText* T = (struct lText*)P;

  assert(NULL != T && T->len >= 0 && NULL != T->str && n >= 0);
  if (0 == n || 0 == T->len)
    return (void*)&g_text_null;
  if (1 == n)
    return T;

  NEW0(text);
  text->len = n * T->len;
  if (ISATEND(T, text->len - T->len)) {
    text->str = T->str;
    p = alloc(text->len - T->len);
    --n;
  } else 
    text->str = p = alloc(text->len);

  for ( ; n-- > 0; p += T->len)
    memcpy(p, T->str, T->len);

  return text;
}

void* 
text_reverse(void* P)
{
  struct lText* T = (struct lText*)P;
  assert(NULL != T && T->len >= 0 && NULL != T->str);
  if (0 == T->len)
    return (void*)&g_text_null;
  else if (1 == T->len)
    return T;
  else {
    struct lText* text;
    char* p;
    int i = T->len;

    NEW0(text);
    text->len = T->len;
    text->str = p = alloc(T->len);
    while (--i >= 0)
      *p++ = T->str[i];

    return text;
  }
}

void* 
text_map(void* P, const void* from_p, const void* to_p)
{
  static char map[256];
  static int inited = 0;

  struct lText* T = (struct lText*)P;
  struct lText* from = (struct lText*)from_p;
  struct lText* to   = (struct lText*)to_p;
  assert(NULL != T && T->len >= 0 && NULL != T->str);
  if (NULL != from && NULL != to) {
    int k;
    for (k = 0; k < (int)sizeof(map); ++k)
      map[k] = k;
    assert(from->len == to->len);
    for (k = 0; k < from->len; ++k)
      map[(unsigned char)from->str[k]] = to->str[k];
    inited = 1;
  } else {
    assert(NULL == from && NULL == to);
    assert(inited);
  }

  if (0 == T->len)
    return (void*)&g_text_null;
  else {
    struct lText* text;
    int i;
    char* p;

    NEW0(text);
    text->len = T->len;
    text->str = p = alloc(T->len);
    for (i = 0; i < T->len; ++i)
      *p++ = map[(unsigned char)T->str[i]];

    return text;
  }
}


/**!< compare */
int 
text_cmp(void* P1, void* P2)
{
  struct lText* T1 = (struct lText*)P1;
  struct lText* T2 = (struct lText*)P2;

  assert(NULL != T1 && T1->len >= 0 && NULL != T1->str);
  assert(NULL != T2 && T2->len >= 0 && NULL != T2->str);
  if (T1->str == T2->str)
    return (T1->len - T2->len);
  else if (T1->len < T2->len) {
    int cond = memcmp(T1->str, T2->str, T1->len);
    return (0 == cond ? -1 : cond);
  } else if (T1->len > T2->len) {
    int cond = memcmp(T1->str, T2->str, T2->len);
    return (0 == cond ? 1 : cond);
  } else 
    return memcmp(T1->str, T2->str, T1->len);
}

int 
text_chr(void* P, int i, int j, int c)
{
  struct lText* T = (struct lText*)P;

  assert(NULL != T && T->len >= 0 && NULL != T->str);
  i = INDEX(i, T->len);
  j = INDEX(j, T->len);
  if (i > j) {
    int t = i;
    i = j;
    j = t;
  }
  assert(i >= 0 && j <= T->len);
  for ( ; i < j; ++i) {
    if (c == T->str[i])
      return (i + 1);
  }

  return 0;
}

int 
text_rchr(void* P, int i, int j, int c)
{
  struct lText* T = (struct lText*)P;

  assert(NULL != T && T->len >= 0 && NULL != T->str);
  i = INDEX(i, T->len);
  j = INDEX(j, T->len);
  if (i > j) {
    int t = i;
    i = j;
    j = t;
  }
  assert(i >= 0 && j <= T->len);
  while (j > i) {
    if (c == T->str[--j])
      return (j + 1);
  }

  return 0;
}

int 
text_upto(void* T, int i, int j, void* set)
{
  return 0;
}

int 
text_rupto(void* T, int i, int j, void* set)
{
  return 0;
}

int 
text_any(void* T, int i, void* set)
{
  return 0;
}

int 
text_many(void* T, int i, int j, void* set)
{
  return 0;
}

int 
text_rmany(void* T, int i, int j, void* set)
{
  return 0;
}

int 
text_find(void* T, int i, int j, void* s)
{
  return 0;
}

int 
text_rfind(void* T, int i, int j, void* s)
{
  return 0;
}

int 
text_match(void* T, int i, int j, void* s)
{
  return 0;
}

int 
text_rmatch(void* T, int i, int j, void* s)
{
  return 0;
}

void 
text_fmt(int code, va_list* app, int (*visit)(int, void*), 
  void* arg, unsigned char flags[], int width, int precision)
{
}


void* 
text_save(void)
{
  struct lTextSave* save;
  NEW0(save);

  save->current = g_current;
  save->avail   = g_current->avail;
  alloc(1);

  return save;
}

void 
text_restore(void** p)
{
  struct lChunk* iter;
  struct lChunk* next;

  struct lTextSave** save = (struct lTextSave**)p;
  assert(NULL != save && NULL != *save);
  g_current = (*save)->current;
  g_current->avail = (*save)->avail;
  FREE(*save);
  for (iter = g_current->next; NULL != iter; iter = next) {
    next = iter->next;
    FREE(iter);
  }
  g_current->next = NULL;
}
