#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include"tab.h"

#define NUM_PROC 5
#define NUM_PAG 10
#define TAM_MEM 64

pthread_mutex_t mutex;


int *memoria;
int *frameLivre;

void *processo(void *arg) {
	int id = *(int*)arg;
	int i;
	printf("Processo[%d] inicializou!\n", id);
	struct PageTable PT = IniciaTabela(id);
	while(i < 5) {
	pthread_mutex_lock(&mutex);
	SolicitaPagina(memoria, &PT, id);
	pthread_mutex_unlock(&mutex);
	//ImprimeTabela(&PT, id);
	sleep(3); i++;
	}
	//(&PT, id);
	pthread_exit(NULL);

}

int main(int argc, char **argv) {
	int i;
	int *arg;
	pthread_mutex_init(&mutex, NULL);
	pthread_t threads[NUM_PROC];

	//==============================
	memoria = AreaDeMemoria(TAM_MEM);
	//==============================
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
	//ImprimeMemoria(memoria, TAM_MEM);
	
	free(arg); free(memoria);
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}
