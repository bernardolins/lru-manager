#include<tab.h>

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

int GetNumPaginasMemoria() {
	return PAGS_MEM;
}


void ImprimeTabela(struct PageTable *PT, int id) {
	int i;
	int numPagsMemoria = GetNumPaginasMemoria();
	
	printf("| Tabela de paginas do processo[%d] |\n", id);
	printf("Paginas na memoria:\nReferencia:\t[ ");
	for(i = 0; i < numPagsMemoria; i++) {
		printf("%d ", PT->PaginasMemoria[i].Referenciada);
	}
	printf("]\nNumero Pagina:\t[ ");
	for(i = 0; i < numPagsMemoria; i++) {
		printf("%d ", PT->PaginasMemoria[i].NumPagina);
	}
	printf("]\n\nTabela de Paginas:\n");
	printf("[  Num Pagina\t|    Num Frame\t]\n");
	for(i = 0; i < NUM_PAG; i++) {
		printf("[\t%d\t|\t\t]\n", PT->TabelaPaginas[i]);
	}
	printf("\n=======================================\n");		
}
