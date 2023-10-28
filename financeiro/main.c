#include "func.h"
#define TAM 100

int main()
{
    char op[50], is_number = 1;
    int i = 0;

    printf("CONTROLE DE FINANCAS\n");
    setlocale(LC_ALL, "");

    des = (despesas *)malloc(sizeof(despesas) * TAM);
    rec = (receitas *)malloc(sizeof(receitas) * TAM);

    if (des == NULL)
    {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    do
    {
        printf("\n\n");
        printf("1 - Receitas\n");
        printf("2 - Despesas \n");
        printf("3 - Listar Rec/Des por mes\n");
        printf("4 - Balanco\n");
        printf("5 - Sair\n");
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
            printf("Erro: voce nao digitou um numero.\n");
            break;
        }

        switch (atoi(op))
        {
        case 1:
            cad_receitas();
            break;
        case 2:
            cad_despesas();
            break;
        case 3:
            mostrarLista();
            break;
        case 4:
            balanco();
            break;
        case 5:
            system("cls");
            printf("\n\nSAINDO DO SISTEMA.....\n\n");
            break;
        default:
            printf("Opcao invalida\n");
        }

    } while (atoi(op) != 5);

    free(des);
    free(rec);
    return 0;
}
