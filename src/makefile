# Copyright (c) 2013 ASMlover. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list ofconditions and the following disclaimer.
#
#    notice, this list of conditions and the following disclaimer in
#  * Redistributions in binary form must reproduce the above copyright
#    the documentation and/or other materialsprovided with the
#    distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

LIB_OUT	= liblibc.a
LIB_DIR	= ../lib
CC	= gcc
AR	= ar
CFLAGS 	= -g -O2 -Wall
LDFLAGS	= -L$(LIB_DIR) -llibc
LIBC_OBJS = error.o arith.o stack.o atom.o except.o assert.o memory.o\
	mem_check.o arena.o list.o slist.o table.o set.o array.o sequence.o\
	ring.o bit.o format.o string.o text.o xp.o
RM	= rm 
MD	= mkdir -p
RD	= rm -rf
CP 	= cp 


all: lib

lib: $(LIB_OUT)

rebuild: clean all

install:
	$(MD) $(LIB_DIR)
	$(CP) $(LIB_OUT) $(LIB_DIR)

uninstall:
	$(RD) $(LIB_DIR)

clean:
	$(RM) $(LIBC_OBJS) $(LIB_OUT)




$(LIB_OUT): $(LIBC_OBJS)
	$(AR) -cru $@ $^

$(LIBC_OBJS): %.o: %.c
	$(CC) -o $*.o -c $(CFLAGS) $^
