#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void ssu_setbuf(FILE *fp, char *buf);

int main(int argc, char *argv[]) 
{
	char buf[BUFFER_SIZE];
	// char *fname = "/dev/pts/19"; // 터미널 번호, 리눅스용
	char *fname = "/dev/ttys001"; // 맥용
	FILE *fp;

	if ((fp = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	ssu_setbuf(fp, buf);
	fprintf(fp, "Hello, ");
	sleep(1);
	fprintf(fp, "UNIX!!");
	sleep(1);
	fprintf(fp, "\n");
	sleep(1);
	ssu_setbuf(fp, NULL);
	fprintf(fp, "HOW");
	sleep(1);
	fprintf(fp, " ARE");
	sleep(1);
	fprintf(fp, " YOU?");
	sleep(1);
	fprintf(fp, "\n");
	sleep(1);

	exit(0);
}

void ssu_setbuf(FILE *fp, char *buf) {
	size_t size;
	int fd;
	int mode;

	fd = fileno(fp); // fp -> fd
	
	if (isatty(fd)) // fd가 터미널인지 체크
		mode = _IOLBF;
	else
		mode = _IOFBF;

	if (buf == NULL) { // buf가 NULL이라면 버퍼링하지 않음
		mode = _IONBF;
		size = 0;
	}
	else
		size = BUFFER_SIZE;

	setvbuf(fp, buf, mode, size);
}
