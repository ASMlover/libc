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




void* 
text_set(const char* str)
{
  return NULL;
}

char* 
text_get(void* T, char* str, int len)
{
  return NULL;
}

void* 
text_box(const char* str, int len)
{
  return NULL;
}


/**!< text operations */
void* 
text_sub(void* T, int i, int j)
{
  return NULL;
}

int 
text_pos(void* T, int i)
{
  return 0;
}

void* 
text_cat(void* T1, void* T2)
{
  return NULL;
}

void* 
text_dup(void* T, int len)
{
  return NULL;
}

void* 
text_reverse(void* T)
{
  return NULL;
}

void* 
text_map(void* T, const void* from, const void* to)
{
  return NULL;
}


/**!< compare */
int 
text_cmp(void* T1, void* T2)
{
  return 0;
}

int 
text_chr(void* T, int i, int j, int c)
{
  return 0;
}

int 
text_rchr(void* T, int i, int j, int c)
{
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
  return NULL;
}

void 
text_restore(void* save)
{
}
