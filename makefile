BIN 	= libc.exe
CC 		= tcc
CFLAGS = -g -O2 -Wall
OBJS 	= main.o\
				\
				./test/test.o ./test/test_arith.o ./test/test_stack.o\
				./test/test_atom.o\
				\
				./src/error.o ./src/arith.o ./src/stack.o ./src/atom.o\
				./src/except.o
RM 		= rm

$(BIN): $(OBJS)
	$(CC) $^ -o $@

clean:
	$(RM) *.o ./src/*.o ./test/*.o $(BIN)
