#include <stdio.h>
#include <stdlib.h>
#include "3_funcoes.h"

int main() {
    int escolhaMenu;

    while(1) {
        printf("-----------Torre de Hanoi-----------\n");
        printf("[1] - Iniciar Jogo.\n");
        printf("[2] - Estatisticas.\n");
        printf("[3] - Sair do Jogo.\n");
        printf("Escolha: ");
        scanf("%d", &escolhaMenu);

        switch(escolhaMenu) {
            case 1:
                break;

            case 2:
                break
            case 3:
                return 0;

            default:
                printf("Opção invalida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
