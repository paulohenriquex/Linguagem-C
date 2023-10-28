#include "func.h"

void cad_despesas()
{
    int i = 0, stop = 0, opc, id, encontrou = 0, opcao = 2, mes;
    float total = 0;
    char op[50], is_number = 1;

    printf("1 - Cadastrar despesas\n");
    printf("2 - Mostrar despesas (mes)\n");
    printf("3 - Alterar despesas\n");
    printf("4 - Excluir despesas\n");
    printf("5 - Listar todas as despesas\n");
    printf("6 - Sair\n");
    scanf("%s", op);

    for (i = 0; op[i] != '\0'; i++)
    {
        if (!isdigit(op[i]))
        {
            is_number = 0;
            break;
        }
    }

    if (!is_number)
    {
        system("cls");
        printf("Erro: voce nao digitou um numero.\n");
        return;
    }

    switch (atoi(op))
    {
        // CADASTRAR DESPESAS
    case 1:

        despesa = fopen("des.txt", "a");

        if (despesa == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        for (i = 0; stop != 2; i++)
        {
            printf("ID despesa: ");
            scanf("%d", &des[i].id);

            printf("Nome despesa: ");
            scanf("%s", des[i].nome);

            printf("Mes da despesa 1-12: ");
            scanf("%d", &des[i].mes);

            printf("Valor da despesa: ");
            scanf("%f", &des[i].vl);

            fprintf(despesa, "%d %s %d %.2f\n", des[i].id, des[i].nome, des[i].mes, des[i].vl);

            printf("1 - Continuar\n");
            printf("2 - Sair\n");
            scanf("%d", &stop);
        }

        fclose(despesa);
        printf("Despesas cadastradas com sucesso!\n");
        break;
        // MOSTRAR DESPESAS
    case 2:

        system("cls");
        // MOSTRAR RECEITAS
        listar(opcao);
        printf("MOSTRAR RECEITAS FILTRADAS POR MES\n\n");
        printf("Escolha o mes que deseja filtrar: ");
        scanf("%d", &opc);

        despesa = fopen("des.txt", "r");

        if (despesa == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        system("cls");
        printf("|-------|-------------|--------|----------|\n");
        printf("|  ID   |   Despesa   |   Mes  |  Valor   |\n");
        printf("|-------|-------------|--------|----------|\n");
        while (fscanf(despesa, "%d %s %d %f", &rec[i].id, des[i].nome, &des[i].mes, &des[i].vl) != EOF)
        {
            if (des[i].mes == opc)
            {
                printf("|%-7d|%-13s|%-8d|%-10.2f|\n", des[i].id, des[i].nome, des[i].mes, des[i].vl);
                total += des[i].vl;
            }
            i++;
        }
        fclose(despesa);
        printf("|-------|-------------|--------|----------|\n");
        printf("\n\n");
        printf("Total R$%.2f\n\n\n", total);
        break;
    case 3:

        system("cls");

        printf("ALTERAR DESPESA\n\n");

        listar(opcao);
        // ALTERAR DESPESA

        printf("Digite o ID da despesa: ");
        scanf("%d", &id);

        printf("Digite o mes da despesa: ");
        scanf("%d", &mes);

        despesa = fopen("des.txt", "r");
        if (despesa == NULL)
        {
            printf("Erro ao abrir arquivo des\n");
            return;
        }

        temp = fopen("temp.txt", "w");

        if (temp == NULL)
        {
            printf("Erro ao abrir arquivo temp\n");
            fclose(temp);
            return;
        }

        while (fscanf(despesa, "%d %s %d %f", &des[i].id, des[i].nome, &des[i].mes, &des[i].vl) != EOF)
        {
            if (id != des[i].id || mes != des[i].mes)
            {
                fprintf(temp, "%d %s %d %.2f\n", des[i].id, des[i].nome, des[i].mes, des[i].vl);
            }
            else
            {
                printf("Novo ID da despesa: ");
                scanf("%d", &des[i].id);

                printf("Novo nome da despesa: ");
                scanf("%s", des[i].nome);

                printf("Novo mes da despesa (1-12): ");
                scanf("%d", &des[i].mes);

                printf("Novo valor da despesa: ");
                scanf("%f", &des[i].vl);

                fprintf(temp, "%d %s %d %.2f\n", des[i].id, des[i].nome, des[i].mes, des[i].vl);
                encontrou = 1;
            }

            i++;
        }

        fclose(despesa);
        fclose(temp);

        if (encontrou == 1)
        {
            if (remove("des.txt") == 0)
            {
                rename("temp.txt", "des.txt");
                printf("\nDespesa alterada com sucesso\n");
                break;
            }
            else
            {
                printf("Erro ao excluir o arquivo des.txt\n");
                remove("temp.txt");
                return;
            }
        }
        break;
    case 4: // EXCLUIR DESPESAS
        system("cls");
        printf("EXLCUIR DESPESAS\n\n");
        listar(opcao);
        printf("Digite o ID da despesa a ser excluida: ");
        scanf("%d", &id);

        printf("Digite o mes da despesa: ");
        scanf("%d", &mes);

        // abre o arquivo original para leitura
        despesa = fopen("des.txt", "r");

        if (despesa == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        // cria um arquivo temporário para escrita
        temp = fopen("temp.txt", "w");

        if (temp == NULL)
        {
            printf("Erro ao criar arquivo temporario\n");
            fclose(despesa);
            return;
        }

        // lê os dados do arquivo original, copiando todos os registros,
        // exceto aquele que possui o ID informado

        while (fscanf(despesa, "%d %s %d %f", &des[i].id, des[i].nome, &des[i].mes, &des[i].vl) != EOF)
        {
            if (id != des[i].id || mes != des[i].mes)
            {
                fprintf(temp, "%d %s %d %.2f\n", des[i].id, des[i].nome, des[i].mes, des[i].vl);
            }
            else
            {
                encontrou = 1;
            }
            i++;
        }

        fclose(despesa);
        fclose(temp);

        // remove o arquivo original e renomeia o arquivo temporário para ter o mesmo nome do arquivo original

        if (encontrou == 1)
        {
            if (remove("des.txt") == 0)
            {
                rename("temp.txt", "des.txt");
                printf("Despesa excluida com sucesso\n");
            }
            else
            {
                printf("Erro ao excluir o arquivo des.txt\n");
                remove("temp.txt");
            }
        }
        else
        {
            printf("Despesa nao encontrada\n");
        }
        break;

        // LISTAR TODAS AS DESPESAS
    case 5:
        system("cls");
        printf("LISTAR TODAS AS DESPESAS\n\n");
        despesa = fopen("des.txt", "r");

        if (despesa == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        system("cls");
        printf("|-------|-------------|--------|----------|\n");
        printf("|  ID   |   Despesa   |   Mes  |  Valor   |\n");
        printf("|-------|-------------|--------|----------|\n");
        while (fscanf(despesa, "%d %s %d %f", &des[i].id, des[i].nome, &des[i].mes, &des[i].vl) != EOF)
        {
            printf("|%-7d|%-13s|%-8d|%-10.2f|\n", des[i].id, des[i].nome, des[i].mes, des[i].vl);
            total += des[i].vl;
            i++;
        }
        fclose(despesa);
        printf("|-------|-------------|--------|----------|\n");
        printf("\n\n");
        printf("Total R$%.2f\n\n", total);
        break;
    case 6:
        break;
    default:
        printf("Opcao invalida\n");
        break;
    }
}