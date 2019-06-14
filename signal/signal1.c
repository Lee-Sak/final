#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void (*old_fun)(int);

void sigint_handler(int signo) {
	printf("ctrl-c 눌렀지?\n");
}

int main(void) {
	// SIGINT라는 시그널이 입력되면 해당 핸들러 실행
	old_fun = signal(SIGINT, sigint_handler);
	// signal 함수는 default값(프로세스 종료)리턴하여 old_fun에 저장

	while(1) {
		printf("signal handler registered!\n");
		sleep(1);
	}

	return 0;
}
