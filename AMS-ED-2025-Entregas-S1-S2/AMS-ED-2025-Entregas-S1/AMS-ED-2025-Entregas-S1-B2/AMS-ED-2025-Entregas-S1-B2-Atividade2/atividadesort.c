/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B2 Atividade 2                       */
/*             Objetivo: <<        booble sort       >>                              */
/*                                                                                  */
/*                                  Autor: Vivian zanon                           */
/*                                                                    Data:06/05/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

void preencherArray(int* array, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Informe o número %d: ", i + 1);
        scanf("%d", &array[i]);
    }
}

void ordenarPorBolha(int* array, int quantidade) {
    int temp;
    int trocou;
    
    for (int i = 0; i < quantidade - 1; i++) {
        trocou = 0;
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                trocou = 1;
            }
        }
        // Se não houve troca, o array já está ordenado
        if (!trocou) {
            break;
        }
    }
}

void mostrarArray(int* array, int quantidade) {
    printf("\nOs números em ordem crescente são:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int quantidade;

    printf("Quantos números você gostaria de inserir? ");
    scanf("%d", &quantidade);

    int* array = (int*) malloc(quantidade * sizeof(int));
    if (!array) {
        printf("Falha ao alocar memória.\n");
        return 1;
    }

    preencherArray(array, quantidade);
    ordenarPorBolha(array, quantidade);
    mostrarArray(array, quantidade);

    free(array);
    return 0;
}
