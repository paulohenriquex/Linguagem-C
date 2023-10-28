#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

void investimentofiss()
{
    setlocale(LC_ALL, "");

    float vlinvestido, vlcota, qntcotas, vldividendo, divyield;
    char nomefii[50];

    printf("Digite o nome do FII: ");
    scanf("%s", nomefii);

    printf("Digite o valor investido: ");
    scanf("%f", &vlinvestido);

    printf("Digite o valor da cota: ");
    scanf("%f", &vlcota);

    printf("Digite o valor do dividendo mensal: ");
    scanf("%f", &vldividendo);

    system("cls");

    qntcotas = vlinvestido / vlcota;
    divyield = (vldividendo * 100 / vlinvestido) * 100;
    printf("Você tem %.2f cotas do fundo %s\n", qntcotas, nomefii);
    printf("O percentual de retorno é: %.2f%%\n", divyield);

    system("pause");
}