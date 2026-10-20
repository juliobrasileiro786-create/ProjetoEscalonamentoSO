#include <stdio.h>

typedef struct
{
    int id;
    int chegada;
    int duracao;
    int executado;
} Processo;

int main()
{
    int n;

    printf("Quantos processos quer cadastrar? ");

    while (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Quantidade invalida. Digite um inteiro maior que zero: ");
        while (getchar() != '\n')
            ;
    }

    Processo processos[n];

    for (int i = 0; i < n; i++)
    {
        processos[i].id = i + 1;
        processos[i].executado = 0;

        printf("Tempo de chegada do processo P%d: ", processos[i].id);

        while (scanf("%d", &processos[i].chegada) != 1 ||
               processos[i].chegada < 0)
        {
            printf("Tempo invalido. Digite um inteiro maior ou igual a zero: ");
            while (getchar() != '\n')
                ;
        }

        printf("Duracao do processo P%d: ", processos[i].id);

        while (scanf("%d", &processos[i].duracao) != 1 ||
               processos[i].duracao <= 0)
        {
            printf("Duracao invalida. Digite um inteiro maior que zero: ");
            while (getchar() != '\n')
                ;
        }
    }

    printf("\nProcessos cadastrados:\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d | Chegada: %d | Duracao: %d\n",
               processos[i].id,
               processos[i].chegada,
               processos[i].duracao);
    }

    int tempo = 0;
    int concluidos = 0;

    printf("\nOrdem de execucao:\n");

    while (concluidos < n)
    {
        int menor = -1;

        for (int i = 0; i < n; i++)
        {
            if (processos[i].executado == 0 &&
                processos[i].chegada <= tempo)
            {
                if (menor == -1 ||
                    processos[i].duracao < processos[menor].duracao)
                {
                    menor = i;
                }
            }
        }

        if (menor == -1)
        {
            tempo++;
        }
        else
        {
            printf("P%d: %d ate %d\n",
                   processos[menor].id,
                   tempo,
                   tempo + processos[menor].duracao);

            tempo += processos[menor].duracao;
            processos[menor].executado = 1;
            concluidos++;
        }
    }

    return 0;
}