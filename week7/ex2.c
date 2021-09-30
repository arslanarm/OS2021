#include "stdlib.h"
#include "stdio.h"

int main() {
	int n;
	printf("Enter the number: ");
	scanf("%d", &n);
	int *array = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		array[i] = i;
	}
	printf("[");
	for (int i = 0; i < n; i++) {
		printf("%d", array[i]);
		if (i < n - 1) {
			printf(", ");
		}
	}
	printf("]");
	free(array);
}
