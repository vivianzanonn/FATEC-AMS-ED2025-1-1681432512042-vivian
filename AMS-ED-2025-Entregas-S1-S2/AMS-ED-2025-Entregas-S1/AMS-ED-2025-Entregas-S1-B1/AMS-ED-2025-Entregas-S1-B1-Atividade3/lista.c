#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    int numero;
    char cliente[50];
    char descricao[100];
    int quantidade;
    char status[20];
    struct Pedido* prox;
} Pedido;

Pedido* criarPedido(int numero, char cliente[], char descricao[], int quantidade, char status[]) {
    Pedido* novo = (Pedido*)malloc(sizeof(Pedido));
    if (novo == NULL) {
        printf("Erro na alocação de memória!\n");
        exit(1);
    }
    novo->numero = numero;
    strcpy(novo->cliente, cliente);
    strcpy(novo->descricao, descricao);
    novo->quantidade = quantidade;
    strcpy(novo->status, status);
    novo->prox = NULL;
    return novo;
}

void inserirPedido(Pedido** head, Pedido* novo) {
    novo->prox = *head;
    *head = novo;
}

int verificarNumeroPedido(Pedido *head, int numero) {
    Pedido * atual = head;
    while (atual != NULL) {
        if (atual->numero == numero) {
            return 1; 
        }
        atual = atual->prox;
    }
    return 0;
}

Pedido* obterPedido(Pedido* head, int numero) {
    Pedido* atual = head;
    while (atual != NULL) {
        if (atual->numero == numero) {
            return atual; 
        }
        atual = atual->prox;
    }
    return NULL;
}

void atualizarStatusPedido(Pedido* head, int numero) {
    Pedido* pedido = obterPedido(head, numero);
    if (pedido != NULL) {
        char novoStatus[20];
        do {
            printf("Novo status (pendente/preparando/pronto/entregue): ");
            scanf("%s", novoStatus);
            if (strcmp(novoStatus, "pendente") != 0 && strcmp(novoStatus, "preparando") != 0 &&
                strcmp(novoStatus, "pronto") != 0 && strcmp(novoStatus, "entregue") != 0) {
                printf("Status inválido. Tente novamente.\n");
            }
        } while (strcmp(novoStatus, "pendente") != 0 && strcmp(novoStatus, "preparando") != 0 &&
                 strcmp(novoStatus, "pronto") != 0 && strcmp(novoStatus, "entregue") != 0);

        strcpy(pedido->status, novoStatus);
        printf("Status atualizado com sucesso!\n");
    } else {
        printf("Pedido não encontrado.\n");
    }
}

void exibirPedidos(Pedido* head) {
    Pedido* atual = head;
    if (atual == NULL) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }
    while (atual != NULL) {
        printf("Pedido #%d - Cliente: %s - %s - Quantidade: %d - Status: %s\n",
               atual->numero, atual->cliente, atual->descricao, atual->quantidade, atual->status);
        atual = atual->prox;
    }
}

void liberarLista(Pedido **head) {
    Pedido* atual = *head;
    Pedido* temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *head = NULL;
}

void deletarPedido(Pedido** head, int numero) {
    if (*head == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Pedido* atual = *head;
    Pedido* anterior = NULL;

  
    if (atual != NULL && atual->numero == numero) {
        *head = atual->prox;  
        free(atual);         
        printf("Pedido #%d removido com sucesso!\n", numero);
        return;
    }

    
    while (atual != NULL && atual->numero != numero) {
        anterior = atual;
        atual = atual->prox;
    }

    
    if (atual == NULL) {
        printf("Pedido #%d não encontrado.\n", numero);
        return;
    }

    
    anterior->prox = atual->prox;
    free(atual);
    printf("Pedido #%d removido com sucesso!\n", numero);
}

int main() {
    Pedido* head = NULL; 
    int opcao;

    do {
        printf("\n--- MENU DE GERENCIAMENTO DE PEDIDOS ---\n");
        printf("1. Inserir Pedido\n");
        printf("2. Exibir Pedidos\n");
        printf("3. Obter Pedido\n");
        printf("4. Atualizar Status do Pedido\n");
        printf("5. Deletar da lista\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int numero, quantidade;
                char cliente[50], descricao[100], status[20];

                do {
                    printf("Número do pedido: ");
                    scanf("%d", &numero);
                    if (numero <= 0) {
                        printf("Número do pedido deve ser positivo!\n");
                    } else if (verificarNumeroPedido(head, numero)) {
                        printf("Número do pedido já existe. Tente novamente.\n");
                    }
                } while (numero <= 0 || verificarNumeroPedido(head, numero));

                printf("Nome do cliente: ");
                scanf(" %[^\n]", cliente);

                printf("Descrição do pedido: ");
                scanf(" %[^\n]", descricao);

                do {
                    printf("Quantidade: ");
                    scanf("%d", &quantidade);
                    if (quantidade < 0) {
                        printf("Quantidade não pode ser negativa! Tente novamente.\n");
                    }
                } while (quantidade < 0);

                do {
                    printf("Status (pendente/preparando/pronto/entregue): ");
                    scanf("%s", status);
                    if (strcmp(status, "pendente") != 0 && strcmp(status, "preparando") != 0 &&
                        strcmp(status, "pronto") != 0 && strcmp(status, "entregue") != 0) {
                        printf("Status inválido. Tente novamente.\n");
                    }
                } while (strcmp(status, "pendente") != 0 && strcmp(status, "preparando") != 0 &&
                         strcmp(status, "pronto") != 0 && strcmp(status, "entregue") != 0);

                Pedido* novoPedido = criarPedido(numero, cliente, descricao, quantidade, status);
                inserirPedido(&head, novoPedido);
                printf("Pedido inserido com sucesso!\n");
                break;
            }
            case 2:
                exibirPedidos(head);
                break;
            case 3: {
                int numero;
                printf("Informe o número do pedido para buscar: ");
                scanf("%d", &numero);
                Pedido* pedido = obterPedido(head, numero);
                if (pedido != NULL) {
                    printf("Pedido encontrado: #%d - Cliente: %s - %s - Quantidade: %d - Status: %s\n",
                           pedido->numero, pedido->cliente, pedido->descricao, pedido->quantidade, pedido->status);
                } else {
                    printf("Pedido não encontrado.\n");
                }
                break;
            }
            case 4: {
                int numero;
                printf("Informe o número do pedido para atualizar o status: ");
                scanf("%d", &numero);
                atualizarStatusPedido(head, numero);
                break;
            }
            case 5: {
                int numero;
                printf("Informe o número do pedido para deletar: ");
                scanf("%d", &numero);
                deletarPedido(&head, numero);
                break;
            }
            case 6: {
                printf("Encerrando o programa...\n");
                liberarLista(&head);
                break;
            }
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
