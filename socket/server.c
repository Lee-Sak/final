#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "echo_socket"

int main(void) {
	int s, s2, len;
	unsigned t;
	struct sockaddr_un local, remote;
	char str[100];

	if( (s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1 ) {
		printf("socket error");
		exit(1);
	}

	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCK_PATH);
	unlink(local.sun_path); // 이미 해당 소켓이 있을 수 있으므로 제거
	len = strlen(local.sun_path) + sizeof(local.sun_family);
	
	// 소켓과 프로세스 연결, unlink안하면 바인딩이 되지 않음
	if(bind(s, (struct sockaddr *)&local, len) == -1) {
		printf("bind");
		exit(1);
	}
	
	// 서버가 수신 클라이언트 연결 대기
	if(listen(s, 5) == -1) {
		printf("listen");
		exit(1);
	} 

	for(;;) {
		int done, n;
		printf("waiting for a connection..\n");
		t = sizeof(remote);
		
		//클라이언트 접속 요청 승인
		if( (s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1 ) {
			printf("accept");
			exit(1);
		}
		printf("Connected.\n");
		
		done = 0;
		
		do {
			n = recv(s2, str, 100, 0);
			if(n <= 0) {
				if(n < 0) printf("recv");
				done = 1;
			}
			if(!done) {
				if(send(s2, str, n, 0) < 0) {
					printf("send");
					done = 1;
				}
			}
		} while(!done);

		close(s2);
	}
	
	return 0;
}

