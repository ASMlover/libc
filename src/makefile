LIB_OUT	= liblibc.a
LIB_DIR	= ../lib
CC	= gcc
AR	= ar
CFLAGS 	= -g -O2 -Wall
LDFLAGS	= -L$(LIB_DIR) -llibc
LIBC_OBJS	= error.o arith.o stack.o atom.o except.o assert.o memory.o\
						mem_check.o arena.o list.o slist.o table.o set.o array.o\
						sequence.o ring.o bit.o format.o string.o text.o xp.o
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
