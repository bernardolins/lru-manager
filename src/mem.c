#include<mem.h>

int* AreaDeMemoria(int nframe) {
  int* area = (int*)malloc(sizeof(int)*nframe);

  return area;
}
