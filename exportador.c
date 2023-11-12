/*LE O NOVO ARQUIVO. BINARIO E PASSA OS DADOS PARA UM NOVO ARQUIVO TXT*/
/*Recebe o nome do Arquivo Binario e do Arquivo de Texto como argumentos*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *Conversao_Binario_String(char *binario){
    int tamanho = strlen(binario);

    // Garante que o tamanho da string binária seja múltiplo de 8 para representação de bytes
    if (tamanho % 8 != 0) {
        printf("Erro: A string binária não tem um tamanho válido.\n");
        exit(1);
    }

    // Aloca memória para a string resultante (incluindo o caractere nulo)
    char *resultado = (char *)malloc(tamanho / 8 + 1);

    if (resultado == NULL) {
        printf("Erro ao alocar memória");
        exit(1);
    }

    // Converte cada byte da string binária para um caractere
    for (int i = 0; i < tamanho / 8; i++) {
        char byte = 0;

        // Converte cada bit do byte
        for (int j = 0; j < 8; j++) {
            byte = (byte << 1) | (binario[i * 8 + j] - '0');
        }

        resultado[i] = byte;
    }

    resultado[tamanho / 8] = '\0';

    return resultado;
}




int main(int argc,char *argv[]){
    /*agrv[1] se refere ao arquivo.bin, já o argv[2] se refere ao arquivo.txt*/

    printf("%d\n", argc);

    char *arquivo_entrada = argv[1];
    char *arquivo_saida = argv[2];

    FILE * arquivo_bin, *arquivo_txt;
    arquivo_bin = fopen(arquivo_entrada, "rb");
    arquivo_txt = fopen(arquivo_saida, "w");

    char binario[50];
    if(arquivo_bin){
        fscanf(arquivo_bin,"%s", &binario);
        
        Conversao_Binario_String(binario);
    }
    else{
        printf("Falha ao abrir o arquivo");
    }
}
