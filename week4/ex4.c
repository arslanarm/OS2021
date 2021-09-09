#include "stdio.h"
#include "stdlib.h"

int main() {
	printf("> ");
	while (1) {
		char command[255];
		char endOfLine;
		scanf("%[^\n]%c", command, &endOfLine);
		printf("> ");
		system(command);
	}
}
