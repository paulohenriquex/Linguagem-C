#include "func.h"

void listar(int a)
{
    int i = 0;

    if (a == 1)
    {
        receita = fopen("rec.txt", "r");

        if (receita == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        printf("|-------|-------------|--------|----------|\n");
        printf("|  ID   |   Receita   |   Mes  |  Valor   |\n");
        printf("|-------|-------------|--------|----------|\n");
        while (fscanf(receita, "%d %s %d %f", &rec[i].id, rec[i].nome, &rec[i].mes, &rec[i].vl) != EOF)
        {
            printf("|%-7d|%-13s|%-8d|%-10.2f|\n", rec[i].id, rec[i].nome, rec[i].mes, rec[i].vl);
            i++;
        }
        fclose(receita);
        printf("|-------|-------------|--------|----------|\n");
        printf("\n\n");
    }
    else
    {
        despesa = fopen("des.txt", "r");

        if (despesa == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        printf("|-------|-------------|--------|----------|\n");
        printf("|  ID   |   Despesa   |   Mes  |  Valor   |\n");
        printf("|-------|-------------|--------|----------|\n");
        while (fscanf(despesa, "%d %s %d %f", &des[i].id, des[i].nome, &des[i].mes, &des[i].vl) != EOF)
        {
            printf("|%-7d|%-13s|%-8d|%-10.2f|\n", des[i].id, des[i].nome, des[i].mes, des[i].vl);
            i++;
        }
        fclose(despesa);
        printf("|-------|-------------|--------|----------|\n");
        printf("\n\n");
    }
}