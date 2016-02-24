#include<mem.h>
#include<stdio.h>
#include<time.h>
#include<tab.h>
#include<stdbool.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

struct FRAME *AreaDeMemoria(int nframe) {
  struct FRAME *area = malloc(sizeof(struct FRAME)*nframe);
  return area;
}

struct Memoria InicializaMemoria() {
  int i;

  struct Memoria memoria;

  memoria.FramesOcupados = 0;
  memoria.ProcessoMaisAntigo = 0;
  memoria.Contador = 0;
  memoria.ProcessosNaMemoria = 0;

  for(i = 0; i < NUM_PROC; i++) {
    memoria.ListaDeProcessos[i] = -1;
  }

  for(i = 0; i < TAM_MEM; i++) {
    memoria.Posicoes[i] = 0;
  }

  return memoria;
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

int EscolhePagina() {
	sleep(1);
	srand(time(NULL));
	return rand()%NUM_PAGS;
}

bool MemoriaCheia(struct Memoria *memoria) {
  if(memoria->FramesOcupados < TAM_MEM) {
    return false; 
  }

  return true;
}

int ProximoFrameLivre(struct FRAME* memPrincipal) {
	int frame = 0;
	int i;
	for(i = 0; i < TAM_MEM; i++) {
		if(memPrincipal[i].Pagina == -1) {
			frame = i;
			break;			
		}
	}
	printf("Frame:%d\n", frame);
	return frame;
}

void PreencheMemoria(struct FRAME *memPrincipal) {
	int i;
	for(i = 0; i < TAM_MEM; i++) {
		memPrincipal[i].NumProcesso = -1;
		memPrincipal[i].Pagina = -1;
	}
}

int Swap2(struct Memoria *memoria, struct FRAME *memPrincipal) {
	memoria->ProcessoMaisAntigo = memoria->ListaDeProcessos[memoria->Contador];
	int i;
	int pag;
	int frame = 0;
	int proximoFrame = 100;
	int id = memoria->ProcessoMaisAntigo;

	printf(KMAG "--- Fazendo Swap. Sai o processo %d\n" KWHT, id);
	
	struct PageTable *tabela = memoria->ListaDePaginas[id];

	
	int tam = tabela->ValorWorkingset;
	for(i = 0; i < tam; i++) {
		if(tabela->TabelaPaginas[tabela->PaginasMemoria[i].NumPagina] < proximoFrame) {
			proximoFrame = tabela->TabelaPaginas[tabela->PaginasMemoria[i].NumPagina];
		}
	}
	
	for(i = 0; i < tam; i++) {
		pag = tabela->PaginasMemoria[i].NumPagina; 
		frame = tabela->TabelaPaginas[pag];
		memPrincipal[frame].NumProcesso = -1;
		memPrincipal[frame].Pagina = -1;

		tabela->TabelaPaginas[pag] = -2;
		tabela->PaginasMemoria[i].NumPagina = -1;
		tabela->ValorWorkingset--;
		memoria->FramesOcupados--;
	}

	//memoria->ProcessosNaMemoria--;
	//memoria->ProcessoMaisAntigo = (memoria->ProcessoMaisAntigo + 1)% 20;
	memoria->ListaDeProcessos[memoria->Contador] = -1;
	memoria->Contador = (memoria->Contador + 1) % 20;
	return proximoFrame;
}

void ImprimeProcessosMemoria(struct Memoria *memoria) {
	int i;
	printf("\t---- Lista de processos: [ ");
	for(i = 0; i < NUM_PROC; i++) {
		printf("%d ", memoria->ListaDeProcessos[i]);
	}
	printf("]\n");
}


void SolicitaPagina(struct Memoria *memoria, struct FRAME *memPrincipal, struct PageTable *PT, int id) {
	int paginaEscolhida = EscolhePagina();
	static int frameLivre = 0;
	printf(KBLU "Processo[%d] solicitou pagina %d\n" KWHT, id, paginaEscolhida);
  //InsereProcessoNaMemoria(memoria, memPrincipal, PT);	
  //LRU(paginaEscolhida, memoria, memPrincipal, PT);

  if(PaginaNaMemoria(PT, paginaEscolhida)) {
    printf(KGRN "--- Página já está na memória\n" KWHT);
    LRU(paginaEscolhida, memoria, memPrincipal, PT);
  } 
  else {
    printf(KRED "--- Page fault\n" KWHT);
    if(MemoriaCheia(memoria)) {
      frameLivre = Swap2(memoria, memPrincipal);
    }
    else {
	frameLivre = ProximoFrameLivre(memPrincipal);
    }
    
    InsereProcessoNaMemoria(memoria, memPrincipal, PT);
   // LRU(paginaEscolhida, memoria, memPrincipal, PT);
   if(PT->ValorWorkingset < 4) {
	    if(PT->TabelaPaginas[paginaEscolhida] == -2) {
		printf("\t---- Buscando pagina %d no DISCO!.\n", paginaEscolhida);
		sleep(2);
	    }
	    memPrincipal[frameLivre].Pagina = paginaEscolhida;
	    memPrincipal[frameLivre].NumProcesso = id;
	    PT->TabelaPaginas[paginaEscolhida] = frameLivre;
	    memoria->FramesOcupados++;
    }
    LRU(paginaEscolhida, memoria, memPrincipal, PT);
    if(PT->ValorWorkingset < 4) {
	PT->ValorWorkingset++;
    }
    ImprimeProcessosMemoria(memoria);
  }

  printf("--- Frames da memória principal ocupados: %d\n", memoria->FramesOcupados);
  printf("\n");
}

int PrimeiraPosicaoVazia(struct Memoria *memoria) {
  int i;
  for(i = 0; i < TAM_MEM; i++) {
    if(memoria->Posicoes[i] == 0) {
      return i;
    } 
  }

  return TAM_MEM;
}

void InsereProcessoNaMemoria(struct Memoria *memoria, struct FRAME* memPrincipal, struct PageTable *PT) {
  if(PT->ValorWorkingset == 0) {
    memoria->ListaDeProcessos[memoria->ProcessosNaMemoria] = PT->ID;
    memoria->ProcessosNaMemoria = (memoria->ProcessosNaMemoria + 1) % NUM_PROC;
  }

//  if(MemoriaCheia(memoria)) {
//    Swap(memoria, memPrincipal);
//  }
//
//  if(PT->ValorWorkingset == 0) {
//    if(MemoriaCheia(memoria)) {
//      Swap(memoria, memPrincipal);
//    }
//
//    int posicao = PrimeiraPosicaoVazia(memoria);
//
//    memPrincipal[posicao].NumProcesso = PT->ID;
//    memPrincipal[posicao].Pagina = PT->PaginasMemoria[0].NumPagina;
//
//    memoria->ListaDeProcessos[memoria->ProcessosNaMemoria] = PT->ID;
//    memoria->ProcessosNaMemoria++;
//    memoria->Posicoes[posicao] = 1;
//  }
}

int Swap(struct Memoria *memoria, struct FRAME *memPrincipal) {
  //bug aqui e no insereMemoria!!
  printf("Cont = %d\n", memoria->Contador);
  memoria->ProcessoMaisAntigo = memoria->ListaDeProcessos[memoria->Contador];
  int i;
  //int id = memoria->ListaDeProcessos[memoria->ProcessoMaisAntigo]; 
  int id = memoria->ProcessoMaisAntigo;
  int proximoFrame = 0;
  printf(KMAG "--- Fazendo Swap. Sai o processo %d\n" KWHT, id);

  struct PageTable *tabela = memoria->ListaDePaginas[id];
   

  for(i = 0; i < tabela->ValorWorkingset; i++) {
    int pagina = tabela->PaginasMemoria[i].NumPagina; 
    int endereco = tabela->TabelaPaginas[pagina];
    if(i == 0) {
	proximoFrame = endereco;
    }
	
    memPrincipal[endereco].NumProcesso = -1;
    memPrincipal[endereco].Pagina = -1;

    memoria->Posicoes[endereco] = 0;

    memoria->FramesOcupados--;
  }

  memoria->ProcessosNaMemoria--;
  //memoria->ProcessoMaisAntigo = (memoria->ProcessoMaisAntigo + 1)% 20;
  memoria->Contador = (memoria->Contador + 1) % 20;
  printf("Processo mais antigo agora: %d\n", memoria->ProcessoMaisAntigo);
  return proximoFrame;
}

void LRU(int pagina, struct Memoria *memoria, struct FRAME *memPrincipal, struct PageTable *PT) {
  printf("\t---- Workingset antes: ");
  ImprimeWorkingset(PT);
  int frame = 0;
  int paginaRetira = 0;

  if(PT->ValorWorkingset < PAGS_MEM) {
    if(PaginaNaMemoria(PT, pagina)) {
      AtualizaReferencia(pagina, PT);
    } 
    else {
      PT->PaginasMemoria[PT->ValorWorkingset].NumPagina = pagina;
      //PT->ValorWorkingset++;
      //memoria->FramesOcupados++;
    }
  } 
  else {
    if(PaginaNaMemoria(PT, pagina)) {
      AtualizaReferencia(pagina, PT);   
    } 
    else {
      printf(KYEL "--- Workingset cheio.\n" KWHT);
      paginaRetira = PT->PaginasMemoria[0].NumPagina;
      frame = PT->TabelaPaginas[paginaRetira];

      PT->TabelaPaginas[paginaRetira] = -1;
      memPrincipal[frame].Pagina = pagina;
      PT->TabelaPaginas[pagina] = frame;
      PT->PaginasMemoria[0].NumPagina = pagina;
      
      AtualizaReferencia(pagina, PT);
      
    }
  }

  printf("\t---- Workingset depois: ");
  ImprimeWorkingset(PT);
}

void AtualizaReferencia(int pagina, struct PageTable *PT) {
  int i;
  for(i = 0; i < PT->ValorWorkingset-1; i++) {
    if(PT->PaginasMemoria[i].NumPagina == pagina) {
      int copo = PT->PaginasMemoria[i+1].NumPagina;
      PT->PaginasMemoria[i+1].NumPagina = PT->PaginasMemoria[i].NumPagina;
      PT->PaginasMemoria[i].NumPagina = copo;
    }
  }
}

void ImprimeMemoria(struct FRAME *memPrincipal, int tamanho) {
	int i;
	for(i = 0; i < tamanho; i++) {
		if(memPrincipal[i].NumProcesso == -1) {
			printf("["KCYN"P%d.%d"KWHT"]", memPrincipal[i].NumProcesso, memPrincipal[i].Pagina);
		}
		else { 
			printf("[P%d.%d]", memPrincipal[i].NumProcesso, memPrincipal[i].Pagina);
		}
	}
  printf("\n");
}

void ImprimeMemoriaProcessos(struct Memoria *memoria) {
  int tamanho = 20;
	int i;
	for(i = 0; i < tamanho; i++) {
		printf("[\t%d\t]\n", memoria->ListaDeProcessos[i]);
	}
}

void ImprimeWorkingset(struct PageTable *PT) {
  int i;
  printf("[ ");
  for(i = 0; i < PT->ValorWorkingset; i++) {
    printf("%d ", PT->PaginasMemoria[i].NumPagina);
  }

  printf("]\n");
}
