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

struct PageTable IniciaTabela(int id) {
	int i;
	struct PageTable PT;
	PT.ID = id;

	for(i = 0; i < PAGS_MEM; i++) {
		PT.PaginasMemoria[i].NumPagina = 0;
		PT.PaginasMemoria[i].Referenciada = 0;
	}

	for(i = 0; i < NUM_PAGS; i++) {
		PT.TabelaPaginas[i] = 0;
	}
	
	return PT;	
}

int GetNumPaginasMemoria() {
	return PAGS_MEM;
}
#endif
