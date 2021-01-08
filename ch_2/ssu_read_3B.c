#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char c;
	int fd;
	int line_count;

	if ((fd = open("ssu_test.txt", O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", "ssu_test.txt");
		exit(1);
	}

	while (1) {
		if (read(fd, &c, 1) > 0) {
			if (c == '\n')
				line_count++;
		}
		else
			break;
	}

	printf("Total line : %d\n", line_count);
	exit(0);
}
