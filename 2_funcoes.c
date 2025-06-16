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

int consultarTopoPilha(Pilha* p) {
    return (p->topo >= 0) ? p->discos[p->topo] : -1;
}

void liberarTorres() {
    for (int i = 0; i < 3; i++) {
        limparPilha(&torres[i]);
    }
}

void inicializarTorres(int n) {
    for (int i = 0; i < 3; i++) criandoUmaPilha(&torres[i], n);
    for (int i = n; i >= 1; i--) adicionarDiscoNoTopo(&torres[0], i);
    movimentosFeitos = 0;
}

void gerarDiscoStr(int tamanho, int max_disco, char* buffer) {
    int largura_total = 2 * max_disco + 1;
    int largura_disco = 2 * tamanho + 1;
    int espacos = (largura_total - largura_disco) / 2;

    int i = 0;
    for (; i < espacos; i++) buffer[i] = ' ';
    for (int j = 0; j < largura_disco; j++) buffer[i++] = tamanho == 0 ? '|' : '#';
    for (; i < largura_total; i++) buffer[i] = ' ';
    buffer[i] = '\0';
}
