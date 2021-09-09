#include "stdio.h"
#include "stdlib.h"

int main() {
	printf("> ");
	while (1) {
		char command[255];
		scanf("%s", command);
		printf("> ");
		system(command);
	}
}
