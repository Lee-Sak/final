#include <stdio.h>
#include <signal.h>

int main(void) {
	sigset_t set;

	sigfillset(&set); // 모든 시그널 등록

	// SIGINT가 등록되었는지 확인
	switch(sigismember(&set, SIGINT)) {
		case 1 : printf("SIGINT는 포함되어 있다.\n");
				 break;
		case 0 : printf("SIGINT는 없다.\n");
				 break;
		default : printf("sigismember() 호출 실패.\n");
	}
	
	return 0;
}

