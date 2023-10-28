#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <windows.h>

typedef struct
{
    float capitalaplicado, vlfinal, juros, txjuros, rendimento;
    int tempo;
} jurossimpless;
jurossimpless js;

void jurossimples()
{

    printf("Digite o valor do investimento: ");
    scanf("%f", &js.capitalaplicado);

    printf("Qual a taxa de juros anual: "); 
    scanf("%f", &js.txjuros);

    printf("Quanto tempo de investimento: ");
    scanf("%d", &js.tempo);

    js.txjuros = js.txjuros / 100 / 12;

    js.vlfinal = js.capitalaplicado + (js.capitalaplicado * js.txjuros * js.tempo);
    js.rendimento = (js.capitalaplicado * js.txjuros * js.tempo);

    printf("O valor final e de R$%.2f\n", js.vlfinal);
    printf("O rendimento foi de: R$%.2f\n", js.rendimento);
    system("pause");
    Sleep(5000);                
}
