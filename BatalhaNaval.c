#include <stdio.h>

#define LINHA 10
#define COLUNA 10

// Tamanho das matrizes de habilidade (área de efeito)
#define HABILIDADE_TAM 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[LINHA][COLUNA]) {
    for (int i = 0; i < LINHA; i++) {
        for (int j = 0; j < COLUNA; j++) {
            tabuleiro[i][j] = 0; // água
        }
    }
}

// Função para posicionar um navio no tabuleiro horizontal ou vertical
// navio de tamanho 3, orientação: 'H' ou 'V'
int posicionarNavio(int tabuleiro[LINHA][COLUNA], int linha, int coluna, char orientacao) {
    // Verifica limites e se espaço está livre (0)
    if (orientacao == 'H') {
        if (coluna < 0 || coluna + 2 >= COLUNA || linha < 0 || linha >= LINHA)
            return 0;
        for (int i = 0; i < 3; i++)
            if (tabuleiro[linha][coluna + i] != 0)
                return 0;
        for (int i = 0; i < 3; i++)
            tabuleiro[linha][coluna + i] = 3; // navio
        return 1;
    } else if (orientacao == 'V') {
        if (linha < 0 || linha + 2 >= LINHA || coluna < 0 || coluna >= COLUNA)
            return 0;
        for (int i = 0; i < 3; i++)
            if (tabuleiro[linha + i][coluna] != 0)
                return 0;
        for (int i = 0; i < 3; i++)
            tabuleiro[linha + i][coluna] = 3; // navio
        return 1;
    }
    return 0;
}

// Função para posicionar navio diagonal descendente (linha e coluna aumentam)
int posicionarNavioDiagonalDesc(int tabuleiro[LINHA][COLUNA], int linha, int coluna) {
    if (linha < 0 || linha + 2 >= LINHA || coluna < 0 || coluna + 2 >= COLUNA)
        return 0;
    for (int i = 0; i < 3; i++)
        if (tabuleiro[linha + i][coluna + i] != 0)
            return 0;
    for (int i = 0; i < 3; i++)
        tabuleiro[linha + i][coluna + i] = 3;
    return 1;
}

// Função para posicionar navio diagonal ascendente (linha diminui, coluna aumenta)
int posicionarNavioDiagonalAsc(int tabuleiro[LINHA][COLUNA], int linha, int coluna) {
    if (linha - 2 < 0 || coluna < 0 || coluna + 2 >= COLUNA || linha >= LINHA)
        return 0;
    for (int i = 0; i < 3; i++)
        if (tabuleiro[linha - i][coluna + i] != 0)
            return 0;
    for (int i = 0; i < 3; i++)
        tabuleiro[linha - i][coluna + i] = 3;
    return 1;
}

// Função para construir matriz de habilidade Cone (5x5)
// O cone aponta para baixo, com origem no topo central (0,2)
void construirCone(int cone[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            // Lógica do cone: 
            // A cada linha descendo, a largura aumenta centralizada
            int centro = HABILIDADE_TAM / 2; // 2
            int alcance = i; // para expandir
            if (j >= centro - alcance && j <= centro + alcance)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Função para construir matriz de habilidade Cruz (5x5)
// Cruz com origem no centro (2,2)
void construirCruz(int cruz[HABILIDADE_TAM][HABILIDADE_TAM]) {
    int centro = HABILIDADE_TAM / 2;
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Função para construir matriz de habilidade Octaedro (5x5)
// Losango com origem no centro (2,2)
void construirOctaedro(int octaedro[HABILIDADE_TAM][HABILIDADE_TAM]) {
    int centro = HABILIDADE_TAM / 2;
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            // Condição para formar um losango:
            // |linha - centro| + |coluna - centro| <= centro
            if (abs(i - centro) + abs(j - centro) <= centro)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Função para sobrepor matriz de habilidade no tabuleiro
// origemLinha, origemColuna = posição central da habilidade no tabuleiro
// A área marcada com 1 na matriz de habilidade marca 5 no tabuleiro (área afetada)
// Verifica limites do tabuleiro para não sair fora
void aplicarHabilidade(int tabuleiro[LINHA][COLUNA], int habilidade[HABILIDADE_TAM][HABILIDADE_TAM], int origemLinha, int origemColuna) {
    int meio = HABILIDADE_TAM / 2;

    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (habilidade[i][j] == 1) {
                int tabLinha = origemLinha - meio + i;
                int tabColuna = origemColuna - meio + j;
                // Verifica limites
                if (tabLinha >= 0 && tabLinha < LINHA && tabColuna >= 0 && tabColuna < COLUNA) {
                    // Se não for navio, marca área de efeito
                    if (tabuleiro[tabLinha][tabColuna] == 0)
                        tabuleiro[tabLinha][tabColuna] = 5;
                }
            }
        }
    }
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[LINHA][COLUNA]) {
    printf("\n   ");
    // Cabeçalho colunas
    for (int c = 0; c < COLUNA; c++) {
        printf(" %d", c);
    }
    printf("\n");

    for (int i = 0; i < LINHA; i++) {
        printf("%2d ", i);
        for (int j = 0; j < COLUNA; j++) {
            if (tabuleiro[i][j] == 0)
                printf(" ~"); // água
            else if (tabuleiro[i][j] == 3)
                printf(" N"); // navio
            else if (tabuleiro[i][j] == 5)
                printf(" *"); // área de habilidade
            else
                printf(" ?"); // valor inesperado
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[LINHA][COLUNA];

    // Inicializa tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    // Horizontal (linha 1, coluna 1)
    if (!posicionarNavio(tabuleiro, 1, 1, 'H'))
        printf("Erro ao posicionar navio horizontal\n");
    // Vertical (linha 4, coluna 5)
    if (!posicionarNavio(tabuleiro, 4, 5, 'V'))
        printf("Erro ao posicionar navio vertical\n");
    // Diagonal descendente (linha 6, coluna 6)
    if (!posicionarNavioDiagonalDesc(tabuleiro, 6, 6))
        printf("Erro ao posicionar navio diagonal descendente\n");
    // Diagonal ascendente (linha 8, coluna 2)
    if (!posicionarNavioDiagonalAsc(tabuleiro, 8, 2))
        printf("Erro ao posicionar navio diagonal ascendente\n");

    // Cria matrizes de habilidade
    int cone[HABILIDADE_TAM][HABILIDADE_TAM];
    int cruz[HABILIDADE_TAM][HABILIDADE_TAM];
    int octaedro[HABILIDADE_TAM][HABILIDADE_TAM];

    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Define pontos de origem para as habilidades no tabuleiro
    int origemConeLinha = 2, origemConeColuna = 3;
    int origemCruzLinha = 5, origemCruzColuna = 7;
    int origemOctaedroLinha = 7, origemOctaedroColuna = 4;

    // Aplica habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Imprime o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}



//- ~ representa água (0).
//- N representa navio (3).
//- * representa área afetada pela habilidade (5).
