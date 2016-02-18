#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include"tab.h"

#define NUM_PROC 5
#define NUM_PAG 10

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

void *processo(void *arg) {
	int id = *(int*)arg;
	int i;
	int numPagsMemoria = GetNumPaginasMemoria();
	printf("Processo[%d] inicializou!\n", id);
	struct PageTable PT = IniciaTabela(id);
	ImprimeTabela(&PT, id);
	pthread_exit(NULL);

}

int main(int argc, char **argv) {
	int i;
	int *arg;
	pthread_t threads[NUM_PROC];

	for(i = 0; i < NUM_PROC; i++) {
		arg = malloc(sizeof(int));
		*arg = i;
		if(pthread_create(&threads[i], NULL, processo, (void*)arg)) {
			printf("Erro ao criar as threads.\n");
			exit(-1);
		}
		sleep(3);
	}	

	for(i = 0; i < NUM_PROC; i++) {
		if(pthread_join(threads[i], NULL)) {
			printf("Erro no join das threads.\n");
			exit(-1);
		}
	}

	pthread_exit(NULL);
}
