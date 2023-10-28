#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

typedef struct No
{
    char nome[50];
} No;

int cont2 = 0;
// Carrega o dicion�rio a partir de um arquivo
int carregarDicionario(FILE *dicionario, No **busca);

// Abre o arquivo do dicion�rio
void abrirDicionario(FILE **dicionario);

// Fun��o principal do corretor ortogr�fico
void corretorOrtografico(No *busca, int cont);

// Remove caracteres especiais de uma palavra
void removerCaracteresEspeciais(char *palavra);

// Busca uma palavra no dicion�rio
bool buscarPalavra(No *busca, int inicio, int fim, char *palavra);

// Fun��o de compara��o para ordena��o das palavras
int compararNo(const void *a, const void *b);

// Sugere corre��es para uma palavra errada
void sugerirCorrecao(No *busca, int cont, char *palavraErrada);

int main()
{
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();

    setlocale(LC_ALL, "");
    int cont = 0;

    FILE *dicionario;
    No *busca;

    abrirDicionario(&dicionario);                  // Abre o arquivo do dicion�rio
    cont = carregarDicionario(dicionario, &busca); // Carrega o dicion�rio para a mem�ria
    fclose(dicionario);                            // Fecha o arquivo do dicion�rio

    corretorOrtografico(busca, cont); // Executa o corretor ortogr�fico

    free(busca); // Libera a mem�ria alocada para o dicion�rio

    end_time = clock();
    total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo total de execu��o: %.2f segundos\n", total_time);
    printf("Cont2 e: %d", cont2);
    return 0;
}

// Abre o arquivo do dicion�rio
void abrirDicionario(FILE **dicionario)
{
    *dicionario = fopen("brazilian.dic", "r"); // Abre o arquivo do dicion�rio para leitura
    if (*dicionario == NULL)
    {
        printf("Erro ao abrir o dicionario\n");
        exit(1);
    }
}

// Fun��o principal do corretor ortogr�fico
void corretorOrtografico(No *busca, int cont)
{
    FILE *texto;
    char buf[1024];
    bool encontrada;

    texto = fopen("brascubas.txt", "r"); // Abre o arquivo do texto para leitura
    if (texto == NULL)
    {
        printf("Erro ao abrir o texto brascubas\n");
        exit(1);
    }

    while (fscanf(texto, "%s", buf) != EOF) // L� cada palavra do texto
    {
        // PRINTANDO O RESTO DO TEXTO
        // printf("%s ", buf);
        strlwr(buf);                                         // Converte a palavra para min�sculas
        removerCaracteresEspeciais(buf);                     // Remove caracteres especiais da palavra
        encontrada = buscarPalavra(busca, 0, cont - 1, buf); // Verifica se a palavra est� no dicion�rio

        if (!encontrada)
            sugerirCorrecao(busca, cont, buf); // Se a palavra n�o for encontrada, sugere corre��es
    }

    fclose(texto); // Fecha o arquivo do texto
}

// Remove caracteres especiais de uma palavra
void removerCaracteresEspeciais(char *palavra)
{
    int i, j;
    for (i = 0, j = 0; palavra[i] != '\0'; i++)
    {
        if (isalpha(palavra[i]) || palavra[i] == '\'') // Mant�m apenas letras e ap�strofos na palavra
        {
            palavra[j++] = palavra[i];
        }
    }
    palavra[j] = '\0'; // Adiciona o caractere nulo para finalizar a palavra corretamente
}

// Busca uma palavra no dicion�rio
bool buscarPalavra(No *busca, int inicio, int fim, char *palavra)
{
    if (inicio > fim)
        return false;

    int meio = (inicio + fim) / 2;
    int comparacao = strcmp(busca[meio].nome, palavra);

    if (comparacao == 0)
    { // A palavra foi encontrada no dicion�rio
        return true;
    }
    else if (comparacao > 0)
    { // A palavra est� antes da posi��o atual no dicion�rio
        cont2++;
        return buscarPalavra(busca, inicio, meio - 1, palavra);
    }
    else // A palavra est� depois da posi��o atual no dicion�rio
        return buscarPalavra(busca, meio + 1, fim, palavra);
}

// Sugere corre��es para uma palavra errada
void sugerirCorrecao(No *busca, int cont, char *palavraErrada)
{

    // Encontra palavras sugestivas no dicion�rio
    for (int i = 0; i < cont; i++)
    {
        if (strcmp(busca[i].nome, palavraErrada) > 0) // Encontra a primeira palavra no dicion�rio maior que a palavra errada
        {

            // printf("[%s]", busca[i].nome);
            break;
        }
    }
    // printf("\n");
}

// Carrega o dicion�rio a partir de um arquivo
int carregarDicionario(FILE *dicionario, No **busca)
{
    char buf[1024];
    int cont = 0;
    abrirDicionario(&dicionario); // Abre o arquivo do dicion�rio

    while (fscanf(dicionario, "%s", buf) != EOF) // L� cada palavra do dicion�rio
    {
        cont++;
    }

    fseek(dicionario, 0, SEEK_SET); // Volta para o in�cio do arquivo do dicion�rio

    *busca = (No *)malloc(sizeof(No) * cont); // Aloca mem�ria para o vetor de busca

    if (*busca == NULL)
    {
        printf("Erro ao alocar mem�ria\n");
        exit(1);
    }

    cont = 0;

    while (fscanf(dicionario, "%s", buf) != EOF) // L� cada palavra do dicion�rio novamente
    {
        strlwr(buf);                          // Converte a palavra para min�sculas
        removerCaracteresEspeciais(buf);      // Remove caracteres especiais da palavra
        if (buf[0] != '\0')                   // Verifica se a palavra n�o est� vazia
            strcpy((*busca)[cont].nome, buf); // Copia a palavra para o vetor de busca
        cont++;
    }

    // Ordena o vetor busca em ordem alfab�tica
    qsort(*busca, cont, sizeof(No), compararNo);

    fclose(dicionario); // Fecha o arquivo do dicion�rio

    return cont; // Retorna o n�mero de palavras carregadas
}

// Fun��o de compara��o para ordena��o das palavras
int compararNo(const void *a, const void *b)
{
    const No *no1 = (const No *)a;
    const No *no2 = (const No *)b;
    return strcmp(no1->nome, no2->nome); // Compara as palavras em ordem alfab�tica
}