// client.c //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "sys-socket"

int main(void) {
	int s, t, len;
	struct sockaddr_un  remote;
	char str[100];
	
	// 소켓 생성
	if( (s = socket(AF_UNIX, SOCK_STREAM, 0) ) == -1 ) {
		printf("socket");
		exit(1);
	}
	
	printf("Trying to connect...\n");
	
	// 연결할 소켓의 통신 방식과 주소 지정
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	// 해당 변수의 구조체 크기 
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	
	// 소켓과 클라이언트 연결
	if( connect(s, (struct sockaddr *)&remote, len) == -1 ) {
		printf("connect");
		exit(1);
	}

	printf("Connected.\n");

	while(printf("> "), fgets(str, 100, stdin), !feof(stdin)) {
			if( send(s, str, strlen(str), 0) == -1) {
				printf("send");
				exit(1);
			}

			if( (t=recv(s, str, 100, 0)) > 0 ) {
				str[t] = '\0';
				printf("echo> %s\n", str);
			}
			else {
				if (t < 0) printf("recv");
				else printf("server closed connection\n");
				exit(1);
			}
	}

	close(s);

	return 0;
}

