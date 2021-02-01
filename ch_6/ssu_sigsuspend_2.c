#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

static void ssu_func(int signo);
void ssu_print_mask(const char *str);

int main(void) 
{
	sigset_t new_mask, old_mask, wait_mask;
	ssu_print_mask("program start: ");

	if (signal(SIGINT, ssu_func) == SIG_ERR) {
		fprintf(stderr, "signal(SIGINT) error\n");
		exit(1);
	}

	sigemptyset(&wait_mask);
	sigaddset(&wait_mask, SIGUSR1);
	sigemptyset(&new_mask);
	sigaddset(&new_mask, SIGINT);

	if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
		fprintf(stderr, "SIG_BLOCK() error\n");
		exit(1);
	}

	ssu_print_mask("in critical region: ");

	if (sigsuspend(&wait_mask) != -1) { // 캐치할 수 있는 시그널이 도착하거나 SIGINT 시그널이 도착할 때까지 프로세스를 잠시 블록
		fprintf(stderr, "sigsuspend() error\n");
		exit(1);
	}

	ssu_print_mask("after return from sigsuspend: ");

	if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
		fprintf(stderr, "SIG_SETMASK() error\n");
		exit(1);
	}

	ssu_print_mask("program exit: ");

	exit(0);
}

void ssu_print_mask(const char *str) {
	sigset_t sigset;
	int err_num;

	err_num = errno;

	if (sigprocmask(0, NULL, &sigset) < 0) {
		fprintf(stderr, "sigprocmask() error\n");
		exit(1);
	}

	printf("%s", str);

	if (sigismember(&sigset, SIGINT))
		printf("SIGINT ");

	if (sigismember(&sigset, SIGQUIT))
		printf("SIGQUIT ");

	if (sigismember(&sigset, SIGUSR1))
		printf("SIGUSR1 ");

	if (sigismember(&sigset, SIGALRM))
		printf("SIGALRM ");

	printf("\n");
	errno = err_num;
}

static void ssu_func(int signo) { 
	ssu_print_mask("\nin ssu_func: ");
}
