#include "stdio.h"

void myswap(int* a, int* b) {
  int z = *a;
  *a = *b;
  *b = z;
}


int main() {
  int first;
  int second;
  printf("Enter the first number: ");
  scanf("%d", &first);
  printf("Enter the second number: ");
  scanf("%d", &second);
  myswap(&first, &second);
  printf("First value: %d\nSecond value: %d", first, second);
}
