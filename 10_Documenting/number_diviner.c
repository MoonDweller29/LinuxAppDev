#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

#define BUF_SIZE 10
#define WRONG_INPUT -1
#define YES 1
#define NO 0

int check_answer(const char* str) {
	if (strcmp(str, _("Yes")) == 0 ||
		strcmp(str, _("yes")) == 0 ||
		strcmp(str, _("Y"))   == 0 ||
		strcmp(str, _("y"))   == 0) {
		return YES;
	} else if (
		strcmp(str, _("No")) == 0 ||
		strcmp(str, _("no")) == 0 ||
		strcmp(str, _("N"))   == 0 ||
		strcmp(str, _("n"))   == 0) {
		return NO;
	}
	else {
		printf(_("wrong input\n"));
		return WRONG_INPUT;
	}
}

void read_to_buf(char buf[], int size) {
	int i = 0;
	int c = getchar();
	while (i < size-1 && c != '\n' && c != EOF) {
		buf[i] = c;
		
		++i;
		c = getchar();
	}
	buf[i] = '\0';
	if (i == size-1) {
		return;
	}
	if (c == EOF) {
		exit(0);
	}
	while(c != '\n' && c != EOF) {
		c = getchar();
	}
}

int bin_search(int low, int high) {
	char buf[BUF_SIZE];

	while (low < high) {
		int mid = (high - low)/2 + low;
		printf(_("Is the number higher than %d?\n"), mid);
		
		read_to_buf(buf, BUF_SIZE);
		int answer = check_answer(buf);
		while(answer == WRONG_INPUT) {
			read_to_buf(buf, BUF_SIZE);
			answer = check_answer(buf);
		}
		if (answer == YES) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}

	return low;
}

int main()
{
	setlocale (LC_ALL, "");
	bindtextdomain ("number_diviner", LOCALE_PATH);
	textdomain ("number_diviner");

	printf(_("Make a number from 1 to 100\n(don't tell it, just imagine and press Enter)\n"));
	int c = getchar();
	while ((c != '\n') && (c != EOF)) {
		c = getchar();
	}

	int x = bin_search(1, 100);
	printf(_("Your number is %d\n"), x);

	return 0;
}