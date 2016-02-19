#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>

#include<tab.h>
#include<mem.h>

#define NUM_PAG 10

pthread_mutex_t mutex;


struct FRAME *memoria;
struct Memoria memProcessos;

int *frameLivre;

//void PreencheTabela(struct PageTable *pt, int id) {
//  int i;
//
//  for(i = 0; i < NUM_PAGS; i++) {
//    pt->TabelaPaginas[i] = id;
//  }
//}

//void imprimeMem(struct Memoria *mem) {
//  int i = 0;
//
//  for(i = 0; i < NUM_PROC; i++) {
//    ImprimeTabela(&mem->ListaDePaginas[i], i);
//  } 
//}

void *processo(void *arg) {
	int id = *(int*)arg;

	printf("Processo[%d] inicializou!\n", id);

	struct PageTable PT = IniciaTabela(id);
  //PreencheTabela(&PT, id);
  memProcessos.ListaDePaginas[id] = &PT;

  while(1) {
	  pthread_mutex_lock(&mutex);
	  SolicitaPagina(&memProcessos, memoria, &PT, id);
	  pthread_mutex_unlock(&mutex);
	  //ImprimeTabela(&PT, id);
    ImprimeMemoria(memoria, 64);
	  sleep(3); 	
  }



	pthread_exit(NULL);

}

int main(int argc, char **argv) {
	int i;
	int *arg;
	pthread_mutex_init(&mutex, NULL);
	pthread_t threads[NUM_PROC];

	//==============================
	memoria = AreaDeMemoria(TAM_MEM);
  memProcessos = InicializaMemoria();
	//==============================
  //
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
  //imprimeMem(&memProcessos);
  ImprimeMemoriaProcessos(&memProcessos);
	
	free(arg); free(memoria);
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}
