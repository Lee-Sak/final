#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
	sigset_t sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);

	printf("PID: %d, waiting for any signal except SIGINT\n", getpid());
	
	//sigset에 있는 명령어만 뺴고 나머지만 기다린다
	sigsuspend(&sigset);
	
	return 0;
}

