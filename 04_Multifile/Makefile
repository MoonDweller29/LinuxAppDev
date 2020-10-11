CFLAGS = -Wall -fPIC
GENERATES = prog prog-a prog-so liboutput.so README
TRASH = *.o *~ o.* *.a test_run_*

all: test README prog prog-a prog-so

fun.o: outlib.h

prog: const.o fun.o prog.o

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

prog-a: prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o $@

liboutput.so: const.o fun.o
	cc -shared $^ -o $@

prog-so: prog.o liboutput.so
	cc -L. -Wl,-rpath,"./" prog.o -loutput -o $@

README: prog
	./$< 2> $@

test_run_%: %
	./$<                         2> $@_0.txt
	./$< 1st_arg                 2> $@_1.txt
	./$< 1st_arg 2nd_arg 3rd_arg 2> $@_2.txt

test: test_run_prog test_run_prog-so test_run_prog-a
	-cmp test_run_prog_0.txt test_run_prog-so_0.txt
	-cmp test_run_prog_1.txt test_run_prog-so_1.txt
	-cmp test_run_prog_2.txt test_run_prog-so_2.txt
	-cmp test_run_prog_0.txt test_run_prog-a_0.txt
	-cmp test_run_prog_1.txt test_run_prog-a_1.txt
	-cmp test_run_prog_2.txt test_run_prog-a_2.txt
	-cmp test_run_prog-a_0.txt test_run_prog-so_0.txt
	-cmp test_run_prog-a_1.txt test_run_prog-so_1.txt
	-cmp test_run_prog-a_2.txt test_run_prog-so_2.txt

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)