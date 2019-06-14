#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY_NUM 77440000
#define MEM_SIZE 1024

int main(void) {
	int shm_id;
	void *shm_addr;
	int *cal_num;
	int pid;

	if(-1 == (shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT | 0666 ))) {
		printf("shmget() error");
		return -1;
	}
	else 
		printf("shmget() success\n");

	if( (void *)-1 == (shm_addr = shmat(shm_id, (void *)0, 0)) ) {
		printf("shmat() error");
		return -1;
	}
	else 
		printf("shmat() success\n");

	cal_num = (int *)shm_addr;
	pid = fork();

	if(pid == 0) {
		// write into the shared memory
		*cal_num = 1;

		while(1) {
			// write into the shared memory
			*cal_num = *cal_num + 1;
			printf("child: %d\n", *cal_num);
			sleep(1);
		}
	}

	else if(pid > 0) {
		while(1) {
			sleep(1);
			// print out data read from the shared memory
			printf("parent: %d\n", *cal_num);
		}
	}
}


