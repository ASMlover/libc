BIN_OUT	= libc-test
BIN_DIR	= ../bin 
LIB_DIR	= ../lib
CC	= gcc
CFLAGS 	= -g -O2 -Wall
LDFLAGS	= -L$(LIB_DIR) -llibc
TEST_OBJS	= main.o\
						\
						test.o test_arith.o test_stack.o test_atom.o test_except.o\
						test_memory.o test_memcheck.o test_arena.o test_list.o\
						test_slist.o test_table.o test_set.o test_array.o\
						test_sequence.o test_ring.o test_bit.o test_format.o\
						test_string.o test_text.o
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
