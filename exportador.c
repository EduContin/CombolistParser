/*LE O NOVO ARQUIVO. BINARIO E PASSA OS DADOS PARA UM NOVO ARQUIVO TXT*/
/*Recebe o arquivo binário como argumento*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *Conversao_Binario_String(const char *binario) {
    int tamanho = strlen(binario) / 8;                          // Calcula o tamanho da string resultante
    char *resultado = (char *)malloc(tamanho + 1);              // Aloca memória para a string resultante

    // Repetição para os bytes
    for (int i = 0; i < tamanho; i++) {
        int byte = 0;

        // Passa 8 bits para 1 byte
        for (int j = 0; j < 8; j++) {
            byte = (byte << 1) | (binario[i * 8 + j] - '0');
        }

        // Passa o byte pra string resultado
        resultado[i] = (char)byte;

    }

    resultado[tamanho] = '\0'; // Insere o caracter nulo no final da string
    return resultado;
}


int main(int argc,char *argv[]){
    /*agrv[2] se refere ao arquivo.bin, já q o argv[1] se refere ao arquivo.txt que será utilizado no gerador*/

    char *arquivo_entrada = argv[2];


    // Abertura de Arquivo.bin + Criação caso inexistente da saída em txt
    FILE * arquivo_bin, *arquivo_txt;
    arquivo_bin = fopen(arquivo_entrada, "rb");
    arquivo_txt = fopen("saida.txt", "w");

    char binario[368];
    
    if(arquivo_bin){
        for(int i = 0;!feof(arquivo_bin);i++){
            fgets(binario,368,arquivo_bin);
            char *String_Saida = Conversao_Binario_String(binario);
            fprintf(arquivo_txt,"%s\n", String_Saida);
        }
    } else{
        printf("Falha ao abrir o arquivo");
    }
    fclose(arquivo_bin);
    fclose(arquivo_txt);

        
}
