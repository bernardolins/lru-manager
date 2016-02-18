#include<mem.h>
#include<stdio.h>
#include<time.h>
#include<tab.h>
#include<stdbool.h>

struct FRAME* AreaDeMemoria(int nframe) {
  struct FRAME* area = (struct FRAME*)malloc(sizeof(struct FRAME)*nframe);
  return area;
}

bool PaginaNaMemoria(struct PageTable *PT, int paginaEscolhida) {
	int i;
	for(i = 0; i < PAGS_MEM; i++) {
		if(PT->PaginasMemoria[i].NumPagina == paginaEscolhida) {
			return true;
		}
	}
	return false;
}

void AtualizaReferencia(int numPagina, int posicao) {
	
}


int EscolhePagina() {
	sleep(1);
	srand(time(NULL));
	return rand()%NUM_PAGS;
}

void SolicitaPagina(struct FRAME *areaMemoria, struct PageTable *PT, int id) {
	int i;
	int paginaEscolhida = EscolhePagina();

	//(PaginaNaMemoria(PT, paginaEscolhida)) ? lru()  : printf("Page fault!\n");
  
	//(MemoriaCheia())? swap() : InsereNaMemoria();	
	//se estiver, apenas atualiza a tabela de paginas para referencia
	//se não estiver, verifica se memoria esta cheia.
	/*if(memoriaCheia) {
		SwapOut();
	}*/

  //1. Verifica se página está na memória
  //  1.1 Se estiver, só atualiza a referência
  //  1.2 Senão
  //    1.2.1 Verifica se memória está cheia e tamanho do workingset
  //      1.2.1.2 Se memória está cheia
  //        1.2.1.2.1 Faz swap
  //      1.2.1.3 Se tem espaço na memória e tamanho do workingset = 4 faz o lru

	printf("Processo[%d] solicitou pagina.\n", id);
	printf("Pagina escolhida: %d\n", paginaEscolhida);

	for(i = id; i < TAM_MEM; i += 5) {
		areaMemoria[i].NumProcesso = id;
	}
}

void ImprimeMemoria(struct FRAME *areaMemoria, int tamanho) {
	int i;
	for(i = 0; i < tamanho; i++) {
		printf("[\t%d\t]\n", areaMemoria[i].Pagina);
	}
}

struct Memoria InicializaMemoria() {
  int i;

  struct Memoria memoria;

  for(i = 0; i < NUM_PROC; i++) {
    memoria.ListaDeProcessos[i] = -1;
  }

  return memoria;
}
