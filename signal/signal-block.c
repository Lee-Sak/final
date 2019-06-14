#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
	sigset_t sigset;
	int ndx;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	// 해당 sigset에 포함된 명령어 block
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	
	// 중요한 일 시작
	for(ndx=3; 0<ndx; ndx--) {
		printf("카운트 다운 %d\n", ndx);
		sleep(1);
	}
	// 중요한 일 종료 ------

	printf("ctrl-c에 대한 블록을 해제합니다.\n");
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	printf("카운트 다은 중에 ctrl-c키를 눌렀다면, 이문장도 출력이 안되.\n");

	while(1)
		;
	
	return 0;
}
