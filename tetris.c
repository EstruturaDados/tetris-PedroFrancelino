//DESAFIO TETRIS STACK - TEMA 3(NOVATO)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca elementos[MAX];
    int front;
    int rear;
    int count;
    int next_id;
} Fila;

void inicializar(Fila *f) {
    f->front = 0;
    f->rear = -1;
    f->count = 0;
    f->next_id = 0;
    
    // Gerar peças iniciais automaticamente
    char tipos[] = {'T', 'O', 'L', 'I', 'I'};
    for (int i = 0; i < MAX; i++) {
        Peca nova;
        nova.tipo = tipos[i];
        nova.id = f->next_id++;
        enqueue(f, nova);
    }
}

int estaVazia(Fila *f) {
    return f->count == 0;
}

int estaCheia(Fila *f) {
    return f->count == MAX;
}

void enqueue(Fila *f, Peca peca) {
    if (estaCheia(f)) {
        printf("Fila cheia! Nao e possivel inserir nova peca.\n");
    } else {
        f->rear = (f->rear + 1) % MAX;
        f->elementos[f->rear] = peca;
        f->count++;
    }
}

Peca dequeue(Fila *f) {
    Peca vazia = {' ', -1};
    
    if (estaVazia(f)) {
        printf("Fila vazia! Nao ha pecas para jogar.\n");
        return vazia;
    } else {
        Peca peca = f->elementos[f->front];
        f->front = (f->front + 1) % MAX;
        f->count--;
        return peca;
    }
}

void mostrarFila(Fila *f) {
    printf("Fila de Pecas: ");
    for (int i = 0; i < f->count; i++) {
        int idx = (f->front + i) % MAX;
        printf("[%c%d] ", f->elementos[idx].tipo, f->elementos[idx].id);
    }
    printf("\n");
}

Peca gerarPeca(Fila *f) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int index = rand() % 4;
    nova.tipo = tipos[index];
    nova.id = f->next_id++;
    return nova;
}

int main() {
    srand(time(NULL)); // Inicializar gerador de números aleatórios
    
    Fila fila;
    inicializar(&fila);

    int opcao;

    do {
        mostrarFila(&fila);
        printf("\n1 - Jogar Peca (dequeue)\n");
        printf("2 - Inserir Nova Peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                {
                    Peca jogada = dequeue(&fila);
                    if (jogada.id != -1) {
                        printf("Peca [%c%d] jogada!\n", jogada.tipo, jogada.id);
                    }
                }
                break;

            case 2:
                if (estaCheia(&fila)) {
                    printf("Fila cheia! Nao e possivel inserir nova peca.\n");
                } else {
                    Peca nova = gerarPeca(&fila);
                    enqueue(&fila, nova);
                    printf("Nova peca [%c%d] inserida!\n", nova.tipo, nova.id);
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

        printf("\n");

    } while (opcao != 0);

    return 0;
}