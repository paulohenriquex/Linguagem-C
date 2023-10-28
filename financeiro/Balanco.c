#include "func.h"

void balanco()
{
    int i = 0;

    float soma[12] = {0};

    receita = fopen("rec.txt", "r");

    while (fscanf(receita, "%d %s %d %f", &rec[i].id, rec[i].nome, &rec[i].mes, &rec[i].vl) != EOF)
    {
        printf("teste");
        if (rec[i].mes == 1)
            soma[0] += rec[i].vl;
        if (rec[i].mes == 2)
            soma[1] += rec[i].vl;
        if (rec[i].mes == 3)
            soma[2] += rec[i].vl;
        if (rec[i].mes == 4)
            soma[3] += rec[i].vl;
        if (rec[i].mes == 5)
            soma[4] += rec[i].vl;
        if (rec[i].mes == 6)
            soma[5] += rec[i].vl;
        if (rec[i].mes == 7)
            soma[6] += rec[i].vl;
        if (rec[i].mes == 8)
            soma[7] += rec[i].vl;
        if (rec[i].mes == 9)
            soma[8] += rec[i].vl;
        if (rec[i].mes == 10)
            soma[9] += rec[i].vl;
        if (rec[i].mes == 11)
            soma[10] += rec[i].vl;
        if (rec[i].mes == 12)
            soma[11] += rec[i].vl;
        i++;
    }
    i = 0;
    fclose(receita);

    despesa = fopen("des.txt", "r");

    while (fscanf(despesa, "%d %s %d %f", &des[i].id, des[i].nome, &des[i].mes, &des[i].vl) != EOF)
    {
        if (des[i].mes == 1)
            soma[0] -= des[i].vl;
        if (des[i].mes == 2)
            soma[1] -= des[i].vl;
        if (des[i].mes == 3)
            soma[2] -= des[i].vl;
        if (des[i].mes == 4)
            soma[3] -= des[i].vl;
        if (des[i].mes == 5)
            soma[4] -= des[i].vl;
        if (des[i].mes == 6)
            soma[5] -= des[i].vl;
        if (des[i].mes == 7)
            soma[6] -= des[i].vl;
        if (des[i].mes == 8)
            soma[7] -= des[i].vl;
        if (des[i].mes == 9)
            soma[8] -= des[i].vl;
        if (des[i].mes == 10)
            soma[9] -= des[i].vl;
        if (des[i].mes == 11)
            soma[10] -= des[i].vl;
        if (des[i].mes == 12)
            soma[11] -= des[i].vl;
        i++;
    }

    fclose(despesa);
    printf("\n\n");
    system("cls");
    printf("SALDO LIQUIDO POR MES\n\n\n");
    printf(" Jan  R$ %.2f\n", soma[0]);
    printf(" Fev  R$ %.2f\n", soma[1]);
    printf(" Mar  R$ %.2f\n", soma[2]);
    printf(" Abr  R$ %.2f\n", soma[3]);
    printf(" Mai  R$ %.2f\n", soma[4]);
    printf(" Jun  R$ %.2f\n", soma[5]);
    printf(" Jul  R$ %.2f\n", soma[6]);
    printf(" Ago  R$ %.2f\n", soma[7]);
    printf(" Set  R$ %.2f\n", soma[8]);
    printf(" Out  R$ %.2f\n", soma[9]);
    printf(" Nov  R$ %.2f\n", soma[10]);
    printf(" Dez  R$ %.2f\n", soma[11]);

    printf("\n\n");
}
