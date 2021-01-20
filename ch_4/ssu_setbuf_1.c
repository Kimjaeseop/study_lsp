#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void) 
{
	char buf[BUFFER_SIZE];

	setbuf(stdout, buf); // buf 사이즈만큼 버퍼링
	printf("Hello, ");
	sleep(1);
	
	printf("OSLAB!!");
	sleep(1);

	printf("\n");
	
	setbuf(stdout, NULL); // 버퍼 사용 X, 버퍼링 된 문자열 출력
	printf("How");
	sleep(1);
	printf(" are");
	sleep(1);
	printf(" you?");
	sleep(1);
	printf("\n");

	exit(0);
}
