#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "3_funcoes.h"

#define MAXIMO 10

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
        printf("A torre de origem esta vazia!\n");
        return 0;
    }

    if (consultarTopoPilha(&torres[destino]) != -1 && consultarTopoPilha(&torres[destino]) < disco) {
        printf("Movimento invalido! Nao pode colocar disco maior sobre menor.\n");
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
void salvarHistorico(int discos, int movimentos, const char* nome) {
    FILE* f = fopen("historico.txt", "a");
    if (f == NULL) {
        printf("Erro ao salvar o historico!\n");
        return;
    }
    fprintf(f, "Jogador: %s | Discos: %d | Movimentos: %d\n", nome, discos, movimentos);
    fclose(f);
}

void mostrarHistorico() {
    FILE* f = fopen("historico.txt", "r");
    if (f == NULL) {
        printf("\nNenhum histórico encontrado.\n\n");
    } else {
        char linha[200];
        system("cls");
        printf("\n--- Historico de Jogadores ---\n");
        while (fgets(linha, sizeof(linha), f)) {
            printf("%s", linha);
        }
        fclose(f);
    }

    printf("\nPressione ENTER para voltar...");
    getchar(); getchar();
    system("cls");
}

void iniciarJogo() {
    int n;
    char origem, destino;
    char playerName[100];
    
    system("cls");
    printf("Digite seu nome: ");
    scanf(" %[^\n]", playerName);
    do {
        system("cls");
        printf("Digite o numero de discos (1 ate %d): ", MAXIMO);
        scanf("%d", &n);
    
        if (n < 1 || n > MAXIMO) {
            printf("Numero invalido! Tente novamente.\n");
            printf("Pressione ENTER para continuar...");
            while (getchar() != '\n'); // Limpa o buffer
            getchar();
        }
    
    } while (n < 1 || n > MAXIMO);

    inicializarTorres(n);

    while (!jogoConcluido(n)) {
        system("cls");  // Limpa a tela (Windows)
        exibirTorres(n);
        printf("\nDigite o movimento (ex: A C para mover de A para C): ");
        scanf(" %c %c", &origem, &destino);

        int o = origem - 'A';
        int d = destino - 'A';

        if (o < 0 || o > 2 || d < 0 || d > 2) {
            printf("Torre invalida! Use A, B ou C.\n");
            printf("Pressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();
            continue;
        }

        if (!moverDisco(o, d)) {
            printf("Movimento invalido. Tente novamente.\n");
            printf("Pressione ENTER para continuar...");
            while (getchar() != '\n'); // joga fora tudo até o fim da linha
            getchar(); // aguarda o ENTER do jogador
        }
    }

    system("cls");
    exibirTorres(n);
    printf("\nParabens %s! Voce completou a Torre de Hanoi em %d movimentos!\n", playerName, movimentosFeitos);
    salvarHistorico(n, movimentosFeitos, playerName);

    printf("\nPressione ENTER para voltar ao menu...");
    getchar(); // Consumir '\n'
    getchar(); 
    system("cls");
}
