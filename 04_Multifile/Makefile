CFLAGS = -Wall
GENERATES = prog README
TRASH = *.o *~ o.*

all: README prog

fun.o: outlib.h

prog: const.o fun.o prog.o

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)