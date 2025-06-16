# Torre de Hanoi - Jogo em C99

Este projeto é uma implementação do clássico **jogo da Torre de Hanoi**, desenvolvida em linguagem C seguindo o padrão **C99**. O objetivo do jogo é mover todos os discos da haste de origem para a haste de destino, obedecendo às regras.

## Sobre o jogo

A Torre de Hanoi é um quebra-cabeça matemático que consiste em:

- Três hastes: origem, auxiliar e destino.
- Um número variável de discos de tamanhos diferentes.
- Somente um disco pode ser movido por vez.
- Um disco maior **nunca pode ser colocado sobre um menor**.

O desafio é mover todos os discos da haste de origem para a haste de destino, utilizando a haste auxiliar quando necessário.

## Funcionalidades

- Escolha do número de discos.
- Exibição visual do estado atual das torres.
- Contagem de movimentos.
- Nome do jogador.
- Interface simples no terminal.

## Como compilar

Você precisa ter o compilador **GCC** instalado. Para compilar o programa, use o terminal:

```bash
gcc 1_main.c 2_funcoes.c -o 5_torre_de_hanoi.exe

Terminal:

./5_torre_de_hanoi.exe

CMD: 

5_torre_de_hanoi.exe
