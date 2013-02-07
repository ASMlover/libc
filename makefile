BIN_OUT	= libc-test
BIN_DIR	= bin 
LIB_OUT	= liblibc.a
LIB_DIR	= lib
CC	= gcc
AR	= ar
CFLAGS 	= -g -O2 -Wall
LDFLAGS	= -L$(LIB_DIR) -llibc
LIBC_OBJS	= ./src/error.o ./src/arith.o ./src/stack.o ./src/atom.o\
						./src/except.o ./src/assert.o ./src/memory.o ./src/mem_check.o\
						./src/arena.o ./src/list.o ./src/slist.o ./src/table.o\
						./src/set.o ./src/array.o ./src/sequence.o ./src/ring.o\
						./src/bit.o ./src/format.o ./src/string.o ./src/text.o\
						./src/xp.o
TEST_OBJS	= main.o\
						\
						./test/test.o ./test/test_arith.o ./test/test_stack.o\
						./test/test_atom.o ./test/test_except.o ./test/test_memory.o\
						./test/test_memcheck.o ./test/test_arena.o ./test/test_list.o\
						./test/test_slist.o ./test/test_table.o ./test/test_set.o\
						./test/test_array.o ./test/test_sequence.o ./test/test_ring.o\
						./test/test_bit.o ./test/test_format.o ./test/test_string.o\
						./test/test_text.o
RM	= rm 
MD	= mkdir -p
RD	= rm -rf
CP 	= cp 


all: lib install-lib $(BIN_OUT) 

lib: $(LIB_OUT)

rebuild: clean all

install:
	$(MD) $(BIN_DIR)
	$(CP) $(BIN_OUT) $(BIN_DIR)

install-lib:
	$(MD) $(LIB_DIR)
	$(CP) $(LIB_OUT) $(LIB_DIR)

uninstall: uninstall-bin uninstall-lib

uninstall-bin:
	$(RD) $(BIN_DIR) 

uninstall-lib:
	$(RD) $(LIB_DIR)

clean: clean-bin clean-lib

clean-bin:
	$(RM) $(TEST_OBJS) $(BIN_OUT) 

clean-lib:
	$(RM) $(LIBC_OBJS) $(LIB_OUT)




$(BIN_OUT): $(TEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(LIB_OUT): $(LIBC_OBJS)
	$(AR) -cru $@ $^

$(LIBC_OBJS): %.o: %.c
	$(CC) -o $*.o -c $(CFLAGS) $^

$(TEST_OBJS): %.o: %.c
	$(CC) -o $*.o -c $(CFLAGS) $^
