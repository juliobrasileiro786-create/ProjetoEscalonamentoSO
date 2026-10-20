#include <stdio.h>
#include <stdbool.h>

#define MAX 50

typedef struct {
    int id;
    int chegada;
    int burst;
    int prioridade;
    int espera;
    int retorno;
} Processo;

typedef struct {
    Processo itens[MAX];
    int total;
} Fila;

void inicializar(Fila *f) {
    f->total = 0;
}

bool vazia(Fila *f) {
    return f->total == 0;
}

void enfileirar(Fila *f, Processo p) {
    int i = f->total - 1;
    while (i >= 0 && (f->itens[i].prioridade > p.prioridade || 
          (f->itens[i].prioridade == p.prioridade && f->itens[i].chegada > p.chegada))) {
        f->itens[i + 1] = f->itens[i];
        i--;
    }
    f->itens[i + 1] = p;
    f->total++;
}

Processo desenfileirar(Fila *f) {
    Processo p = f->itens[0];
    for (int i = 0; i < f->total - 1; i++) {
        f->itens[i] = f->itens[i + 1];
    }
    f->total--;
    return p;
}

int main() {
    int n;
    printf("Quantidade de processos: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    Processo p[n];
    bool entrou[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        entrou[i] = false;
        printf("\n--- Processo P%d ---\n", p[i].id);
        printf("Tempo de Chegada: ");
        scanf("%d", &p[i].chegada);
        printf("Tempo de Burst (CPU): ");
        scanf("%d", &p[i].burst);
        printf("Prioridade (menor = mais urgente): ");
        scanf("%d", &p[i].prioridade);
    }

    Fila fila;
    inicializar(&fila);

    int tempo = 0;
    int concluidos = 0;
    float soma_espera = 0;
    float soma_retorno = 0;

    printf("\nOrdem de Execução: ");

    while (concluidos < n) {
        for (int i = 0; i < n; i++) {
            if (!entrou[i] && p[i].chegada <= tempo) {
                enfileirar(&fila, p[i]);
                entrou[i] = true;
            }
        }

        if (vazia(&fila)) {
            tempo++;
            continue;
        }

        Processo atual = desenfileirar(&fila);
        printf("P%d ", atual.id);

        atual.espera = tempo - atual.chegada;
        tempo += atual.burst;
        atual.retorno = tempo - atual.chegada;

        soma_espera += atual.espera;
        soma_retorno += atual.retorno;
        concluidos++;
    }

    printf("\n\nTempo Médio de Espera: %.2f", soma_espera / n);
    printf("\nTempo Médio de Retorno: %.2f\n", soma_retorno / n);

    return 0;
}