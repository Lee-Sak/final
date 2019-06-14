// How to block other signals?

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signo) {
	int ndx;

	printf("ctrl-c 키눌렀지?.\n");
	printf("5초간대기, 이떄 ctrl-z 키 눌러.\n");

	for(ndx=5; 0<ndx; ndx--) {
		printf("%d초 남았어.\n", ndx);
		sleep(1);
	}
}

int main(void) {
	struct sigaction act;

	act.sa_handler = sigint_handler;
	sigfillset(&act.sa_mask); // 모든 시그널 블록
	
	sigaction(SIGINT, &act, NULL);
	
	while(1) {
		printf("signal handler registered for SIGINT\n");
		sleep(1);
	}
}

