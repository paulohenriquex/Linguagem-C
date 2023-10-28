#include "func.h"

void cad_receitas()
{

    int opc, i = 0, stop = 0, id, encontrou = 0, opcao = 1, mes;

    FILE *temp;
    float total = 0;
    char painel[50], is_number = 1;

    printf("1 - Cadastrar Receitas\n");
    printf("2 - Mostrar Receitas (mes)\n");
    printf("3 - Alterar Receitas\n");
    printf("4 - Excluir Receitas\n");
    printf("5 - Listar todas as Receitas\n");
    printf("6 - Sair\n");
    scanf("%s", painel);

    for (i = 0; painel[i] != '\0'; i++)
    {
        if (!isdigit(painel[i]))
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

    switch (atoi(painel))
    {
        // CADASTRAR RECEITAS
    case 1:
        printf("CADASTRAR RECEITAS\n\n");
        receita = fopen("rec.txt", "a");

        if (receita == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        for (i = 0; stop != 2; i++)
        {
            printf("ID receita: ");
            scanf("%d", &rec[i].id);

            printf("Nome receita: ");
            scanf("%s", rec[i].nome);

            printf("Mes da receita 1-12: ");
            scanf("%d", &rec[i].mes);

            printf("Valor da receita: ");
            scanf("%f", &rec[i].vl);

            fprintf(receita, "%d %s %d %.2f\n", rec[i].id, rec[i].nome, rec[i].mes, rec[i].vl);

            printf("1 - Continuar\n");
            printf("2 - Sair\n");
            scanf("%d", &stop);
        }

        fclose(receita);
        printf("receitas cadastradas com sucesso!\n");
        break;

    case 2:
        system("cls");
        // MOSTRAR RECEITAS
        listar(opcao);
        printf("MOSTRAR RECEITAS FILTRADAS POR MES\n\n");
        printf("Escolha o mes que deseja filtrar: ");
        scanf("%d", &opc);

        receita = fopen("rec.txt", "r");

        if (receita == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        system("cls");
        printf("|-------|-------------|--------|----------|\n");
        printf("|  ID   |   Receita   |   Mes  |  Valor   |\n");
        printf("|-------|-------------|--------|----------|\n");
        while (fscanf(receita, "%d %s %d %f", &rec[i].id, rec[i].nome, &rec[i].mes, &rec[i].vl) != EOF)
        {
            if (rec[i].mes == opc)
            {
                printf("|%-7d|%-13s|%-8d|%-10.2f|\n", rec[i].id, rec[i].nome, rec[i].mes, rec[i].vl);
                total += rec[i].vl;
            }
            i++;
        }
        fclose(receita);
        printf("|-------|-------------|--------|----------|\n");
        printf("\n\n");
        printf("Total R$%.2f\n\n\n", total);
        break;
    case 3:
        system("cls");

        printf("ALTERAR RECEITA\n\n");

        listar(opcao);
        // ALTERAR RECEITAS

        printf("Digite o ID da receita: ");
        scanf("%d", &id);

        printf("Digite o mes da receita: ");
        scanf("%d", &mes);

        receita = fopen("rec.txt", "r");
        if (receita == NULL)
        {
            printf("Erro ao abrir arquivo rec\n");
            return;
        }

        temp = fopen("temp.txt", "w");

        if (temp == NULL)
        {
            printf("Erro ao abrir arquivo temp\n");
            fclose(temp);
            return;
        }

        while (fscanf(receita, "%d %s %d %f", &rec[i].id, rec[i].nome, &rec[i].mes, &rec[i].vl) != EOF)
        {
            if (id != rec[i].id || mes != rec[i].mes)
            {
                fprintf(temp, "%d %s %d %.2f\n", rec[i].id, rec[i].nome, rec[i].mes, rec[i].vl);
            }
            else
            {
                printf("Novo ID da receita: ");
                scanf("%d", &rec[i].id);

                printf("Novo nome da receita: ");
                scanf("%s", rec[i].nome);

                printf("Novo mes da receita (1-12): ");
                scanf("%d", &rec[i].mes);

                printf("Novo valor da receita: ");
                scanf("%f", &rec[i].vl);

                fprintf(temp, "%d %s %d %.2f\n", rec[i].id, rec[i].nome, rec[i].mes, rec[i].vl);
                encontrou = 1;
            }

            i++;
        }

        fclose(receita);
        fclose(temp);

        if (encontrou == 1)
        {
            if (remove("rec.txt") == 0)
            {
                rename("temp.txt", "rec.txt");
                printf("\nReceita alterada com sucesso\n");
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

    case 4: // EXCLUIR RECEITAS
        system("cls");
        printf("EXCLUIR RECEITAS\n\n");
        listar(opcao);

        printf("Digite o ID da receita a ser excluida: ");
        scanf("%d", &id);

        printf("Digite o mes da receita: ");
        scanf("%d", &mes);

        // abre o arquivo original para leitura
        receita = fopen("rec.txt", "r");

        if (receita == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        // cria um arquivo temporário para escrita
        temp = fopen("temp.txt", "w");

        if (temp == NULL)
        {
            printf("Erro ao criar arquivo temporario\n");
            fclose(receita);
            return;
        }

        // lê os dados do arquivo original, copiando todos os registros,
        // exceto aquele que possui o ID informado

        while (fscanf(receita, "%d %s %d %f", &rec[i].id, rec[i].nome, &rec[i].mes, &rec[i].vl) != EOF)
        {
            if (id != rec[i].id || mes != rec[i].mes)
            {
                fprintf(temp, "%d %s %d %.2f\n", rec[i].id, rec[i].nome, rec[i].mes, rec[i].vl);
            }
            else
            {
                encontrou = 1;
            }
            i++;
        }

        fclose(receita);
        fclose(temp);

        // remove o arquivo original e renomeia o arquivo temporário para ter o mesmo nome do arquivo original

        if (encontrou == 1)
        {
            if (remove("rec.txt") == 0)
            {
                rename("temp.txt", "rec.txt");
                printf("Receita excluida com sucesso\n");
            }
            else
            {
                printf("Erro ao excluir o arquivo rec.txt\n");
                remove("temp.txt");
            }
        }
        else
        {
            printf("Receita nao encontrada\n");
        }
        break;

        // LISTAR TODAS AS RECEITAS
    case 5:
        system("cls");
        printf("LISTAR TODAS AS RECEITAS\n\n");

        receita = fopen("rec.txt", "r");

        if (receita == NULL)
        {
            printf("Erro ao abrir arquivo\n");
            return;
        }

        system("cls");
        printf("|-------|-------------|--------|----------|\n");
        printf("|  ID   |   Receita   |   Mes  |  Valor   |\n");
        printf("|-------|-------------|--------|----------|\n");
        while (fscanf(receita, "%d %s %d %f", &rec[i].id, rec[i].nome, &rec[i].mes, &rec[i].vl) != EOF)
        {
            printf("|%-7d|%-13s|%-8d|%-10.2f|\n", rec[i].id, rec[i].nome, rec[i].mes, rec[i].vl);
            total += rec[i].vl;
            i++;
        }
        fclose(receita);
        printf("|-------|-------------|--------|----------|\n");
        printf("\n\n");
        printf("Total R$%.2f\n\n", total);
        break;
    case 6:
        printf("Saindo do sistema!\n");
        break;
    default:
        printf("Opcao invalida\n");
        break;
    }
}