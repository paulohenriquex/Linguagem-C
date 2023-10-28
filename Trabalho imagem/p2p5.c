#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// declaração da estrutura para receber os valores da imagem
typedef struct
{
    int largura;
    int altura;
    int valormaximo;
    unsigned char **pixels;
} imagemPGM;

// Função para ler uma imagem PGM do arquivo
imagemPGM lerImagemPGM(const char *nomeArquivo)
{
    // variável imagem do tipo imagemPGM
    imagemPGM imagem;

    // Abrindo arquivo
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char formato[3];
    fscanf(arquivo, "%s", formato);

    // Verificando formato do arquivo
    if (formato[0] != 'P')
    {
        printf("Formato de arquivo inválido. Apenas PGM (P5 e P2) é suportado.\n");
        exit(1);
    }

    // Verificando o tipo de imagem PGM
    if (formato[1] == '5')
    {
        // Leitura de imagem PGM no formato P5
        fscanf(arquivo, "%d %d", &imagem.largura, &imagem.altura);
        fscanf(arquivo, "%d", &imagem.valormaximo);

        // Alocando memória para os pixels, unsigned usado para modificar o valor para positivo
        imagem.pixels = (unsigned char **)malloc(imagem.altura * sizeof(unsigned char *));

        for (int i = 0; i < imagem.altura; i++)
        {
            imagem.pixels[i] = (unsigned char *)malloc(imagem.largura * sizeof(unsigned char));
            fread(imagem.pixels[i], sizeof(unsigned char), imagem.largura, arquivo);
        }
    }
    else if (formato[1] == '2')
    {
        // Leitura de imagem PGM no formato P2
        char linha[100];
        fgets(linha, sizeof(linha), arquivo);
        while (linha[0] == '#')
        {
            fgets(linha, sizeof(linha), arquivo);
        }

        sscanf(linha, "%d %d", &imagem.largura, &imagem.altura);
        fscanf(arquivo, "%d", &imagem.valormaximo);

        // Alocando memória para os pixels
        imagem.pixels = (unsigned char **)malloc(imagem.altura * sizeof(unsigned char *));

        for (int i = 0; i < imagem.altura; i++)
        {
            imagem.pixels[i] = (unsigned char *)malloc(imagem.largura * sizeof(unsigned char));

            for (int j = 0; j < imagem.largura; j++)
            {
                int valor;
                fscanf(arquivo, "%d", &valor);
                imagem.pixels[i][j] = (unsigned char)valor;
            }
        }
    }
    else
    {
        printf("Formato de arquivo inválido. Apenas PGM (P5 e P2) é suportado.\n");
        exit(1);
    }

    fclose(arquivo);
    return imagem;
}

// Função para escrever uma imagem PGM no arquivo
void escreverImagemPGM(const char *nomeArquivo, imagemPGM imagem)
{
    // Abrindo novo arquivo para salvar a imagem
    FILE *arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    // Escrevendo o cabeçalho no novo arquivo
    fprintf(arquivo, "P5\n");
    fprintf(arquivo, "%d %d\n", imagem.largura, imagem.altura);
    fprintf(arquivo, "%d\n", imagem.valormaximo);

    // Escrevendo os valores dos pixels
    for (int i = 0; i < imagem.altura; i++)
    {
        fwrite(imagem.pixels[i], sizeof(unsigned char), imagem.largura, arquivo);
    }

    fclose(arquivo);
}

// Função para rotacionar uma imagem utilizando o método do vizinho mais próximo
imagemPGM rotacionarImagem(imagemPGM imagemOriginal, float angulo)
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
    // Função fabs faz o número ser inteiro positivo mesmo que seja negativo
    int novoLargura = (int)(fabs(imagemOriginal.largura * cosseno) + fabs(imagemOriginal.altura * seno));
    int novoAltura = (int)(fabs(imagemOriginal.altura * cosseno) + fabs(imagemOriginal.largura * seno));

    // Criar uma nova imagem com as dimensões calculadas
    // Criando uma variável do tipo imagemPGM, recebendo nova largura, nova altura e novo valor máximo
    imagemPGM imagemRotacionada;
    imagemRotacionada.largura = novoLargura;
    imagemRotacionada.altura = novoAltura;
    imagemRotacionada.valormaximo = imagemOriginal.valormaximo;

    // Alocando memória para os pixels para a imagem rotacionada
    imagemRotacionada.pixels = (unsigned char **)malloc(imagemRotacionada.altura * sizeof(unsigned char *));

    for (int i = 0; i < imagemRotacionada.altura; i++)
    {
        imagemRotacionada.pixels[i] = (unsigned char *)malloc(imagemRotacionada.largura * sizeof(unsigned char));

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
            // cálculo para representar a posição atual do pixel em relação ao centro da imagem original
            int x = j - centroX;
            int y = i - centroY;

            // são usados para calcular as coordenadas correspondentes na nova imagem rotacionada.
            // Isso é feito aplicando as fórmulas de rotação.
            int novoX = round(x * cosseno - y * seno) + (novoLargura / 2);
            int novoY = round(x * seno + y * cosseno) + (novoAltura / 2);

            // Verificando se novoX e novoY estão dentro dos limites da nova imagem rotacionada
            // Se estiverem dentro dos limites, o valor do pixel correspondente na imagem original
            // (imagemOriginal.pixels[i][j]) é atribuído ao pixel correspondente na nova imagem rotacionada
            // (imagemRotacionada.pixels[novoY][novoX]).
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
void liberarImagem(imagemPGM imagem)
{
    for (int i = 0; i < imagem.altura; i++)
    {
        free(imagem.pixels[i]);
    }
    free(imagem.pixels);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso incorreto. Por favor, forneça o nome do arquivo PGM e o ângulo de rotação como argumentos.\n");
        return 1;
    }

    // Passando o nome do arquivo e ângulo de rotação como argumentos
    char *nomeArquivo = argv[1];
    float angulo = atof(argv[2]);

    // Lendo a imagem original do arquivo
    imagemPGM imagemOriginal = lerImagemPGM(nomeArquivo);

    // Rotacionando a imagem
    imagemPGM imagemRotacionada = rotacionarImagem(imagemOriginal, angulo);

    // Escrevendo a imagem rotacionada em um novo arquivo
    escreverImagemPGM("imagem_rotacionada.pgm", imagemRotacionada);

    // Liberando a memória alocada
    liberarImagem(imagemOriginal);
    liberarImagem(imagemRotacionada);

    printf("Imagem rotacionada salva com sucesso!\n");

    return 0;
}
