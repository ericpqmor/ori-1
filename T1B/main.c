#include "t.h"


int main(){

    FILE *arquivo = malloc(sizeof(FILE*));

    char string[sizeof(Reg)];
    add end;
    Reg registro;
    printf("%ld\n",sizeof(Reg)+10*sizeof(int)+20*sizeof(char));

   //criaArquivo(N_ARQUIVO);
    int n;
    scanf("%d",&n);

    for(int i=0;i<10;i++){
    scanf("%*c%[^\n]",string);
    sscanf(string,"%ld %s %s %s %s %s %s %d %s %s",&registro.key,registro.nome,registro.lName,registro.city,registro.state,registro.cep,registro.phone,&end.nro,end.rua,end.complemento);
    registro.adress = end;

    
    
    insere(arquivo,registro);

    }

    arquivo = fopen(N_ARQUIVO,"rb");

    le_arquivo(arquivo);

    fclose(arquivo);

    print_arq_secundario();

    int pos,tam;
    char nome[10];

    if(busca_key(arquivo,378,&pos,&tam,nome,TRUE)){
        printf("%d %s\n",tam,nome);
    }


    return 0;

}
/*
gcc -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm main.c t.c t.h -o 1

*/

