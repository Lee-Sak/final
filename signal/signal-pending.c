#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
	sigset_t pendingset;
	int ndx = 0;

	// 모든 시그널 블록화
	sigfillset(&pendingset);
	// 이전 블록된 시그널 집합을 모두 지우고 두번째 인수인 sigset 시그널 집합으로 설정
	sigprocmask(SIG_SETMASK, &pendingset, NULL);

	while(1) {
		printf("카운트: %d\n", ndx++);
		sleep(1);
		if( 0 == sigpending(&pendingset) ) {
			if( sigismember(&pendingset, SIGINT) ) {
				printf("ctrl-c 눌렀지, 무한 루프 종료.\n");
				break;
			}
		}
	}
	return 0;
}
	
	
