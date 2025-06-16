#ifndef TORRE_HANOI_H
#define TORRE_HANOI_H
typedef struct {
    int* discos;
    int topo;
    int capacidade;
} Pilha;

extern Pilha torres[3];
extern int movimentosFeitos;

void criandoUmaPilha(Pilha* p, int capacidade);
void limparPilha(Pilha* p);
int adicionarDiscoNoTopo(Pilha* p, int valor);
int removerDoTopo(Pilha* p, int* valor);

#endif
