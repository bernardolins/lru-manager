#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include"tab.h"

#define NUM_PROC 5
#define NUM_PAG 10

void *processo(void *arg) {
	int id = *(int*)arg;
	int i;
	printf("Processo[%d] inicializou!\n", id);
	struct PageTable PT = IniciaTabela(id);
	printf("Tabela de paginas do processo[%d] = ", id);
	for(i = 0; i < NUM_PAG; i++) {
		printf("%d ", PT.TabelaPaginas[i]);
	}
	printf("\n");
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
