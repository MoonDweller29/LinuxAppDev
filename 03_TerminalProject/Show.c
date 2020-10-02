#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>

#define BUF_SIZE 10
#define DX 3

// enum key_code
// {
// 	KEY_RIGHT   =  261,
// 	KEY_LEFT    =  260,
// 	KEY_UP      =  259,
// 	KEY_DOWN    =  258,
// 	KEY_NPAGE   =  338,
// 	KEY_PPAGE   =  339,
// 	KEY_ESCAPE  =  27
// }
struct Text
{
	int line_count;
	char **lines;
};
typedef struct Text Text;

char *read_line(FILE *f, int *finished)
{
	*finished = 0;
	int buf_size = BUF_SIZE;
	char *line = (char*) malloc(buf_size);
	char c;
	
	int i = 0;
	while (((c=fgetc(f)) != '\n') && (c != EOF))
	{
		if (i >= buf_size)
		{
			buf_size += BUF_SIZE;
			line = (char *) realloc (line, buf_size);
		}
		line[i] = c;
		++i;
	}

	if(c == EOF){ *finished = 1; }

	if (i >= buf_size)
	{
		buf_size += 1;
		line = (char *) realloc (line, buf_size);
	}
	line[i] = '\0';

	return line;
}

Text read_file(const char *filename)
{
	Text text;
	FILE *f = fopen(filename, "r");
	if (f == NULL)
	{
		fprintf(stderr,"no file with name %s\n", filename);
		text.line_count = -1;
		return text;
	}
	int buf_size = BUF_SIZE;
	char **lines = (char **) malloc(buf_size*sizeof(char*));
	int eof_reached = 0;

	int i = 0;
	while (!eof_reached)
	{
		if (i >= buf_size)
		{
			buf_size += BUF_SIZE;
			char **lines = (char **) realloc(lines, buf_size*sizeof(char*));
		}
		lines[i] = read_line(f, &eof_reached);
		++i;
	}
	text.line_count = i;
	text.lines = lines;
	
	fclose(f);

	return text;
}

void free_text(Text text)
{
	for (int i = 0; i < text.line_count; ++i)
	{
		free(text.lines[i]);
	}
	free(text.lines);
}

void w_add_nchars(WINDOW *win, const char *str, uint32_t n)
{
	for (int i = 0; (i < n) && (str[i] != '\0'); ++i)
	{
		waddch(win, str[i]);
	}
}

void draw_text(Text text, const char *filename)
{
    WINDOW *win;
    int c = 0;

    initscr();

    noecho();
    cbreak();
    printw("File: %s; line count: %d;", filename, text.line_count); //title
    refresh();

    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    
    //hide cursor
    curs_set(0);

    do {
        box(win, 0, 0);
    	wmove (win, 1, 1);
     //    waddstr (win, "Hello, World!");
        // waddch(win, 'K');
        // w_add_nchars(win, "HELLO", 10);
        w_add_nchars(win, text.lines[0], 10);
        waddch(win, '\n');
        // wprintw(win, "  Key: %d, Name: %s\n", c, keyname(c));
        wrefresh(win);
    } while((c = wgetch(win)) != 27);

    endwin();
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr,"to few args\n");
		fprintf(stderr,"filename is required\n");
		return -1;
	}

	Text text = read_file(argv[1]);
	if (text.line_count < 0)
	{
		return -1;
	}

	draw_text(text, argv[1]);

    free_text(text);
}