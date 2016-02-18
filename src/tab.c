#include<tab.h>

struct PageTable IniciaTabela(int id) {
	int i;
	struct PageTable PT;

	PT.ID = id;

	for(i = 0; i < PAGS_MEM; i++) {
		PT.PaginasMemoria[i].NumPagina = -1;
	}

	for(i = 0; i < NUM_PAGS; i++) {
		PT.TabelaPaginas[i] = -1;
	}
	
	return PT;	
}

int GetNumPaginasMemoria() {
	return PAGS_MEM;
}


void ImprimeTabela(struct PageTable *PT, int id) {
	int i;
	int numPagsMemoria = GetNumPaginasMemoria();
	
	printf("| Tabela de paginas do processo[%d] |\n", id);
	printf("Paginas na memoria:\n\t[ ");

	printf("]\nNumero Pagina:\t[ ");
	for(i = 0; i < numPagsMemoria; i++) {
		printf("%d ", PT->PaginasMemoria[i].NumPagina);
	}
	printf("]\n\nTabela de Paginas:\n");
	printf("[  Num Pagina\t|    Num Frame\t]\n");
	for(i = 0; i < NUM_PAGS; i++) {
		printf("[\t%d\t|\t\t]\n", PT->TabelaPaginas[i]);
	}
	printf("\n=======================================\n");		
}
