BIN_OUT	= libc-test
BIN_DIR	= bin 
CC 			= gcc
CFLAGS 	= -g -O2 -Wall
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


all: $(BIN_OUT)

rebuild: clean $(BIN_OUT)

install:
	$(MD) $(BIN_DIR)
	$(CP) $(BIN_OUT) $(BIN_DIR)

uninstall:
	$(RD) $(BIN_DIR) 

clean:
	$(RM) $(LIBC_OBJS) $(TEST_OBJS) $(BIN_OUT) 



$(BIN_OUT): $(TEST_OBJS) $(LIBC_OBJS)
	$(CC) -o $@ $^ 

$(LIBC_OBJS): %.o: %.c
	$(CC) -o $*.o -c $(CFLAGS) $^

$(TEST_OBJS): %.o: %.c
	$(CC) -o $*.o -c $(CFLAGS) $^
