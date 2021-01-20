#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int charcter;

	while ((charcter = getc(stdin)) != EOF) {
		if (putc(charcter, stdout) == EOF) {
			fprintf(stderr, "standard output error\n");
			exit(1);
		}
	}

	if (ferror(stdin)) { // tests the error indicator for the stream pointed to by stream, return non-zero if it is set.
		fprintf(stderr, "standard input error\n");
		exit(1);
	}

	exit(0);
}
