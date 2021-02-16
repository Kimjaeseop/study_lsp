#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

void *ssu_loop1(void *arg);
void *ssu_loop2(void *arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int shared_value;

int main(void) 
{
	pthread_t tid1, tid2;
	int status;

	shared_value = 0;

	if (pthread_create(&tid1, NULL, ssu_loop1, NULL) != 0) {
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	sleep(1);

	if (pthread_create(&tid2, NULL, ssu_loop2, NULL) != 0) {
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	if (pthread_join(tid1, (void *)&status) != 0) {
		fprintf(stderr, "pthread_join1 error\n");
		exit(1);
	}

	if (pthread_join(tid2, (void *)&status) != 0) {
		fprintf(stderr, "%s\n", strerror(errno));
		fprintf(stderr, "pthread_join2 error\n");
		exit(1);
	}

	status = pthread_mutex_destroy(&mutex);
	printf("code	=	%d\n", status);
	printf("programming is end\n");

	exit(0);
}

void *ssu_loop1(void *arg) {
	int i;

	for (i = 0; i < 10; i++) {
		pthread_mutex_lock(&mutex);
		printf("loop1 : %d\n", shared_value);
		shared_value++;

		if (i == 10) {
			return NULL;
		}

		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	printf("ssu_loop1 end\n");
	return NULL;
}

void *ssu_loop2(void *arg) {
	int i;

	for (i = 0; i < 10; i++) {
		pthread_mutex_lock(&mutex);
		printf("loop2 : %d\n", shared_value);
		shared_value++;
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}

	printf("ssu_loop2 end\n");
	return NULL;
}
