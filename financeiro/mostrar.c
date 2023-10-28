#include "func.h"

void mostrarLista()
{
    float soma[12] = {0};
    int i = 0, op;

    printf("1 - Listar total receitas  por mes\n");
    printf("2 - Listar total despesas  por mes\n");
    scanf("%d", &op);

    if (op != 1 && op != 2)
    {
        printf("Opcao invalida\n");
        return;
    }

    if (op == 1)
    {
        receita = fopen("rec.txt", "r");

        while (fscanf(receita, "%d %s %d %f", &rec[i].id, rec[i].nome, &rec[i].mes, &rec[i].vl) != EOF)
        {
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

        fclose(receita);

        system("cls");
        printf("LISTA DE RECEITAS POR MES\n\n");

        printf("1 -\tJan\tR$%.2f\n", soma[0]);
        printf("2 -\tFev\tR$%.2f\n", soma[1]);
        printf("3 -\tMar\tR$%.2f\n", soma[2]);
        printf("4 -\tAbr\tR$%.2f\n", soma[3]);
        printf("5 -\tMai\tR$%.2f\n", soma[4]);
        printf("6 -\tJun\tR$%.2f\n", soma[5]);
        printf("7 -\tJul\tR$%.2f\n", soma[6]);
        printf("8 -\tAgo\tR$%.2f\n", soma[7]);
        printf("9 -\tSet\tR$%.2f\n", soma[8]);
        printf("10 -\tOut\tR$%.2f\n", soma[9]);
        printf("11 -\tNov\tR$%.2f\n", soma[10]);
        printf("12 -\tDez\tR$%.2f\n", soma[11]);
        printf("\n\n");
    }
    if (op == 2)
    {
        i = 0;

        despesa = fopen("des.txt", "r");

        while (fscanf(despesa, "%d %s %d %f", &des[i].id, des[i].nome, &des[i].mes, &des[i].vl) != EOF)
        {
            if (des[i].mes == 1)
                soma[0] += des[i].vl;
            if (des[i].mes == 2)
                soma[1] += des[i].vl;
            if (des[i].mes == 3)
                soma[2] += des[i].vl;
            if (des[i].mes == 4)
                soma[3] += des[i].vl;
            if (des[i].mes == 5)
                soma[4] += des[i].vl;
            if (des[i].mes == 6)
                soma[5] += des[i].vl;
            if (des[i].mes == 7)
                soma[6] += des[i].vl;
            if (des[i].mes == 8)
                soma[7] += des[i].vl;
            if (des[i].mes == 9)
                soma[8] += des[i].vl;
            if (des[i].mes == 10)
                soma[9] += des[i].vl;
            if (des[i].mes == 11)
                soma[10] += des[i].vl;
            if (des[i].mes == 12)
                soma[11] += des[i].vl;
            i++;
        }

        fclose(despesa);

        system("cls");
        printf("LISTA DE DESPESAS POR MES\n\n");

        printf("1 -\tJan\tR$%.2f\n", soma[0]);
        printf("2 -\tFev\tR$%.2f\n", soma[1]);
        printf("3 -\tMar\tR$%.2f\n", soma[2]);
        printf("4 -\tAbr\tR$%.2f\n", soma[3]);
        printf("5 -\tMai\tR$%.2f\n", soma[4]);
        printf("6 -\tJun\tR$%.2f\n", soma[5]);
        printf("7 -\tJul\tR$%.2f\n", soma[6]);
        printf("8 -\tAgo\tR$%.2f\n", soma[7]);
        printf("9 -\tSet\tR$%.2f\n", soma[8]);
        printf("10 -\tOut\tR$%.2f\n", soma[9]);
        printf("11 -\tNov\tR$%.2f\n", soma[10]);
        printf("12 -\tDez\tR$%.2f\n", soma[11]);
        printf("\n\n");
    }
}