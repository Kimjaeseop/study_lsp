#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

void ssu_signal_handler(int signo);

jmp_buf jump_buffer;

int main(void) 
{
	signal(SIGINT, ssu_signal_handler);

	while (1) {
		if (setjmp(jump_buffer) == 0) { // return : 직접 호출 0, setlongjmp에 의한 호출 0이 아닌 값
			printf("Hit Ctrl-c at anytime ... \n");
			pause();
		}
	}

	exit(0);
}

void ssu_signal_handler(int signo) {
	char character;

	signal(signo, SIG_IGN);
	printf("Did you hit Ctrl-c\nDo you really want to quit? [y/n] ");
	character = getchar();

	if (character == 'y' || character == 'Y')
		exit(0);
	else {
		signal(SIGINT, ssu_signal_handler);
		longjmp(jump_buffer, 1);
	}
}
