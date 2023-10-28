#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// declaração da strtura para receber os valores da imagem
typedef struct
{
    int largura;
    int altura;
    int valormaximo;
    int **pixels;
} imagempgm;

// Função para ler uma imagem PGM do arquivo
imagempgm lerimagempgm(const char *nomeArquivo)
{
    // variavel imagem do tipo imagempgm
    imagempgm imagem;

    // Abrindo arquivo
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char formato[3];
    fscanf(arquivo, "%s", formato);

    // Verificando formato do arquivo
    if (formato[0] != 'P' || formato[1] != '2')
    {
        printf("Formato de arquivo inválido. Apenas PGM (P2) é suportado.\n");
        exit(1);
    }

    // Lendo a largura e altura da imagem e o valor maximo de pixels
    fscanf(arquivo, "%d %d", &imagem.largura, &imagem.altura);
    fscanf(arquivo, "%d", &imagem.valormaximo);

    // Alocando memoria para os pixels
    imagem.pixels = (int **)malloc(imagem.altura * sizeof(int *));

    for (int i = 0; i < imagem.altura; i++)
    {
        imagem.pixels[i] = (int *)malloc(imagem.largura * sizeof(int));

        for (int j = 0; j < imagem.largura; j++)
        {
            // Lendo os valores dos pixels
            fscanf(arquivo, "%d", &imagem.pixels[i][j]);
        }
    }

    fclose(arquivo);
    return imagem;
}

// Função para escrever uma imagem PGM rotacionada em outro arquivo
void escreverimagempgm(const char *nomeArquivo, imagempgm imagem)
{
    // Abrindo novo arquivo para salvar a imagem rotacionada
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    // Escrevendo o cabeçalho no novo arquivo
    fprintf(arquivo, "P2\n");
    fprintf(arquivo, "%d %d\n", imagem.largura, imagem.altura);
    fprintf(arquivo, "%d\n", imagem.valormaximo);

    // Escrevendo os valores dos pixels
    for (int linha = 0; linha < imagem.altura; linha++)
    {
        for (int coluna = 0; coluna < imagem.largura; coluna++)
        {
            fprintf(arquivo, "%d ", imagem.pixels[linha][coluna]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

// Função para rotacionar uma imagem utilizando o método do vizinho mais próximo
imagempgm rotacionarImagem(imagempgm imagemOriginal, float angulo)
{
    // Valor de pi, seno, cosseno, radiano.
    float pi = 3.1416;
    float radiano = angulo * pi / 180.0;
    float seno = sin(radiano);
    float cosseno = cos(radiano);

    // Calculando o centro X e Y da imagem.
    int centroX = imagemOriginal.largura / 2;
    int centroY = imagemOriginal.altura / 2;

    // Calcular as dimensões da nova imagem
    // Verificando quantos pixels a nova imagem terá, função fabs faz o numero ser inteiro positivo mesmo que seja negativo
    int novoLargura = (int)(fabs(imagemOriginal.largura * cosseno) + fabs(imagemOriginal.altura * seno));
    int novoAltura = (int)(fabs(imagemOriginal.altura * cosseno) + fabs(imagemOriginal.largura * seno));

    // Criar uma nova imagem com as dimensões calculadas
    // Criando uma variavel do tipo imagempgm, recebendo nova largura, nova altura e novo valor maximo
    imagempgm imagemRotacionada;
    imagemRotacionada.largura = novoLargura;
    imagemRotacionada.altura = novoAltura;
    imagemRotacionada.valormaximo = imagemOriginal.valormaximo;

    // Alocando memoria para os pixels para a imagem rotacionada
    imagemRotacionada.pixels = (int **)malloc(imagemRotacionada.altura * sizeof(int *));

    for (int i = 0; i < imagemRotacionada.altura; i++)
    {
        imagemRotacionada.pixels[i] = (int *)malloc(imagemRotacionada.largura * sizeof(int));

        for (int j = 0; j < imagemRotacionada.largura; j++)
        {
            // preenchendo os espaços com branco para o novo tamanho da imagem
            imagemRotacionada.pixels[i][j] = 255;
        }
    }

    for (int i = 0; i < imagemOriginal.altura; i++)
    {
        for (int j = 0; j < imagemOriginal.largura; j++)
        {
            // calculo para representar a posição atual do pixel em relação ao centro da imagem original
            int x = j - centroX;
            int y = i - centroY;

            // esse calcúlo é usados para calcular as coordenadas correspondentes na nova imagem rotacionada.Isso é feito aplicando as fórmulas de rotação.
            int novoX = round(x * cosseno - y * seno) + (novoLargura / 2);
            int novoY = round(x * seno + y * cosseno) + (novoAltura / 2);

            // Verificando se novoX e novoY estão dentro dos limites da nova imagem rotacionada
            // Se estiverem dentro dos limites, o valor do pixel correspondente na imagem original (imagemOriginal.pixels[i][j]) é atribuído ao pixel correspondente na nova imagem rotacionada (imagemRotacionada.pixels[novoY][novoX]).
            if (novoX >= 0 && novoX < novoLargura && novoY >= 0 && novoY < novoAltura)
            {
                // Atribuindo o valor do pixel correspondente na imagem original para a nova imagem rotacionada
                imagemRotacionada.pixels[novoY][novoX] = imagemOriginal.pixels[i][j];
            }
        }
    }

    return imagemRotacionada;
}

// Função para liberar memória alocada
void liberarImagem(imagempgm imagem)
{
    for (int i = 0; i < imagem.altura; i++)
    {
        free(imagem.pixels[i]);
    }
    free(imagem.pixels);
}

int main(int argc, char *argv[])
{
    // Verificação de entrada de argummentos
    if (argc != 3)
    {
        printf("Uso incorreto. Por favor, forneça o nome do arquivo PGM e o ângulo de rotação como argumentos.\n");
        return 1;
    }

    // Passando o nome do arquivo e angulo de rotação como argumentos, afot converte uma string para um numero float
    char *nomeArquivo = argv[1];
    float angulo = atof(argv[2]);

    // Lendo a imagem original do arquivo
    imagempgm imagemOriginal = lerimagempgm(nomeArquivo);

    // Rotacionando a imagem
    imagempgm imagemRotacionada = rotacionarImagem(imagemOriginal, angulo);

    // Escrevendo a imagem rotacionada em um novo arquivo
    escreverimagempgm("imagem_rotacionada.pgm", imagemRotacionada);

    // liberando a memoria alocada
    liberarImagem(imagemOriginal);
    liberarImagem(imagemRotacionada);

    printf("Imagem rotacionada salva com sucesso!\n");

    return 0;
}
