#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]; // Matriz do tabuleiro 10x10
    int navio_horizontal[TAM_NAVIO] = {3, 3, 3};  // Navio horizontal
    int navio_vertical[TAM_NAVIO] = {3, 3, 3};    // Navio vertical

    // Inicializa o tabuleiro com 0 (água)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Coordenadas iniciais do navio horizontal
    int linha_h = 2;
    int coluna_h = 4;

    // Verifica se o navio horizontal cabe e não colide
    if (coluna_h + TAM_NAVIO <= TAM_TABULEIRO) {
        int pode_posicionar = 1;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha_h][coluna_h + i] != 0) {
                pode_posicionar = 0;
                break;
            }
        }

        // Posiciona o navio horizontal
        if (pode_posicionar) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linha_h][coluna_h + i] = navio_horizontal[i];
            }
        } else {
            printf("Erro: colisão ao posicionar navio horizontal!\n");
        }
    } else {
        printf("Erro: navio horizontal fora do tabuleiro!\n");
    }

    // Coordenadas iniciais do navio vertical
    int linha_v = 5;
    int coluna_v = 1;

    // Verifica se o navio vertical cabe e não colide
    if (linha_v + TAM_NAVIO <= TAM_TABULEIRO) {
        int pode_posicionar = 1;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha_v + i][coluna_v] != 0) {
                pode_posicionar = 0;
                break;
            }
        }

        // Posiciona o navio vertical
        if (pode_posicionar) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linha_v + i][coluna_v] = navio_vertical[i];
            }
        } else {
            printf("Erro: colisão ao posicionar navio vertical!\n");
        }
    } else {
        printf("Erro: navio vertical fora do tabuleiro!\n");
    }

    // Exibe o tabuleiro
    printf("\n--- TABULEIRO BATALHA NAVAL ---\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
