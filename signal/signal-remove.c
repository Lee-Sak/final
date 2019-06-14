#include <stdio.h>
#include <signal.h>

int main(void) {
	sigset_t set;

	sigemptyset(&set); // 시그널 집합 변수의 내용을 모두 제거
	sigaddset(&set, SIGINT); // 시그널 집합 변수에 SIGINT 추가

	// SIGINT가 등록되었는지 확인
	switch(sigismember(&set, SIGINT)) {
		case 1 : printf("SIGINT는 포함되어 있다.\n");
				 break;
		case 0 : printf("SIGINT는 없다.\n");
				 break;
		default : printf("sigismember() 호출 실패.\n");
	}
	// SIGINT 삭제
	sigdelset(&set, SIGINT);
	
	//SIGINT가 등록되었는지 확인
	switch(sigismember(&set, SIGINT)) {
		case 1 : printf("SIGINT는 포함되어 있다.\n");
				 break;
		case 0 : printf("SIGINT는 없다.\n");
				 break;
		default : printf("sigismember() 호출 실패.\n");
	}
	return 0;
}
