#include "stdio.h"
#include "stdlib.h"

void bubble_sort(int *array, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (array[j] > array[j + 1]) {
				int z = array[j];
				array[j] = array[j + 1];
				array[j + 1] = z;
			}
		}
	}
}


int main() {
	int n;
	printf("Enter the size of the array: ");
	scanf("%d", &n);
	int *array = (int*) malloc(n * sizeof(int));
	printf("Enter the array(separated by space): ");
	for (int i = 0; i < n; i++) {
		scanf("%d", array + i);
	}
	bubble_sort(array, n);
	printf("Sorted array: [");
	for (int i = 0; i < n; i++) {
		printf("%d", array[i]);
		if (i < n - 1) {
			printf(" ");
		}
	}
	printf("]\n");
	return 0;
}
