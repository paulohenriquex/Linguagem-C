#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

typedef struct
{
    float montante, txjuros, subtotal, juros, rendimentoliq, rendimentomensal, vlimposto;
    int periodo;

} juroscompostoss;
juroscompostoss jc;

void juroscompostos()
{
    float rendimentopercia;

    setlocale(LC_ALL, "");
    printf("Qual o montante inical? \n");
    scanf("%f", &jc.montante);

    printf("Quantos meses de investimento? \n");
    scanf("%d", &jc.periodo);

    printf("Qual a taxa de juros anual? \n");
    scanf("%f", &jc.txjuros);

    jc.txjuros = jc.txjuros / 100 / 12;
    jc.subtotal = jc.montante * pow((1 + jc.txjuros), jc.periodo);
    jc.juros = jc.subtotal - jc.montante;
    jc.vlimposto = jc.juros * 0.20;
    jc.rendimentoliq = jc.juros - (jc.juros * 0.20);
    jc.rendimentomensal = jc.rendimentoliq / 12;
    rendimentopercia = (jc.subtotal / jc.montante);

    printf("O valor total ser� de: R$%.2f\n", jc.subtotal);
    printf("O rendimento foi de R$ %.2f\n", jc.juros);
    printf("O valor do imposto de renda ser� de: R$%.2f\n", jc.vlimposto);
    printf("O rendimento l�quido ser� de R$ %.2f\n", jc.rendimentoliq);
    printf("O rendimento mensal ser� de: %.2f \n\n", jc.rendimentomensal);
    printf("O rendimento ser� de: %.2f%%\n", rendimentopercia);
    system("pause");
}
