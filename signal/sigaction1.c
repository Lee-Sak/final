#include <stdio.h>
#include <signal.h>
#include <unistd.h>

struct sigaction act_new;
struct sigaction act_old;

void sigint_handler(int signo) {
	printf("ctrl-c 키룰 늘렀지?\n");
	printf("또 눌르면 종료되.\n");
	sigaction(SIGINT, &act_old, NULL);
}

int main(void) {
	act_new.sa_handler = sigint_handler; // 시그널 핸들러 지정
	// sigset_t sa_mask; 시그널을 처리하는 동안 블록화할 시그널 집합의 마스크
	sigemptyset(&act_new.sa_mask); // 시그널 처리 중 블록될 시그널은 없음

	// SIGINT를 지정하면서 act_old에 이전 정보를 저장
	sigaction(SIGINT, &act_new, &act_old);

	while(1) {
		printf("sigaction\n");
		sleep(1);
	}
	return 0;
}
