#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

typedef struct {
    char tipo;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX_FILA];
    int inicio, fim, total;
} Fila;

// Estrutura da pilha
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// Funcoes da fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

Peca desenfileirar(Fila *f) {
    Peca vazia = {'?', -1};
    if (filaVazia(f)) return vazia;
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    return p;
}

void mostrarFila(Fila *f) {
    printf("Fila: ");
    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }
    printf("\n");
}

// Funcoes da pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

void empilhar(Pilha *p, Peca x) {
    if (pilhaCheia(p)) return;
    p->itens[++p->topo] = x;
}

Peca desempilhar(Pilha *p) {
    Peca vazia = {'?', -1};
    if (pilhaVazia(p)) return vazia;
    return p->itens[p->topo--];
}

Peca topo(Pilha *p) {
    Peca vazia = {'?', -1};
    if (pilhaVazia(p)) return vazia;
    return p->itens[p->topo];
}

void mostrarPilha(Pilha *p) {
    printf("Pilha (Topo -> Base): ");
    if (pilhaVazia(p)) {
        printf("(vazia)\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}

// Gerador de pecas
char tipos[] = {'I', 'O', 'T', 'L'};

Peca gerarPeca(int *proxID) {
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = (*proxID)++;
    return p;
}

// Programa principal
int main() {
    srand(time(NULL));
    Fila fila;
    Pilha reserva;
    inicializarFila(&fila);
    inicializarPilha(&reserva);
    int proxID = 0;

    for (int i = 0; i < MAX_FILA; i++) {
        enfileirar(&fila, gerarPeca(&proxID));
    }

    int opcao;
    do {
        printf("\n=== NIVEL MESTRE ===\n");
        mostrarFila(&fila);
        mostrarPilha(&reserva);
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca (fila -> pilha)\n");
        printf("3 - Usar peca reservada\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Troca multipla (3 pecas)\n");
        printf("6 - Inverter fila\n");
        printf("0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = desenfileirar(&fila);
            if (jogada.id != -1) {
                printf("Peca jogada: [%c %d]\n", jogada.tipo, jogada.id);
                enfileirar(&fila, gerarPeca(&proxID));
            }
        } else if (opcao == 2) {
            if (!filaVazia(&fila) && !pilhaCheia(&reserva)) {
                Peca movida = desenfileirar(&fila);
                empilhar(&reserva, movida);
                printf("Peca reservada: [%c %d]\n", movida.tipo, movida.id);
                enfileirar(&fila, gerarPeca(&proxID));
            } else {
                printf("Nao foi possivel reservar a peca.\n");
            }
        } else if (opcao == 3) {
            Peca usada = desempilhar(&reserva);
            if (usada.id != -1) {
                printf("Peca usada da reserva: [%c %d]\n", usada.tipo, usada.id);
                enfileirar(&fila, gerarPeca(&proxID));
            }
        } else if (opcao == 4) {
            if (!filaVazia(&fila) && !pilhaVazia(&reserva)) {
                int idx = fila.inicio;
                Peca temp = fila.itens[idx];
                fila.itens[idx] = reserva.itens[reserva.topo];
                reserva.itens[reserva.topo] = temp;
                printf("Troca simples realizada!\n");
            } else {
                printf("Nao ha pecas suficientes para trocar.\n");
            }
        } else if (opcao == 5) {
            if (fila.total >= 3 && reserva.topo + 1 >= 3) {
                for (int i = 0; i < 3; i++) {
                    int idx = (fila.inicio + i) % MAX_FILA;
                    Peca temp = fila.itens[idx];
                    fila.itens[idx] = reserva.itens[reserva.topo - i];
                    reserva.itens[reserva.topo - i] = temp;
                }
                printf("Troca multipla (3 pecas) concluida!\n");
            } else {
                printf("Nao ha pecas suficientes para troca multipla.\n");
            }
        } else if (opcao == 6) {
            Pilha aux;
            inicializarPilha(&aux);
            while (!filaVazia(&fila)) empilhar(&aux, desenfileirar(&fila));
            while (!pilhaVazia(&aux)) enfileirar(&fila, desempilhar(&aux));
            printf("Fila invertida!\n");
        }
    } while (opcao != 0);

    printf("Encerrando nivel mestre...\n");
    return 0;
}