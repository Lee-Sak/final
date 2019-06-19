#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<pthread.h>

#define SOCK_PATH "sys-socket"

double result;
void *t_function(void *data) {
	char buf[1024]; 
	strncpy(buf, (char *)data, 1024);
	int x,y;
	char o;
	x = atoi(&buf[0]);
	o = buf[1];
	y = atoi(&buf[2]);
	printf("thread start\n");

	if(o == '+')	result = x + y;
	else if(o == '-')	result = x - y;
	else if(o == '*')	result = x * y;
	else	result = (double)x / y;
	printf("Thread end\n");
}

int main(void){
	int s, s2, len;
	unsigned int t;
	struct sockaddr_un local, remote;
	char str[100];
	double res;
	pthread_t p_thread;
	
	int thr_id;
	int status;

	if((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCK_PATH);
	// 소켓이 이미 있을 경우 bind가 되지 않으므로 삭제 시켜준다
	unlink(local.sun_path);
	len = strlen(local.sun_path) + sizeof(local.sun_family);
	
	// 서버프로세스와 소켓을 연결
	if(bind(s, (struct sockaddr *)&local, len) == -1){
		perror("bind");
		exit(1);
	}
	// 서버가 수신 클라이언트 연결 대기
	if(listen(s, 5) == -1){
		perror("listen");
		exit(1);
	}

	for(;;){
		int done, n;
		printf("Waiting for a connection...\n");
		t = sizeof(remote);
		// 클라이언트 접속 요청 승인후 데이터 주고받을 새 소켓 s2 생성
		if((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1){
			perror("accept");
			exit(1);
		}

		printf("Connected.\n");
			done = 0;
		do{
			n = recv(s2, str, 100, 0);
			if(n <= 0){
				if(n < 0) perror("recv");
				done = 1;
			}
			if(!done) {
				thr_id = pthread_create(&p_thread, NULL, t_function, (void *)str);
				pthread_join(p_thread, (void **)&status);
				//sleep(1);
				if(thr_id < 0) {
					printf("thread create error!");
					exit(0);
				}
				sprintf(str, "%.2lf", result);	
				if(send(s2, str, n, 0) < 0){
					perror("send");
					done =1;
				}
			}
		} while(!done);
		close(s2);
	}	
	return 0;
}

