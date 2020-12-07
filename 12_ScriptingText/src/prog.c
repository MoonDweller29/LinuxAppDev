/* COMMENT: "prog 0.0.1 Mon Dec  7 23:12:39 MSK 2020" */
#include <stdio.h>
#include "outlib.h"

int main(int argc, char *argv[]) {
	int i;
	Count = 0;
    if(argc > 1) {
		output("<INIT>");
		for(i=1; i<argc; i++)
			output(argv[i]);
		output("<DONE>");
	}
	else
		usage(argv[0]);

	return 0;
}