CFLAGS=-std=c11 -g -static

99cc: 99cc.c

test: 99cc
		./test.sh

clean:
		rm -f 99cc *.o *~ tmp*

.PHONY: test clean