/*LE O NOVO ARQUIVO. BINARIO E PASSA OS DADOS PARA UM NOVO ARQUIVO TXT*/
/*Recebe o arquivo binário como argumento*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_BIN 400


// Função para a Conversão do Binário para String
char *Conversao_Binario_String(const char *binario) {
    int Tamanho_String = strlen(binario) / 8;                          // Calcula o tamanho da string resultante
    char *Resultado_String = (char *)malloc(Tamanho_String + 1);       // Aloca memória para a string resultante

    // Repetição para os bytes
    for (int i = 0; i < Tamanho_String; i++) {
        int byte = 0;

        // Passa 8 bits para 1 byte
        for (int j = 0; j < 8; j++) {
            byte = (byte << 1) | (binario[i * 8 + j] - '0');
        }

        // Passa o byte pra string resultado
        Resultado_String[i] = (char)byte;

    }

    Resultado_String[Tamanho_String] = '\0'; // Insere o caracter nulo no final da string
    return Resultado_String;
    free(Resultado_String); // Libera a memória alocada pelo Resultado_String
}


int main(int argc,char *argv[]){
    /*agrv[3] se refere ao arquivo binário que virá do editor.c, o qual será transcrito para txt*/

    // Verifica a se a quantidade de argumentos recebidos esta correta
    if (argc < 2)
    {
        printf("ERRO: numero errado de argumentos presentes");
        return 1;
    }
    
    char *arquivo_entrada = argv[1];

    // Abertura de Arquivo.bin + Criação caso inexistente da saída em txt
    FILE * arquivo_bin, *arquivo_txt;
    arquivo_bin = fopen(arquivo_entrada, "rb");
    arquivo_txt = fopen("saida.txt", "w");

    char* binario =(char*) calloc(TAMANHO_BIN, sizeof(char));
    
    if(arquivo_bin){
        while(!feof(arquivo_bin)){
            fgets(binario,TAMANHO_BIN,arquivo_bin);
            char *String_Saida = Conversao_Binario_String(binario);
            fprintf(arquivo_txt,"%s\n", String_Saida);
        }
        printf("Exportacao do arquivo realizada com sucesso!!!");
        free(binario);
        fclose(arquivo_bin);
        fclose(arquivo_txt);
    } else{
        printf("Falha ao abrir o arquivo");
        return 1;
    }    
}
