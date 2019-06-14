// Mutex locking & unlocking
// gcc mutex1.c -lpthread -o mutext1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int ncount; // 쓰레드간 공유되는 자원
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 쓰레드 초기화(생성)

// 쓰레드 함수 1
void *do_loop(void *data) {
	int i;
	int random_time = rand() % 5 + 1; // Range 1~5

	pthread_mutex_lock(&mutex); // 잠금을 생성

	for(i=0; i<5; i++) {
		printf("th_fuc1: %d\n", ncount);
		ncount++;
		sleep(random_time);
	}
	pthread_mutex_unlock(&mutex);
}

//쓰레드 함수2
void *do_loop1(void *data) {
	int i;
	int random_time = rand() % 5 + 1; // Range 1~5

	pthread_mutex_lock(&mutex); // 잠금을 생성

	for(i=0; i<5; i++) {
		printf("th_fuc2: %d\n", ncount);
		ncount++;
		sleep(random_time);
	}
	pthread_mutex_unlock(&mutex);
}

int main(void) {
	pthread_t p_thread[2];

	int thr_id;
	int status;
	int a = 1;

	ncount = 0;
	thr_id = pthread_create(&p_thread[0], NULL, do_loop, (void *)&a);
	thr_id = pthread_create(&p_thread[1], NULL, do_loop1, (void *)&a);

	pthread_join(p_thread[0], (void *)&status);
	pthread_join(p_thread[1], (void *)&status);
	
	// mutex 객체 파괴
	status = pthread_mutex_destroy(&mutex);

	printf("code = %d\n", status);
	printf("Programming is end\n");
	return 0;
}

















