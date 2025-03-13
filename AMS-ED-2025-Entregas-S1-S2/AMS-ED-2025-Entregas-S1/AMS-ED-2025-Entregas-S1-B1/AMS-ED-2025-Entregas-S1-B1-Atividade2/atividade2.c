#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char identificacao[30];
    float *escrita;
    float *curriculo;
    float *pratica;
    float *banca;
    float notaFinal; 
} Participante;

void capturarNome(Participante *p) {
    printf("Informe o nome do participante: ");
    scanf("%s", p->identificacao);
}

void coletarNotas(float **notas, int qtd, const char *descricao) {
    *notas = (float *)malloc(qtd * sizeof(float));
    if (*notas == NULL) {
        printf("Falha ao alocar memoria para %s.\n", descricao);
        exit(1);
    }
    printf("Digite as %d notas para %s:\n", qtd, descricao);
    for (int i = 0; i < qtd; i++) {
        do {
            printf("Nota %d: ", i + 1);
            scanf("%f", &(*notas)[i]);
            if ((*notas)[i] < 0 || (*notas)[i] > 10) {
                printf("Valor invalido! As notas devem estar entre 0 e 10.\n");
            }
        } while ((*notas)[i] < 0 || (*notas)[i] > 10);
    }
}

float calcularSoma(float *valores, int *qtd) {
    float maior = valores[0], menor = valores[0], total = 0;
    int maiorIdx = 0, menorIdx = 0;

    for (int i = 1; i < *qtd; i++) {
        if (valores[i] > maior) {
            maior = valores[i];
            maiorIdx = i;
        }
        if (valores[i] < menor) {
            menor = valores[i];
            menorIdx = i;
        }
    }

    for (int i = 0; i < *qtd; i++) {
        if (i != maiorIdx && i != menorIdx) {
            total += valores[i];
        }
    }

    return total;
}

int ordenarNotas(const void *x, const void *y) {
    float notaX = ((Participante *)x)->notaFinal;
    float notaY = ((Participante *)y)->notaFinal;
    return (notaY > notaX) ? 1 : -1;
}

int main() {
    int totalParticipantes;

    do {
        printf("Informe o numero de participantes (Maximo 50): ");
        scanf("%d", &totalParticipantes);
        if (totalParticipantes <= 0 || totalParticipantes > 50) {
            printf("Valor invalido! Escolha entre 1 e 50 participantes.\n");
        }
    } while (totalParticipantes <= 0 || totalParticipantes > 50);

    Participante *lista = (Participante *)malloc(totalParticipantes * sizeof(Participante));
    if (lista == NULL) {
        printf("Erro ao alocar memoria para os participantes.\n");
        exit(1);
    }

    for (int i = 0; i < totalParticipantes; i++) {
        printf("\n--- Participante %d ---\n", i + 1);
        capturarNome(&lista[i]);
        coletarNotas(&lista[i].escrita, 4, "Prova Escrita");
        coletarNotas(&lista[i].curriculo, 5, "Analise Curricular");
        coletarNotas(&lista[i].pratica, 10, "Prova Pratica");
        coletarNotas(&lista[i].banca, 3, "Entrevista na Banca");

        int tamEscrita = 4, tamCurriculo = 5, tamPratica = 10, tamBanca = 3;
        float totalEscrita = calcularSoma(lista[i].escrita, &tamEscrita);
        float totalCurriculo = calcularSoma(lista[i].curriculo, &tamCurriculo);
        float totalPratica = calcularSoma(lista[i].pratica, &tamPratica);
        float totalBanca = calcularSoma(lista[i].banca, &tamBanca);

        lista[i].notaFinal = (totalEscrita * 0.3) + (totalCurriculo * 0.1) + (totalPratica * 0.4) + (totalBanca * 0.2);
    }

    qsort(lista, totalParticipantes, sizeof(Participante), ordenarNotas);

    printf("\n=== Top 5 Participantes com Melhores Notas ===\n");
    for (int i = 0; i < (totalParticipantes < 5 ? totalParticipantes : 5); i++) {
        printf("%d - %s: %.2f\n", i + 1, lista[i].identificacao, lista[i].notaFinal);

        free(lista[i].escrita);
        free(lista[i].curriculo);
        free(lista[i].pratica);
        free(lista[i].banca);
    }

    free(lista);
    return 0;
}