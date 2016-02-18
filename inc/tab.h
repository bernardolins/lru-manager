#ifndef _TABH_
#define _TABH_

#include<stdio.h>

#define PAGS_MEM 4
#define NUM_PAGS 10

struct Paginas {
	int NumPagina;
	int Referenciada;
};

struct PageTable {
	int ID;
	struct Paginas PaginasMemoria[PAGS_MEM];
	int TabelaPaginas[NUM_PAGS];
};

struct PageTable IniciaTabela(int id);
int GetNumPaginasMemoria();

#endif
