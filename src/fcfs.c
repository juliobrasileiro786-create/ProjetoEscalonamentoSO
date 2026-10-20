#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    int chegada;
    int burst;
} Processo;

int main() {
    Processo fila[MAX], aux;
    int n, tempo = 0;
    int espera, retorno;
    int inicio = 0, fim = 0;
    float totalEspera = 0;

    // Quantidade de processos
    printf("Quantidade de processos: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Quantidade invalida!\n");
        return 1;
    }

    // Cadastro dos processos
    for (int i = 0; i < n; i++) {
        printf("\nProcesso P%d\n", i + 1);

        fila[fim].id = i + 1;

        printf("Tempo de chegada: ");
        if (scanf("%d", &fila[fim].chegada) != 1) {
            printf("Entrada invalida!\n");
            return 1;
        }

        printf("Tempo de CPU (burst): ");
        if (scanf("%d", &fila[fim].burst) != 1) {
            printf("Entrada invalida!\n");
            return 1;
        }

        if (fila[fim].chegada < 0 ||
            fila[fim].burst <= 0) {
            printf("Dados invalidos!\n");
            return 1;
        }

        fim++;
    }

    // Ordenar por tempo de chegada
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            if (fila[i].chegada > fila[j].chegada ||
                (fila[i].chegada == fila[j].chegada &&
                 fila[i].id > fila[j].id)) {

                aux = fila[i];
                fila[i] = fila[j];
                fila[j] = aux;
            }
        }
    }

    printf("\n===== ESCALONAMENTO FCFS =====\n");
    printf("Ordem de execucao:\n");

    // Executar processos da fila
    while (inicio < fim) {
        Processo p = fila[inicio];
        inicio++;

        // Verifica se a CPU esta ociosa
        if (tempo < p.chegada) {
            printf("CPU ociosa de %d ate %d\n",
                   tempo, p.chegada);

            tempo = p.chegada;
        }

        // Calcula o tempo de espera
        espera = tempo - p.chegada;

        printf("P%d: inicio=%d ", p.id, tempo);

        // Executa o processo
        tempo = tempo + p.burst;

        // Calcula o tempo de retorno
        retorno = tempo - p.chegada;

        totalEspera += espera;

        printf("fim=%d espera=%d retorno=%d\n",
               tempo, espera, retorno);
    }

    // Media de espera
    printf("\nTempo medio de espera: %.2f\n",
           totalEspera / n);

    printf("Tempo total da simulacao: %d\n", tempo);

    return 0;
}