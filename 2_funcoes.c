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

void exibirTorres(int n) {
    printf("\nEstado atual das torres:\n\n");
    char linha[3][32];

    for (int i = n - 1; i >= 0; i--) {
        for (int t = 0; t < 3; t++) {
            int disco = (i <= torres[t].topo) ? torres[t].discos[i] : 0;
            gerarDiscoStr(disco, n, linha[t]);
        }
        printf("%s   %s   %s\n", linha[0], linha[1], linha[2]);
    }

    int largura = 2 * n + 1;
    for (int t = 0; t < 3; t++) {
        for (int i = 0; i < (largura - 1) / 2; i++) printf(" ");
        printf("%c", 'A' + t);
        for (int i = 0; i < (largura - 1) / 2; i++) printf(" ");
        printf("   ");
    }
    printf("\n");
}

int moverDisco(int origem, int destino) {
    int disco;

    if (!removerDoTopo(&torres[origem], &disco)) {
        printf("A torre de origem está vazia!\n");
        return 0;
    }

    if (consultarTopoPilha(&torres[destino]) != -1 && consultarTopoPilha(&torres[destino]) < disco) {
        printf("Movimento inválido! Não pode colocar disco maior sobre menor.\n");
        adicionarDiscoNoTopo(&torres[origem], disco);
        return 0;
    }

    adicionarDiscoNoTopo(&torres[destino], disco);
    movimentosFeitos++;
    return 1;
}

int jogoConcluido(int n) {
    return torres[2].topo == n - 1;
}
