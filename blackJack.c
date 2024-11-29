#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int qntd;
    char simbolo;
    int valor;
} Carta;

Carta* criaBaralho() {
    int num = 13;
    char simbolos[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'};

    Carta *baralho = (Carta *)malloc(num * sizeof(Carta));
    if (baralho == NULL) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }
    for (int i = 0; i < num; i++) {
        baralho[i].qntd = 4;
        baralho[i].simbolo = simbolos[i];
        baralho[i].valor = i + 1;
    }
    return baralho;
}

void swap(Carta *c, int a, int b) {
    Carta aux = c[a];
    c[a] = c[b];
    c[b] = aux;
}

void embaralhar(Carta *c, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(c, i, j);
    }
}

int calculaSoma(Carta *cartas, int n) {
    int soma = 0;
    for(int i = 0; i < n; i++) {
        soma += cartas[i].valor;
    }
    return soma;
}

void listaBaralho(Carta *c, Carta *d, int n, int m) {
    system("cls");
    printf("Meu Baralho: \n");
    for (int i = 0; i < n; i++) {
        printf("\tqntd: %d \tsimbolo: %c \tvalor: %d\n\n", c[i].qntd, c[i].simbolo, c[i].valor);
    }
    printf("soma: %d\n\n", calculaSoma(c, n));

    printf("Dealer Baralho: \n");
    for (int i = 0; i < m; i++) {
        printf("\tqntd: %d \tsimbolo: %c \tvalor: %d\n\n", d[i].qntd, d[i].simbolo, d[i].valor);
    }
    printf("soma: %d\n", calculaSoma(d, m));
}

int adicionaCarta(Carta *baralhoPrincipal, Carta *baralhoJogador, int *nSize, int indiceCarta) {
    if (baralhoPrincipal[indiceCarta].qntd > 0) {
        baralhoJogador[*nSize] = baralhoPrincipal[indiceCarta];
        (*nSize)++;
        baralhoPrincipal[indiceCarta].qntd--;
        return 1;
    }
    return 0;
}

void game(Carta *c) {
    int num = 13;
    Carta *meuBaralho = (Carta *)malloc(num * sizeof(Carta));
    Carta *dealerBaralho = (Carta *)malloc(num * sizeof(Carta));
    int n_size = 0, m_size = 0;

    int end, soma, soma2 = 0;

    do {
        scanf("%d", &end);
        if (end != 1) return;

        int random, random2;
        do {
            random = rand() % num;
            random2 = rand() % num;
        } while (c[random].qntd <= 0 && c[random2].qntd <= 0);

        if (adicionaCarta(c, meuBaralho, &n_size, random)) {
            soma = calculaSoma(meuBaralho, n_size);
        }

        if (soma2 <= 17) {
            if (adicionaCarta(c, dealerBaralho, &m_size, random2)) {
                soma2 = calculaSoma(dealerBaralho, m_size);
            }
        }

        if (soma > 21) {
            printf("perdeu, soma: %d somaDealer: %d\n", soma, soma2);
            return;
        } else if (soma2 > 21) {
            printf("ganhou, soma: %d somaDealer: %d\n", soma, soma2);
            return;
        }

        printf("\n\n");
        listaBaralho(meuBaralho, dealerBaralho, n_size, m_size);

    } while (end);

    while (soma2 <= 17) {
        int random;
        do {
            random = rand() % num;
        } while (c[random].qntd <= 0);
        if (adicionaCarta(c, dealerBaralho, &m_size, random)) {
            soma2 = calculaSoma(dealerBaralho, m_size);
        }

        if (soma2 > 21) {
            printf("ganhou, soma: %d somaDealer: %d\n", soma, soma2);
            return;
        }
    }

    if (soma == soma2) {
        printf("empate, soma: %d somaDealer: %d\n", soma, soma2);
    } else if (soma > soma2) {
        printf("ganhou, soma: %d somaDealer: %d\n", soma, soma2);
    } else {
        printf("perdeu, soma: %d somaDealer: %d\n", soma, soma2);
    }

    free(meuBaralho);
    free(dealerBaralho);
}

int main() {
    srand(time(0));

    Carta *cartas = criaBaralho();
    embaralhar(cartas, 13);

    game(cartas);

    free(cartas);

    return 0;
}
