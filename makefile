BIN 	= libc.exe
CC 		= gcc
CFLAGS = -g -O2 -Wall
OBJS 	= main.o\
				\
				./test/test.o ./test/test_arith.o ./test/test_stack.o\
				./test/test_atom.o ./test/test_except.o ./test/test_memory.o\
				./test/test_memcheck.o ./test/test_arena.o ./test/test_list.o\
				./test/test_slist.o ./test/test_table.o ./test/test_set.o\
				./test/test_array.o ./test/test_sequence.o ./test/test_ring.o\
				\
				./src/error.o ./src/arith.o ./src/stack.o ./src/atom.o\
				./src/except.o ./src/assert.o ./src/memory.o ./src/mem_check.o\
				./src/arena.o ./src/list.o ./src/slist.o ./src/table.o\
				./src/set.o ./src/array.o ./src/sequence.o ./src/ring.o
RM 		= rm

$(BIN): $(OBJS)
	$(CC) $^ -o $@

clean:
	$(RM) *.o ./src/*.o ./test/*.o $(BIN)
