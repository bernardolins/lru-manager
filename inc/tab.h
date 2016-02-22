#ifndef _TABH_
#define _TABH_

#include<stdio.h>

#define PAGS_MEM 4
#define NUM_PAGS 50

struct Paginas {
	int NumPagina;
};

struct PageTable {
	int ID;
	struct Paginas PaginasMemoria[PAGS_MEM];
	int TabelaPaginas[NUM_PAGS];
  	int ValorWorkingset;
};

struct PageTable IniciaTabela(int id);
int GetNumPaginasMemoria();
void ImprimeTabela(struct PageTable *PT, int id);

#endif
