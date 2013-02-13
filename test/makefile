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

BIN_OUT	= libc-test
BIN_DIR	= ../bin 
LIB_DIR	= ../lib
CC	= gcc
CFLAGS 	= -g -O2 -Wall
LDFLAGS	= -L$(LIB_DIR) -llibc
TEST_OBJS = main.o\
	\
	test.o test_arith.o test_stack.o test_atom.o test_except.o test_memory.o\
	test_memcheck.o test_arena.o test_list.o test_slist.o test_table.o\
	test_set.o test_array.o test_sequence.o test_ring.o test_bit.o\
	test_format.o test_string.o test_text.o
RM	= rm 
MD	= mkdir -p
RD	= rm -rf
CP 	= cp 


all: bin

bin: $(BIN_OUT)

rebuild: clean all

install:
	$(MD) $(BIN_DIR)
	$(CP) $(BIN_OUT) $(BIN_DIR)

uninstall:
	$(RD) $(BIN_DIR) 

clean:
	$(RM) $(TEST_OBJS) $(BIN_OUT) 




$(BIN_OUT): $(TEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(TEST_OBJS): %.o: %.c
	$(CC) -o $*.o -c $(CFLAGS) $^
