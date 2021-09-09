#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/wait.h>

void mysystem(char *command) {
	int pid = fork();
	if (pid == 0) {
		int spaces = 0;
		for (int i = 0; i < strlen(command); i++) {
			if (command[i] == ' ') {
				spaces++;
			}
		}
		int *lengths = malloc(sizeof(int) * spaces);
		for (int i = 0; i < spaces; i++) {
			lengths[i] = 0;
		}
		int j = 0;
		for (int i = 0; i < strlen(command); i++) {
			if (command[i] == ' ') {
				lengths[j]++;
				j++;
			}
		}
		char **arguments = malloc(sizeof(char*) * (spaces + 1));
		for (int i = 0; i < spaces + 1; i++) {
			arguments[i] = malloc(sizeof(char) * lengths[i]);
		}
		int prev = 0;
		int i;
		j = 0;
		for (i = 0; i < strlen(command); i++) {
			if (command[i] == ' ') {
				strncpy(arguments[j], command + prev, i - prev);
				j++;
				prev = i + 1;	
			}
		}
		strncpy(arguments[j], command + prev, i - prev);
		
		execvp(arguments[0], arguments);
	}
	waitpid(pid, NULL, 0);
	
}

int main() {
	char argument[2000];
	char endOfline;
	printf("> ");
	while (scanf("%2000[^\n]%c", argument, &endOfline) != EOF) {
		if (strlen(argument) != 0) {
		mysystem(argument);
		}
		printf("> ");
	}
}

