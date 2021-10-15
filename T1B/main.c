#include "t.h"

int main(){

    FILE *arquivo = malloc(sizeof(FILE*));

    char string[sizeof(Reg)];
    add end;
    Reg registro;
    printf("%ld\n",sizeof(Reg)+10*sizeof(int)+20*sizeof(char));

    criaArquivo(N_ARQUIVO);

    scanf("%[^\n]",string);
    sscanf(string,"%ld %s %s %s %s %s %s %d %s %s",&registro.key,registro.nome,registro.lName,registro.city,registro.state,registro.cep,registro.phone,&end.nro,end.rua,end.complemento);
    registro.adress = end;

    int v[10];

    v[0] = sizeof(long int);
    v[1] = strlen(registro.lName)+1;
    v[2] = strlen(registro.nome)+1;
    v[3] = sizeof(int);
    v[4] = strlen(registro.adress.rua)+1;
    v[5] = strlen(registro.adress.complemento)+1;
    v[6] = strlen(registro.city)+1;
    v[7] = strlen(registro.state)+1;
    v[8] = strlen(registro.cep)+1;
    v[9] = strlen(registro.phone)+1;

    int soma=0;
    for(int i=0;i<10;i++)
        soma += v[i];

    int tam = 10 * sizeof(int) + 20 * sizeof(char) + soma;


    arquivo = fopen(N_ARQUIVO,"ab");
    escreve_arquivo(arquivo,registro,'1',v,tam);
    fclose(arquivo);

    arquivo = fopen(N_ARQUIVO,"rb");
    le_arquivo(arquivo);
    fclose(arquivo);

    return 0;

}

