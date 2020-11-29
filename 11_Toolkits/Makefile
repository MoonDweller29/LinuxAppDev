TGT_NAME = word_freq.out

all: $(TGT_NAME)

$(TGT_NAME): word_freq.c
	gcc -g `pkg-config --cflags glib-2.0` $^ -o $@ `pkg-config --libs glib-2.0`
	 
clean:
	rm $(TGT_NAME)