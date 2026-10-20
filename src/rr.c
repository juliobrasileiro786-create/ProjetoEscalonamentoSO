
#include <stdio.h>

int main() {
    int n, quantum;
    int tempo = 0;
    int concluidos = 0;

    printf("Quantidade de processos: ");
    scanf("%d", &n);

    int restante[n];

    for (int i = 0; i < n; i++) {
        printf("Tempo de CPU do P%d: ", i + 1);
        scanf("%d", &restante[i]);
    }

    printf("Quantum: ");
    scanf("%d", &quantum);

    while (concluidos < n) {
        for (int i = 0; i < n; i++) {
            if (restante[i] > 0) {
                int execucao;

                if (restante[i] < quantum) {
                    execucao = restante[i];
                } else {
                    execucao = quantum;
                }

                restante[i] -= execucao;
                tempo += execucao;

                printf("Tempo %d: P%d executou %d unidade(s)\n",
                       tempo, i + 1, execucao);

                if (restante[i] == 0) {
                    concluidos++;
                    printf("P%d terminou!\n", i + 1);
                }
            }
        }
    }

    printf("\nTodos os processos foram concluidos.\n");
    printf("Tempo total de CPU: %d\n", tempo);

    return 0;
}
