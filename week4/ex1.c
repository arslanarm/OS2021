#include "stdio.h"
#include "sys/types.h"
#include "unistd.h"
#include "stdlib.h"
int main(int argc, char** argv) {
	int n = atoi(argv[1]);
	int pid = fork();
	if (pid == 0) {
		printf("Hello from child %d\n", pid - n);
	} else {
		printf("Hello from parent %d\n", pid - n);
	}
}
