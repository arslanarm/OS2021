#include "stdio.h"
#include "string.h"

int main() {
  printf("Enter the line: ");
  char str[255];
  scanf("%s", str);
  int size = strlen(str);
  printf("Reversed string: ");
  for (int i = size - 1; i >= 0; i--) {
    putchar(str[i]);
  }
}
