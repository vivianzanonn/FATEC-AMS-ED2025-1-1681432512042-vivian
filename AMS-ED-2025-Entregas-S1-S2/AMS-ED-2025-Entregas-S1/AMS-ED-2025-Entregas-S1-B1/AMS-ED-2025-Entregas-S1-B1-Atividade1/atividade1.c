#include <stdio.h>


float aplicar_desconto(float *valorproduto, float desconto, char tipo) {
    if (tipo == 'p') { 
        *valorproduto -= (*valorproduto * (desconto / 100));
    } else if (tipo == 'r') { 
        *valorproduto -= desconto;
    }
    return 0;
}

int main() {
    float valorproduto, desconto, valorfinal;
    char tipodesconto ='a';

    printf("Digite o preço do produto: R$ ");
    scanf("%f", &valorproduto);

    float preco_original = valorproduto;

    printf("Digite o valor do desconto: ");
    scanf("%f", &desconto);


while(tipodesconto != 'r' && tipodesconto != 'p'){
     printf("O desconto deve ser aplicado em (p)orcentagem ou em (r)eais? ");
    scanf(" %c", &tipodesconto);
}
   

    aplicar_desconto(&valorproduto, desconto, tipodesconto);

    valorfinal = valorproduto;

    printf("Preço original: R$ %.2f\n", preco_original);
    printf("Desconto aplicado: R$ %.2f\n", (tipodesconto == 'p') ? (preco_original * (desconto / 100)) : desconto);
    printf("Preço final após desconto: R$ %.2f\n", valorfinal);

    return 0;
}