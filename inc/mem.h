#ifndef MEM
#define MEM

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<tab.h>
#include<time.h>
#include<unistd.h>

#define TAM_MEM 64

#define NUM_PROC 20

struct FRAME {
  int NumProcesso;
  int Pagina;
};

struct Memoria {
  int Posicoes[TAM_MEM];
  int FramesOcupados;
  int ListaDeProcessos[NUM_PROC];
  int ProcessoMaisAntigo;
  int Contador;
  int ProcessosNaMemoria;
  struct PageTable *ListaDePaginas[NUM_PROC];
};

struct FRAME* AreaDeMemoria(int nframe);
struct Memoria InicializaMemoria();

bool PaginaNaMemoria(struct PageTable *PT, int paginaEscolhida);
int EscolhePagina();
void SolicitaPagina(struct Memoria *memoria, struct FRAME *memPrincipal, struct PageTable *PT, int id);

void InsereProcessoNaMemoria(struct Memoria *memoria, struct FRAME* memPrincipal, struct PageTable *PT);

int PrimeiraPosicaoVazia(struct Memoria *memoria);
int Swap2(struct Memoria *memoria, struct FRAME *memPrincipal);
void ImprimeProcessoMemoria(struct Memoria *memoria);
void PreencheMemoria(struct FRAME *memPrincipal);

int Swap(struct Memoria *memoria, struct FRAME *memPrincipal);
int ProximoFrameLivre(struct FRAME *memPrincipal);

void LRU(int pagina, struct Memoria *memoria, struct FRAME *memPrincipal, struct PageTable *PT);
void AtualizaReferencia(int numPagina, struct PageTable *PT);

void ImprimeMemoriaProcessos(struct Memoria *memoria);
void ImprimeWorkingset(struct PageTable *PT);
void ImprimeMemoria(struct FRAME *memPrincipal, int tamanho);

#endif
