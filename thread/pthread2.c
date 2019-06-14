// creating 5 threads
// gcc pthread2.c -lpthread -o pthread2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

void *perform_work(void *arguments) {
	int index = *( (int *)arguments);
	int sleep_time = 1 + rand() % NUM_THREADS;

	printf("THREAD %d: Started.\n", index);
	printf("THREAD %d: will be sleeping for %d seconds.\n", index, sleep_time);

	sleep(sleep_time);

	printf("THREAD %d: Ended.\n", index);
}

int main(void) {
	pthread_t threads[NUM_THREADS];

	int thread_args[NUM_THREADS];
	int i;
	int result_code;

	// create all threads one by one
	for(i=0; i<NUM_THREADS; i++) {
		printf("IN MAIN: creating thread %d.\n", i);
		thread_args[i] = i;
		result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
		// assert(exp) : exp가 true면그냥 진행, false면 프로그램 종료
		assert(!result_code);
	}

	printf("IN MAIN: All threads are created.\n");

	// wait for each thread to complete
	for(i=0; i<NUM_THREADS; i++) {
		result_code = pthread_join(threads[i], NULL);
		assert(!result_code);
		printf("IN MAIN: Thread %d has ended.\n", i);
	}
	
	printf("MAIN program has ended.\n");
	return 0;
}
