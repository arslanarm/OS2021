#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void *my_realloc(void *ptr, size_t size) {
	void *new_pointer = malloc(size);
	if (ptr == NULL) return new_pointer;
	memcpy(new_pointer, ptr, size);
	free(ptr);
	return new_pointer;
}

int main() {
	int *a = malloc(2 * sizeof(int));
	for (int i = 0; i < 2; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	a = my_realloc(a, 3 * sizeof(int));
	for (int i = 0; i < 3; i++) {
		printf("%d ", a[i]);
	}
	free(a);
}
