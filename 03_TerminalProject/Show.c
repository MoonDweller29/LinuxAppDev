#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 10
#define DX 3
int TAB_SIZE = 4;

#define MIN(X, Y) X < Y ? X : Y
#define MAX(X, Y) X < Y ? Y : X


enum key_code
{
// 	KEY_RIGHT   =  261,
// 	KEY_LEFT    =  260,
// 	KEY_UP      =  259,
// 	KEY_DOWN    =  258,
// 	KEY_NPAGE   =  338,
// 	KEY_PPAGE   =  339,
	KEY_SPACE   =  32,
	KEY_ESC     =  27
};

struct Text
{
	int line_count;
	int max_line_len;
	char **lines;
};
typedef struct Text Text;

struct Page
{
	int first_line;
	int last_line;
	int height;
	int horizontal_offs;
};
typedef struct Page Page;

char *read_line(FILE *f, int *finished, int *line_len)
{
	*finished = 0;
	int buf_size = BUF_SIZE;
	char *line = (char*) malloc(buf_size);
	char c;
	
	int i = 0;
	while (((c=fgetc(f)) != '\n') && (c != EOF))
	{
		int repeat = 1;
		if (c == '\t')
		{
			repeat = TAB_SIZE;
			c = ' ';
		}
		for (int j = 0; j < repeat; ++j)
		{
			if (i >= buf_size)
			{
				buf_size += BUF_SIZE;
				line = (char *) realloc (line, buf_size);
			}
			line[i] = c;
			++i;
		}
	}

	if(c == EOF){ *finished = 1; }

	if (i >= buf_size)
	{
		buf_size += 1;
		line = (char *) realloc (line, buf_size);
	}
	line[i] = '\0';
	*line_len = i;

	return line;
}

Text read_file(const char *filename)
{
	Text text;
	text.max_line_len = 0;
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
			lines = (char **) realloc(lines, buf_size*sizeof(char*));
		}
		int curr_line_len;
		lines[i] = read_line(f, &eof_reached, &curr_line_len);
		text.max_line_len = MAX(curr_line_len, text.max_line_len);
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

Page create_page(int first_line, int line_count, int text_line_count, int horizontal_offs)
{
	Page page;
	page.height = line_count;
	page.first_line = MIN(first_line, text_line_count-1);
	page.last_line = MIN(first_line + line_count -1, text_line_count-1);
	page.horizontal_offs = horizontal_offs;

	return page;
}

WINDOW *dbg_win;
Page page_up(Page page, int line_shift)
{
	int actual_shift = MIN(page.first_line, line_shift);
	page.first_line -= actual_shift;
	page.last_line -= actual_shift;

	return page;
}

Page page_down(Page page, int line_shift, int text_line_count)
{
	int actual_shift = MIN(line_shift, text_line_count-1 - page.last_line);
	page.first_line += actual_shift;
	page.last_line += actual_shift;

	return page;
}

Page page_left(Page page, int line_shift)
{
	page.horizontal_offs = MAX(0, page.horizontal_offs - line_shift);

	return page;
}

Page page_right(Page page, int line_shift, int max_line_len)
{
	page.horizontal_offs = MIN(page.horizontal_offs + line_shift, max_line_len - 1);

	return page;
}

void wput_text_line(WINDOW *win, Text text, int i, int horizontal_offs, int win_width)
{
	char line_start[10];
	sprintf(line_start, " %3d: ", i+1);
	wprintw(win, "%s", line_start);
	int rest_width = win_width -1 - strlen(line_start);
	if (horizontal_offs < strlen(text.lines[i]))
		w_add_nchars(win, text.lines[i] + horizontal_offs, rest_width);
	waddch(win, '\n');
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

	int WIN_WIDTH = COLS-2*DX;
	int WIN_HEIGHT = LINES-2*DX;
	win = newwin(WIN_HEIGHT, WIN_WIDTH, DX, DX);
	dbg_win = win;
	keypad(win, TRUE);
	// scrollok(win, TRUE);
	
	//hide cursor
	curs_set(0);

	Page page = create_page(0, WIN_HEIGHT-2, text.line_count, 0);
	
	do {
		werase(win);
		wmove (win, 1, 0);

		switch (c)
		{
			case KEY_UP:
				page = page_up(page, 1);
				break;
			case KEY_DOWN:
			case KEY_SPACE:
				page = page_down(page, 1, text.line_count);
				break;
			case KEY_RIGHT:
				page = page_right(page, 1, text.max_line_len);
				break;
			case KEY_LEFT:
				page = page_left(page, 1);
				break;
			case KEY_NPAGE:
				page = page_down(page, WIN_HEIGHT-2, text.line_count);
				break;
			case KEY_PPAGE:
				page = page_up(page, WIN_HEIGHT-2);
				break;
			default:
				break;
		}

		for (int i = page.first_line; i <= page.last_line; ++i)
		{
			wput_text_line(win, text, i, page.horizontal_offs, WIN_WIDTH);
		}
		// wprintw(win, "  Key: %d, Name: %s\n", c, keyname(c));

		box(win, 0, 0);
		wrefresh(win);
		
		move(LINES-DX+1,0);
		printw(" Column: %3d", page.horizontal_offs + 1);
		refresh();
	} while((c = wgetch(win)) != KEY_ESC);

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