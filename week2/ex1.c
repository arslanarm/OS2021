#include "stdio.h"
#include "limits.h"
#include "float.h"
int main() {
  int maxI = INT_MAX;
  float maxF = FLT_MAX;
  double maxD = DBL_MAX;
  printf("Max Integer: %d\nMax Float: %f\nMax Double: %f\n", maxI, maxF, maxD);
}
