#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 1024

int main(void) {
	int n, p2c[2], c2p[2];
	pid_t pid;
	char line[MAXLINE];

	if( pipe(p2c) < 0 || pipe(c2p) < 0)
		printf("error");
	if( (pid = fork()) < 0) 
		printf("error");
	else if( pid > 0 ) { // parent
		close(p2c[0]); // p2c read mode close
		close(c2p[1]); // c2p write mode close
		write(p2c[1], "Hello World!\n", 14);
		n = read(c2p[0], line, MAXLINE);
		printf("parent get : %s", line);
	}
	else { // child
		close(p2c[1]);
		close(c2p[0]);
		n = read(p2c[0], line, MAXLINE);
		line[0] = tolower(line[0]);
		write(c2p[1], line, n);
		printf("child get : %s", line);
	}
	exit(1);
}
