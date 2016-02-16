#include<mem.c>

int* area(int nframe) {
  int* area = (int*)malloc(sizeof(int)*nframe);
  return area;
}
