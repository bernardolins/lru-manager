#include<stdio.h>

#define PAGS_MEM 4
#define NUM_PAGS 50

struct PageTable {
	int ID;
	int PaginasMemoria[PAGS_MEM];
	int TabelaPaginas[NUM_PAGS];
};

struct PageTable IniciaTabela(int id) {
	int i;
	struct PageTable PT;
	PT.ID = id;

	for(i = 0; i < PAGS_MEM; i++) {
		PT.PaginasMemoria[i] = 0;
	}

	for(i = 0; i < NUM_PAGS; i++) {
		PT.TabelaPaginas[i] = 0;
	}
	
	return PT;	
}
