#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 30
#define TAM_COR  10
#define MAX_TERRITORIOS 50

// cada território tem nome, cor e tropas
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// cadastro básico dos territórios
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor (jogador): ");
        scanf(" %9s", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// mostra todos os territórios na tela
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n==== MAPA ====\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %s | %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// lógica do ataque simplificado
void atacar(Territorio* atacante, Territorio* defensor) {
    // não pode atacar a si mesmo
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não pode atacar a si mesmo.\n");
        return;
    }
    // precisa ter pelo menos 2 tropas pra atacar
    if (atacante->tropas < 2) {
        printf("Erro: precisa de pelo menos 2 tropas.\n");
        return;
    }

    // rolagem dos dados
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nAtaque: %s (%s) [%d] x %s (%s) [%d]\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    printf("Dados: A=%d D=%d\n", dadoA, dadoD);

    // se o atacante ganhar, troca a cor e move tropas
    if (dadoA > dadoD) {
        printf("%s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        int mover = atacante->tropas / 2;
        if (mover < 1) mover = 1;
        atacante->tropas -= mover;
        defensor->tropas = mover;
    } else {
        // se perder, só perde 1 tropa
        printf("Defesa venceu!\n");
        atacante->tropas--;
        if (atacante->tropas < 1) atacante->tropas = 1;
    }
}

int main() {
    srand(time(NULL));

    int qtd;
    printf("Quantos territórios (max %d)? ", MAX_TERRITORIOS);
    scanf("%d", &qtd);

    if (qtd > MAX_TERRITORIOS) qtd = MAX_TERRITORIOS;

    Territorio mapa[MAX_TERRITORIOS];

    cadastrarTerritorios(mapa, qtd);

    int continuar = 1;
    while (continuar) {
        exibirMapa(mapa, qtd);

        int a, d;
        printf("Índice atacante: ");
        scanf("%d", &a);
        printf("Índice defensor: ");
        scanf("%d", &d);

        if (a == d) {
            printf("Erro: não pode atacar o mesmo.\n");
        } else {
            atacar(&mapa[a], &mapa[d]);
        }

        printf("\nOutro ataque? (1=sim, 0=não): ");
        scanf("%d", &continuar);
    }

    printf("\nFim de jogo.\n");
    return 0;
}