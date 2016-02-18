#include<mem.h>

int* mem_area(int nframe) {
  int* area = (int*)malloc(sizeof(int)*nframe);

  return area;
}
