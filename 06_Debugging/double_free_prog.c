#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 100

int main()
{
	char *buf = (char*) malloc(BUF_SIZE);
	for (int i = 0; i < 5; ++i)
	{
		sprintf(buf, "i = %d", i);
		printf("%s\n", buf);
	}
	free(buf);
	free(buf);

	printf("Finished without errors\n");

	return 0;
}