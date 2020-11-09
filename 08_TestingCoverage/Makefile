TESTS_BIN = tests_bin
TESTS = $(TESTS_BIN)/clear $(TESTS_BIN)/grow $(TESTS_BIN)/init $(TESTS_BIN)/pop $(TESTS_BIN)/push

$(TESTS_BIN)/%.c: tests/%.ts
	checkmk $< > $@

$(TESTS_BIN)/%: $(TESTS_BIN)/%.c libbuf.so $(TESTS_BIN)
	gcc `pkg-config --cflags check` -I. $< -o $@ `pkg-config --libs check` -L. -lbuf


all: libbuf.so $(TESTS)

libbuf.so: buf.c buf.h
	gcc -Wall -shared -fPIC $< -o $@

$(TESTS_BIN):
	mkdir -p $@

check:
	-LD_LIBRARY_PATH=./ ./$(TESTS_BIN)/clear
	-LD_LIBRARY_PATH=./ ./$(TESTS_BIN)/grow
	-LD_LIBRARY_PATH=./ ./$(TESTS_BIN)/init
	-LD_LIBRARY_PATH=./ ./$(TESTS_BIN)/pop
	-LD_LIBRARY_PATH=./ ./$(TESTS_BIN)/push

clear:
	-rm -r $(TESTS_BIN)
	-rm libbuf.so