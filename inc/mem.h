#ifndef MEM
#define MEM

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<tab.h>
#include<time.h>
#include<unistd.h>

#define TAM_MEM 64

struct FRAME {
  int NumProcesso;
  int Pagina;
};

struct FRAME* AreaDeMemoria(int nframe);

bool PaginaNaMemoria(struct PageTable *PT, int paginaEscolhida);
void AtualizaReferencia(int numPagina, int posicao);
int EscolhePagina();
void SolicitaPagina(struct FRAME *areaMemoria, struct PageTable *PT, int id);
void ImprimeMemoria(struct FRAME *areaMemoria, int tamanho);
#endif
