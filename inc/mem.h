#ifndef MEM
#define MEM

#include <stdio.h>
#include <stdlib.h>

struct FRAME {
  int NumProcesso;
  int Pagina;
};

struct FRAME* AreaDeMemoria(int nframe);

#endif
