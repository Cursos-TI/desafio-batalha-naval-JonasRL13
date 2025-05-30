#include <stdio.h>

#define LINHA 10
#define COLUNA 10
#define TAMANHO_NAVIO 3

int main() {
    int tabuleiro[LINHA][COLUNA];
    int i, j;

    // Inicializa o tabuleiro com 0 (água)
    for (i = 0; i < LINHA; i++) {
        for (j = 0; j < COLUNA; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Posicionamento dos navios (tamanho fixo 3)

    // Navio Horizontal - Exemplo: linha 1, coluna 1
    int linhaH = 1;
    int colunaH = 1;
    int valido = 1;

    // Verifica se cabe e não sobrepõe
    if (linhaH >= 0 && linhaH < LINHA && colunaH >= 0 && colunaH + TAMANHO_NAVIO - 1 < COLUNA) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaH][colunaH + i] != 0) {
                valido = 0;
                break;
            }
        }
        if (valido) {
            for (i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = 3;
            }
        } else {
            printf("Erro: navio horizontal sobreposto\n");
        }
    } else {
        printf("Erro: navio horizontal fora do tabuleiro\n");
    }

    // Navio Vertical - Exemplo: linha 4, coluna 5
    int linhaV = 4;
    int colunaV = 5;
    valido = 1;

    if (linhaV >= 0 && linhaV + TAMANHO_NAVIO - 1 < LINHA && colunaV >= 0 && colunaV < COLUNA) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] != 0) {
                valido = 0;
                break;
            }
        }
        if (valido) {
            for (i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = 3;
            }
        } else {
            printf("Erro: navio vertical sobreposto\n");
        }
    } else {
        printf("Erro: navio vertical fora do tabuleiro\n");
    }

    // Navio Diagonal Descendente (linha e coluna aumentam)
    // Exemplo: linha 6, coluna 2
    int linhaD1 = 6;
    int colunaD1 = 2;
    valido = 1;

    if (linhaD1 >= 0 && linhaD1 + TAMANHO_NAVIO - 1 < LINHA && colunaD1 >= 0 && colunaD1 + TAMANHO_NAVIO - 1 < COLUNA) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaD1 + i][colunaD1 + i] != 0) {
                valido = 0;
                break;
            }
        }
        if (valido) {
            for (i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaD1 + i][colunaD1 + i] = 3;
            }
        } else {
            printf("Erro: navio diagonal descendente sobreposto\n");
        }
    } else {
        printf("Erro: navio diagonal descendente fora do tabuleiro\n");
    }

    // Navio Diagonal Ascendente (linha diminui, coluna aumenta)
    // Exemplo: linha 8, coluna 4
    int linhaD2 = 8;
    int colunaD2 = 4;
    valido = 1;

    if (linhaD2 - (TAMANHO_NAVIO - 1) >= 0 && colunaD2 >= 0 && colunaD2 + TAMANHO_NAVIO - 1 < COLUNA) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaD2 - i][colunaD2 + i] != 0) {
                valido = 0;
                break;
            }
        }
        if (valido) {
            for (i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaD2 - i][colunaD2 + i] = 3;
            }
        } else {
            printf("Erro: navio diagonal ascendente sobreposto\n");
        }
    } else {
        printf("Erro: navio diagonal ascendente fora do tabuleiro\n");
    }

    // Exibir tabuleiro
    printf("\n  ");
    // Cabeçalho colunas (A-J)
    for (j = 0; j < COLUNA; j++) {
        printf(" %c", 'A' + j);
    }
    printf("\n");

    for (i = 0; i < LINHA; i++) {
        printf("%2d", i + 1); // número da linha
        for (j = 0; j < COLUNA; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
