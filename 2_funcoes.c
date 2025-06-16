#include <stdio.h>
#include <string.h>
#include "3_funcoes.h"

Pilha torres[3]; 
int movimentosFeitos = 0;

void criandoUmaPilha(Pilha* p, int capacidade) {
    p->discos = (int*)malloc(sizeof(int) * capacidade);
    p->topo = -1;
    p->capacidade = capacidade;
}

void limparPilha(Pilha* p) {
    free(p->discos);
    p->discos = NULL;
    p->topo = -1;
    p->capacidade = 0;
}

int adicionarDiscoNoTopo(Pilha* p, int valor) {
    if (p->topo >= p->capacidade - 1) return 0;
    p->discos[++p->topo] = valor;
    return 1;
}

int removerDoTopo(Pilha* p, int* valor) {
    if (p->topo < 0) return 0;
    *valor = p->discos[p->topo--];
    return 1;
}
