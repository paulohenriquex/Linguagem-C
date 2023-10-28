#include <stdio.h>
#include <locale.h>
#include <windows.h>

void cadastrodespesa();
void cadastroreceitas();
void valorfuturo();
void juroscompostos();
void jurossimples();
void investimentofiss();

int main()
{
    setlocale(LC_ALL, "");
    int op = 9;
    while (op != 0)
    {
        system("cls");
        printf("1 -  Cadastrar despesas\n");
        printf("2 -  Cadastrar receitas\n");
        printf("3 -  Valor futuro do investimento mensal\n");
        printf("4 -  Juros compostos\n");
        printf("5 -  Juros simples\n");
        printf("6 - Investimento FIIS\n");
        printf("0 - Sair\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            cadastrodespesa();
            break;
        case 2:
            cadastroreceitas();
            break;
        case 3:
            valorfuturo();
            break;
        case 4:
            juroscompostos();
            break;
        case 5:
            jurossimples();
            system("pause");
            break;
        case 6:
            investimentofiss();
            break;
        }
    }
}