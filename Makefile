CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

99cc: $(OBJS)
		$(CC) -o 99cc $(OBJS) $(LDFLAGS)

$(OBJS): 99cc.h

test: 99cc
		./test.sh

clean:
		rm -f 99cc *.o *~ tmp*

.PHONY: test clean
