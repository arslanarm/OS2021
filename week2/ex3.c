#include "stdio.h"
#include "stdlib.h"


void print_tree(int n) {
  printf("Making a tree for number %d\n", n);
  for (int i = 1; i < n + 1; i++) {
    for (int j = 0; j < n - i; j++) {
      putchar(' ');
    }
    for (int j = 0; j < 2*i - 1; j++) {
      putchar('*');
    }
    putchar('\n');
  }
}

void print_right_triangle(int n) {
  printf("Making a right triangle for number %d\n", n);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      putchar('*');
    }
    putchar('\n');
  }
}

void print_isosceles_triangle(int n) {
  printf("Making an isosceles triangle for number %d\n", n);
  for (int i = 1; i <= n; i++) {
    if (i <= n / 2) {
      for (int j = 1; j <= i; j++) putchar('*');
    } else {
      for (int j = 0; j <= n - i; j++) putchar('*');
    }
    putchar('\n');
  }
}

void print_square(int n) {
  printf("Making a square for number %d\n", n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      putchar('*');
    }
    putchar('\n');
  }
}

int main(int argc, char** argv) {
  if (argc == 1) {
    printf("Required paramter N has not been given. Please provide N.");
    return 1;
  }
  int n = atoi(argv[1]);
  if (n == 0) {
    printf("Invalid parameter N. N shoud be an integer value greater than zero");
    return 1;
  }
  print_tree(n);
  print_right_triangle(n);
  print_isosceles_triangle(n);
  print_square(n);
}
