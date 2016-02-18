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

bool MemoriaCheia(struct Memoria *memoria) {
  if(memoria->FramesOcupados <= TAM_MEM) {
    return false; 
  }

  return true;
}

bool WorkingSetLivre(struct PageTable *PT) {
  if(PT->ValorWorkingset < PAGS_MEM) {
    return true; 
  }

  return false;
}

void SolicitaPagina(struct Memoria *memoria, struct FRAME *areaMemoria, struct PageTable *PT, int id) {
	int i;
	int paginaEscolhida = EscolhePagina();

	//(PaginaNaMemoria(PT, paginaEscolhida)) ? lru()  : printf("Page fault!\n");
  
	//(MemoriaCheia())? swap() : InsereNaMemoria();	
	//se estiver, apenas atualiza a tabela de paginas para referencia
	//se não estiver, verifica se memoria esta cheia.
	/*if(memoriaCheia) {
		SwapOut();
	}*/

	printf("Processo[%d] solicitou pagina.\n", id);
	printf("Pagina escolhida: %d\n", paginaEscolhida);

  if(PaginaNaMemoria(PT, paginaEscolhida)) {
    printf("Já está\n");
    //atualiza a referência
  } 
  else {
    if(MemoriaCheia(memoria)) {
      printf("Faz Swap!!!!");
      //swap();
    }

    InsereProcessoNaMemoria(memoria, PT);
    //lru();

    //else if(WorkingSetLivre(PT)) {
    //  printf("Page fault\n");
    //  printf("Adiciona nova página do processo %d na memória\n", id);
    //  //Adiciona página na memória
    //  //Atualiza referências no workingset
    //  memoria->FramesOcupados++;
    //  printf("frames ocupados: %d\n", memoria->FramesOcupados);
    //}

    //memoria cheia
  }

  //1. Verifica se página está na memória
  //  1.1 Se estiver, só atualiza a referência
  //  1.2 Senão
  //    1.2.1 Verifica se memória está cheia e tamanho do workingset
  //      1.2.1.2 Se memória está cheia
  //        1.2.1.2.1 Faz swap
  //      1.2.1.3 Se tem espaço na memória e tamanho do workingset = 4 faz o lru


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

void ImprimeMemoriaProcessos(struct Memoria *memoria) {
  int tamanho = 20;
	int i;
	for(i = 0; i < tamanho; i++) {
		printf("[\t%d\t]\n", memoria->ListaDeProcessos[i]);
	}
}

struct Memoria InicializaMemoria() {
  int i;

  struct Memoria memoria;

  memoria.FramesOcupados = 0;
  memoria.ProcessoMaisAntigo = 0;
  memoria.ProcessosNaMemoria = 0;

  for(i = 0; i < NUM_PROC; i++) {
    memoria.ListaDeProcessos[i] = -1;
  }

  return memoria;
}

void InsereProcessoNaMemoria(struct Memoria *memoria, struct PageTable *PT) {
  if(PT->ValorWorkingset == 0) {
    memoria->ListaDeProcessos[memoria->ProcessosNaMemoria] = PT->ID;
    memoria->ProcessosNaMemoria++;
  }
}

void Swap(struct Memoria *memoria, struct FRAME *memPrincipal) {
  int i;
  int id = memoria->ListaDeProcessos[memoria->ProcessoMaisAntigo];

  struct PageTable tabela = memoria->ListaDePaginas[id];
  
  for(i = 0; i < tabela.ValorWorkingset; i++) {
    int pagina = tabela.PaginasMemoria[i]; 
    int endereco = memoria.TabelaPaginas[pagina];

    memPrincipal[endereco]->NumProcesso = -1;
    memPrincipal[endereco]->Pagina = -1;
  }

  memoria->ProcessoMaisAntigo = (memoria->ProcessoMaisAntigo + 1)% 20;
}
